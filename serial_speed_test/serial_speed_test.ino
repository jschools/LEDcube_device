

long sequenceNum;
byte expectedValue;
boolean failure;

void setup() {
  Serial.begin(115200);
  
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  sequenceNum = 0;
  expectedValue = 0;
  failure = false;
}

void loop() {
  if (!failure) {
    int readVal = Serial.read();
    
    if (readVal != -1) {
      if (((byte) readVal) != expectedValue) {
        failure = true;
        digitalWrite(13, HIGH);
      }
      expectedValue++;
      sequenceNum++;
    }
  }
}
