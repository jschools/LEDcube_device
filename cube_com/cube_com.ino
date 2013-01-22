
#define CUBE_DIM 8
#define DISPLAY_BUFFER_LENGTH 64
#define FRAME_BUFFER_LENGTH 16

#include <stdlib.h>
#include <TimerOne.h>
#include "pins.h"

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
  Timer1.initialize(600); // 600
  Timer1.attachInterrupt(layerIsr);
  
  // draw some initial graphics
  drawInitialGraphics();
}

int writeIdx = 0;

void loop() {
  int in = Serial.read();
  if (in >= 0) {
    writeDisplayBuffer[writeIdx] = (byte) in;
    writeIdx++;
    if (writeIdx == DISPLAY_BUFFER_LENGTH) {
      writeIdx = 0;
      swapDisplayBuffer();
    }   
  }
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
  byte reversedLayer = CUBE_DIM - layer - 1;
  int offset = reversedLayer * CUBE_DIM;
  byte* layerBuffer = displayBuffer + offset;
  writeBytesToRegisters(layerBuffer, CUBE_DIM);
}

void swapDisplayBuffer() {
  byte* tmp = readDisplayBuffer;
  readDisplayBuffer = writeDisplayBuffer;
  writeDisplayBuffer = tmp;
}

void drawInitialGraphics() {
  for (int i = 0; i < 8; i++) {
    setPixel(readDisplayBuffer, i, 0, 0, true);
  }
  for (int i = 0; i < 8; i++) {
    setPixel(readDisplayBuffer, i, 0, 7, true);
  }
  for (int i = 0; i < 8; i++) {
    setPixel(readDisplayBuffer, i, 7, 0, true);
  }
  for (int i = 0; i < 8; i++) {
    setPixel(readDisplayBuffer, i, 7, 7, true);
  }
  
  for (int i = 0; i < 8; i++) {
    setPixel(readDisplayBuffer, 0, i, 0, true);
  }
  for (int i = 0; i < 8; i++) {
    setPixel(readDisplayBuffer, 0, i, 7, true);
  }
  for (int i = 0; i < 8; i++) {
    setPixel(readDisplayBuffer, 7, i, 0, true);
  }
  for (int i = 0; i < 8; i++) {
    setPixel(readDisplayBuffer, 7, i, 7, true);
  }
  
  for (int i = 0; i < 8; i++) {
    setPixel(readDisplayBuffer, 0, 0, i, true);
  }
  for (int i = 0; i < 8; i++) {
    setPixel(readDisplayBuffer, 0, 7, i, true);
  }
  for (int i = 0; i < 8; i++) {
    setPixel(readDisplayBuffer, 7, 0, i, true);
  }
  for (int i = 0; i < 8; i++) {
    setPixel(readDisplayBuffer, 7, 7, i, true);
  }
}




