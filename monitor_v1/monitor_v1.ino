
const int ADDR[] = {A0, A1, A2, A3};
const int CLK = 2;
bool change = false;


void setup() {
  
  Serial.begin(9600);
  while (!Serial);
  
  for(int i=0; i<4; i++) {
    pinMode(ADDR[i], INPUT);
  }
  pinMode(CLK, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(CLK), onClock, RISING);
}


void onClock() {
  change = !change;
}

bool previousChange = false;

void loop() {

  if(change != previousChange) {
    printAddr();
    previousChange = change;
  }
}

void printAddr() {
  for(int i=3; i>=0; i--) {
    Serial.print(digitalRead(ADDR[i]));
  }
  Serial.println();
}












