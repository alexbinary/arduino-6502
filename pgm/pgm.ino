
const int ADDR[] = {A0,A1,A2,A3};
const int DATA[] = {D10,D9,D8,D7, D6,D5,D4,D3};
const int CLK = D2;
const int RW = A5;


void setup() {
  
  Serial.begin(9600);
  while (!Serial);
  
  for(int i=0; i<4; i++) {
    pinMode(ADDR[i], INPUT);
  }
  pinMode(CLK, OUTPUT);
  pinMode(RW, INPUT);
}


bool clk = 0;
int clk_period = 2000;

unsigned char bus_addr = 0;
unsigned char bus_data = 0;

#define R 1
#define W 0
bool bus_rw = 0;


void loop() {

  clk = !clk;
  digitalWrite(CLK, clk);
  if(clk) {
    Serial.println("Clock up");
  } else {
    Serial.println("Clock down");
  }

  delay(clk_period/2);
  readAddr();

  if(bus_rw == R) {
    unsigned char rom[] = {
      0xAD, 0x09, 0x00, // $0009 -> A
      0x6D, 0x0A, 0x00, // A = A + $000A
      0x8D, 0x0B, 0x00, // A -> $000B
      0x28,             // $0009
      0x02,             // $000A
      0x00,             // $000B
      0x00, 0x00        // (RV) $FFFC $FFFD
    };
    unsigned char data = rom[bus_addr];
    writeData(data);
    print(bus_addr, bus_rw, data);
  } else {
    readData();
    print(bus_addr, bus_rw, bus_data);
  }
  
  delay(clk_period/2);
}


void readAddr() {

  bus_addr = 0;
  for(int i=0; i<4; i++) {
    bus_addr += digitalRead(ADDR[i]) << i;
  }

  bus_rw = digitalRead(RW);
}

void readData() {

  for(int i=0; i<8; i++) {
    pinMode(DATA[i], INPUT);
  }

  bus_data = 0;
  for(int i=0; i<8; i++) {
    bus_data += digitalRead(DATA[i]) << i;
  }
}

void writeData(unsigned char data) {

  for(int i=0; i<8; i++) {
    pinMode(DATA[i], OUTPUT);
  }

  for(int i=0; i<8; i++) {
    digitalWrite(DATA[i], data & 1<<i);
  }
}

void print(unsigned char addr, bool rw, unsigned char data) {

  char output[25];
  sprintf(output, " %01x  %c  %02x", addr, rw ? 'R' : 'W', data);
  Serial.println(output);
}












