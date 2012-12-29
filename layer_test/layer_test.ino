#include <TimerOne.h>

// main.c

#define LAYER_MASK_0 0x01
#define LAYER_MASK_1 0x02
#define LAYER_MASK_2 0x04

#define LAYER_SELECT_0 A0
#define LAYER_SELECT_1 A1
#define LAYER_SELECT_2 A2
#define LAYER_GLOBAL_ENABLE 11

void setup() {
  pinMode(LAYER_SELECT_0, OUTPUT);
  pinMode(LAYER_SELECT_1, OUTPUT);
  pinMode(LAYER_SELECT_2, OUTPUT);
  pinMode(LAYER_GLOBAL_ENABLE, OUTPUT);
  
  setLayersEnabled(true);
  
  Timer1.initialize(125000);
  Timer1.attachInterrupt(layerIsr);
  
  Serial.begin(38400);
  
  Serial.println("Layer Test");
}

byte selectedLayer = 0;

void layerIsr() {
  selectedLayer++;
  
  setLayer(selectedLayer);
  
}

void loop() {
  analogWrite(LAYER_GLOBAL_ENABLE, 255);
  
}

void setLayer(int layer) {
  setLayersEnabled(false);
  setLayerSelectBits(layer);
  setLayersEnabled(true);
}

void setLayerSelectBits(int layer) {
  digitalWrite(LAYER_SELECT_0, layer & LAYER_MASK_0 ? HIGH : LOW);
  digitalWrite(LAYER_SELECT_1, layer & LAYER_MASK_1 ? HIGH : LOW);
  digitalWrite(LAYER_SELECT_2, layer & LAYER_MASK_2 ? HIGH : LOW);
}

void setLayersEnabled(boolean enabled) {
  digitalWrite(LAYER_GLOBAL_ENABLE, enabled ? HIGH : LOW);
}
