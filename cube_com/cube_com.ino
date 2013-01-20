
#include <stdlib.h>
#include "pins.h"
#include "layer.h"
#include <TimerOne.h>

#define DISPLAY_BUFFER_A 0
#define DISPLAY_BUFFER_B 1

#define DISPLAY_BUFFER_LENGTH 64
#define FRAME_BUFFER_LENGTH 16


// global state
byte currentLayer = 0;
byte readBuffer = DISPLAY_BUFFER_A;
byte writeBuffer = DISPLAY_BUFFER_B;
byte readFrameIdx;
byte writeFrameIdx;

// buffers
byte* displayBufferA;
byte* displayBufferB;

void setup() {
  // buffers
  displayBufferA = (byte*) calloc(DISPLAY_BUFFER_LENGTH, sizeof(byte));
  displayBufferA = (byte*) calloc(DISPLAY_BUFFER_LENGTH, sizeof(byte));
  
  // init outputs
  initPins();
  
  // init serial
  Serial.begin(115200);
  
  // initialize the timer interrupt
  Timer1.initialize(500);
  Timer1.attachInterrupt(layerIsr);
}

void loop() {
  
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

void swapBuffer() {
  if (readBuffer == DISPLAY_BUFFER_A) {
    readBuffer = DISPLAY_BUFFER_B;
    writeBuffer = DISPLAY_BUFFER_A;
  }
  else {
    readBuffer = DISPLAY_BUFFER_A;
    writeBuffer = DISPLAY_BUFFER_B;
  }
}





