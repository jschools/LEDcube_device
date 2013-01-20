
#include "pins.h"
#include "layer.h"
#include <TimerOne.h>

volatile unsigned char currentLayer = 0;

void setup() {
  // init serial
  Serial.begin(115200);
  
  // init outputs
  initPins();
  
  Timer1.initialize(500);
  Timer1.attachInterrupt(layerIsr);
}

void loop() {
  takeCommandFromSerial();
  //currentLayer++;
  //setLayer(currentLayer);
  //delay(100);
}

void layerIsr() {
  currentLayer++;
  setLayer(currentLayer);
}

void takeCommandFromSerial() {
  int readVal = Serial.read();
  byte b = 0x00;
  switch (readVal) {
  case '1':
    b = 0xff;
    writeBytesToRegisters(&b, 1);
    break;
  case '0':
    b = 0x00;
    writeBytesToRegisters(&b, 1);
    break;
  default:
    break;
  }
}
