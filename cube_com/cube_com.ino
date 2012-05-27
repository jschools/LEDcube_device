// simple_test_3

#include "pins.h"

void setup() {
  // init serial
  Serial.begin(115200);
  
  // init outputs
  initPins();
}

void loop() {
  takeCommandFromSerial();
  delay(1);
}

void takeCommandFromSerial() {
  int readVal = Serial.read();
  byte b = 0x00;
  switch (readVal) {
  case 's':
    shift();
    latch();
    break;
  case '1':
    b = 0xff;
    writeBytesToRegisters(&b, 1);
    break;
  case '0':
    b = 0x00;
    writeBytesToRegisters(&b, 1);
    break;
  case 'p':
    delay(10);
    break;
  default:
    break;
  }
}
