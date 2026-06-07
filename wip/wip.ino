
const int CLK = D2;


void setup() {
  
  Serial.begin(9600);
  while (!Serial);
  
  pinMode(CLK, OUTPUT);
}


bool clk = 0;
int clk_halfperiod = 1000;


void loop() {

  clk = !clk;
  digitalWrite(CLK, clk);
  if(clk) {
    Serial.println("CLK 1");
  } else {
    Serial.println("CLK 0");
  }

  delay(clk_halfperiod/2);
  delay(clk_halfperiod/2);
}