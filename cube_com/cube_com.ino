// simple_test_3

#include "pins.h"

void setup() {
  Serial.begin(115200);
  
  pinMode(PIN_SHIFT_CLK, OUTPUT);
  pinMode(PIN_LATCH_CLK, OUTPUT);
  pinMode(PIN_ACTIVITY, OUTPUT);
  digitalWrite(PIN_SHIFT_CLK, LOW);
  digitalWrite(PIN_LATCH_CLK, LOW);
  digitalWrite(PIN_ACTIVITY, LOW);
  
  for (int pin = PIN_DATA_0; pin <= PIN_DATA_7; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }
  
  clearAllOutputs();
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
