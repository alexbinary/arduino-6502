
const int ADDR[] = {A0,A1,A2,A3};
const int DATA[] = {D10,D9,D8,D7, D6,D5,D4,D3};
const int OEB = A4;
const int WEB = A5;


void setup() {
  
  Serial.begin(9600);
  while (!Serial);
  
  pinMode(OEB, OUTPUT);
  pinMode(WEB, OUTPUT);
  
  for(int i=0; i<4; i++) {
    pinMode(ADDR[i], OUTPUT);
  }
  for(int i=0; i<8; i++) {
    pinMode(DATA[i], INPUT);
  }

  digitalWrite(WEB, HIGH);

  writeROM();
}


void loop() {

  readROM();
}

void readROM() {

  for(unsigned char addr = 0 ; addr < 0xF ; addr++) {
    unsigned char data = readByte(addr);
    char output[25];
    sprintf(output, "R %01x %02x", addr, data);
    Serial.println(output);
  }
}


void writeROM() {

  unsigned char rom[] = {
    0xAD, 0x09, 0x00, // $0009 -> A
    0xAD, 0x0A, 0x00, // $000A -> A
    0x6D, 0x0B, 0x00, // A = A + $000B
    0x28,             // $0009
    0x02,             // $000A
    0x0A,             // $000B
    0x00, 0x00        // (RV) $FFFC $FFFD
  };
  unsigned char addr = 0x0;

  for(int i=0 ; i<14 ; i++) {
    unsigned char data = rom[i];
    char output[25];
    sprintf(output, "W %01x %02x", addr, data);
    Serial.println(output);
    writeByte(addr++, data);
  }
}


unsigned char readByte(unsigned char addr) {

  unsigned char data;

  setAddr(addr);
  delay(100);
  digitalWrite(OEB, LOW);
  delay(100);
  data = readData();

  return data;
}

void writeByte(unsigned char addr, unsigned char data) {

  digitalWrite(OEB, HIGH);
  delay(100);
  setAddr(addr);
  delay(100);
  digitalWrite(WEB, LOW);
  delay(100);
  setData(data);
  delay(100);
  digitalWrite(WEB, HIGH);
  delay(100);
}

void setAddr(unsigned char addr) {

  for(int i=0; i<4; i++) {
    digitalWrite(ADDR[i], addr & 1<<i);
  }
}

void setData(unsigned char data) {

  for(int i=0; i<8; i++) {
    pinMode(DATA[i], OUTPUT);
  }

  for(int i=0; i<8; i++) {
    digitalWrite(DATA[i], data & 1<<i);
  }
}

unsigned char readData() {

  for(int i=0; i<8; i++) {
    pinMode(DATA[i], INPUT);
  }

  unsigned char data = 0;
  for(int i=0; i<8; i++) {
    data += digitalRead(DATA[i]) << i;
  }

  return data;
}