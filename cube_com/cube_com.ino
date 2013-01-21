
#include <stdlib.h>
#include <TimerOne.h>
#include "pins.h"

#define CUBE_DIM 8
#define DISPLAY_BUFFER_LENGTH 64
#define FRAME_BUFFER_LENGTH 16

// global state
byte currentLayer = 0;

// buffers
byte* readDisplayBuffer;
byte* writeDisplayBuffer;

void setup() {
  // init outputs
  initPins();
  
  // buffers
  readDisplayBuffer = (byte*) malloc(DISPLAY_BUFFER_LENGTH * sizeof(byte));
  writeDisplayBuffer = (byte*) malloc(DISPLAY_BUFFER_LENGTH * sizeof(byte));  
  clearBuffer(readDisplayBuffer, DISPLAY_BUFFER_LENGTH);
  clearBuffer(writeDisplayBuffer, DISPLAY_BUFFER_LENGTH);
  
  // init serial
  Serial.begin(115200);
  
  // initialize the timer interrupt
  Timer1.initialize(600); // 500
  Timer1.attachInterrupt(layerIsr);
  
  for (int i = 0; i < 64; i++) {
    readDisplayBuffer[i] = 0xff;
  }
}

void loop() {
  //Serial.readBytes((char*) readDisplayBuffer, DISPLAY_BUFFER_LENGTH);
  //swapDisplayBuffer();
  delay(1);
}

void layerIsr() { 
  currentLayer++;
  currentLayer %= CUBE_DIM;
  
  writeLayerBytesToRegisters(readDisplayBuffer, currentLayer);
  
  setGlobalEnable(false);
  latch();
  setLayer(currentLayer);
  setGlobalEnable(true);
}

void clearBuffer(byte* buffer, int length) {
  for (int i = 0; i < length; i++) {
    buffer[i] = 0;
  }
}

void writeLayerBytesToRegisters(byte* displayBuffer, int layer) {
  int offset = layer * CUBE_DIM;
  byte* layerBuffer = displayBuffer + offset;
  writeBytesToRegisters(layerBuffer, CUBE_DIM);
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

void swapDisplayBuffer() {
  byte* tmp = readDisplayBuffer;
  readDisplayBuffer = writeDisplayBuffer;
  writeDisplayBuffer = tmp;
}





