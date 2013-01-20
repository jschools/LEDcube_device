// simple_test_3

#include "pins.h"
#include "layer.h"

volatile unsigned char currentLayer = 0;

void setup() {
  // init serial
  Serial.begin(115200);
  
  // init outputs
  initPins();
  
  setLayer(currentLayer);
}

void loop() {
  takeCommandFromSerial();
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
  case '.':
    currentLayer++;
    setLayer(currentLayer);
    break;
  case 'p':
    delay(10);
    break;
  default:
    break;
  }
}
