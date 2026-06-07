
const int ADDR[] = {A0,A1,A2,A3};  // LSB to MSB
const int DATA[] = {D10,D9,D8,D7, D6,D5,D4,D3}; // LSB to MSB
const int CLK = D2;
const int RWB = D12;
const int RESB = D11;


int clk_halfperiod = 1000;


typedef uint8_t uint8;


void setup() {
  
  Serial.begin(9600);
  while (!Serial);

  for(int i=0; i<4; i++) {
    pinMode(ADDR[i], INPUT);
  }
  for(int i=0; i<8; i++) {
    pinMode(DATA[i], OUTPUT);
  }
  pinMode(CLK, OUTPUT);
  pinMode(RWB, OUTPUT);
  pinMode(RESB, OUTPUT);

  delay(2000);
  
  const int DDRB = 0x02;
  const int PORTB = 0x00;
  const int DDRA = 0x03;
  const int PORTA = 0x01;

  reset();
  sendByte(DDRB, 0xFF);
  sendByte(PORTB, 0x02);
  // sendByte(0x02, 0x00);
  // readByte(0x00);
}


void clock() {

  for(int i=0; i<5; i++) {
    digitalWrite(CLK, HIGH);
    delay(clk_halfperiod);
    digitalWrite(CLK, LOW);
    delay(clk_halfperiod);
    Serial.print(".");
  }
}


void reset() {

  Serial.print("Resetting");
  digitalWrite(RESB, LOW);
  clock();
  digitalWrite(RESB, HIGH);
  Serial.println("done");
}


void sendByte(uint8 addr, uint8 byte) {

  Serial.print("Sending ");
  Serial.print(byte, HEX);
  Serial.print(" to ");
  Serial.print(addr, HEX);

  for(int i=0; i<4; i++) {
    digitalWrite(ADDR[i], (addr >> i) & 1);
  }
  digitalWrite(RWB, 0);

  for(int i=0; i<8; i++) {
    digitalWrite(DATA[i], (byte >> i) & 1);
  }
  clock();
  Serial.println("done");
}



void readByte(uint8 addr) {

  Serial.print("Reading from ");
  Serial.print(addr, HEX);

  for(int i=0; i<4; i++) {
    digitalWrite(ADDR[i], (addr >> i) & 1);
  }
  digitalWrite(RWB, 1);

  clock();
  
  for(int i=0; i<8; i++) {
    Serial.print(digitalRead(DATA[i]));
  }
  Serial.println("");
}


void loop() {
}