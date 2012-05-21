// simple_test_3

#include "pins.h"

void setup() {
  Serial.begin(9600);
  
  pinMode(PIN_SHIFT_CLK, OUTPUT);
  pinMode(PIN_LATCH_CLK, OUTPUT);
  pinMode(PIN_ACTIVITY, OUTPUT);
  pinMode(PIN_DATA_0, OUTPUT);
  pinMode(PIN_DATA_1, OUTPUT);
  
  digitalWrite(PIN_SHIFT_CLK, LOW);
  digitalWrite(PIN_LATCH_CLK, LOW);
  digitalWrite(PIN_ACTIVITY, LOW);
  digitalWrite(PIN_DATA_0, LOW);
  digitalWrite(PIN_DATA_1, LOW);
  
  clearAllOutputs();
}

unsigned char num = 0;
void loop() {
  fillRegWithByte(PIN_DATA_0, 0xff);
  delay(500);
  fillRegWithByte(PIN_DATA_0, 0x00);
  delay(500);
  hitHiLow(PIN_ACTIVITY);
}
