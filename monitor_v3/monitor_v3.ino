
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
  for(int i=0; i<8; i++) {
    pinMode(DATA[i], INPUT);
  }
  pinMode(RW, INPUT);

  pinMode(CLK, OUTPUT);
}


bool clk = 0;
int clk_period = 1000;


void loop() {

  clk = !clk;
  digitalWrite(CLK, clk);
  if(clk) {
    Serial.println("CLK 1");
  } else {
    Serial.println("CLK 0");
  }

  delay(clk_period/2);
  readBus();
  delay(clk_period/2);
}


void readBus() {

  unsigned char addr = 0;
  for(int i=0; i<4; i++) {
    addr += digitalRead(ADDR[i]) << i;
  }

  unsigned char data = 0;
  for(int i=0; i<8; i++) {
    data += digitalRead(DATA[i]) << i;
  }

  bool rw = digitalRead(RW);

  char output[25];
  sprintf(output, " %01x  %c  %02x", addr, rw ? 'R' : 'W', data);
  Serial.println(output);
}












