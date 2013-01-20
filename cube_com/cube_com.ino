
#include <stdlib.h>
#include "pins.h"
#include "layer.h"
#include <TimerOne.h>

#define BUFFER_A 0
#define BUFFER_B 1

#define FRAME_SIZE 8
#define BUFFER_LENGTH (FRAME_SIZE * FRAME_SIZE)

// global state
byte currentLayer = 0;
byte readBuffer = BUFFER_A;
byte writeBuffer = BUFFER_B;

// buffers
byte* frameBufferA;
byte* frameBufferB;


void setup() {
  // buffers
  frameBufferA = (byte*) malloc(BUFFER_LENGTH * sizeof(byte));
  frameBufferB = (byte*) malloc(BUFFER_LENGTH * sizeof(byte));
  
  // init outputs
  initPins();
  
  // init serial
  Serial.begin(115200);
  
  // initialize the timer interrupt
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

void swapBuffer() {
  if (readBuffer == BUFFER_A) {
    readBuffer = BUFFER_B;
    writeBuffer = BUFFER_A;
  }
  else {
    readBuffer = BUFFER_A;
    writeBuffer = BUFFER_B;
  }
}





