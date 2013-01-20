// reg_util

#include "pins.h"

#define LOWER_MASK 0x0f
#define UPPER_MASK 0xf0

// initializes all output pins to OUTPUT
// writes LOW to all output pins
// shifts 0's into all output registers
void initPins() {
  initPin(PIN_SHIFT_CLK);
  initPin(PIN_LATCH_CLK);
  initPin(PIN_ACTIVITY);
  
  initPin(PIN_DATA_0);
  initPin(PIN_DATA_1);
  initPin(PIN_DATA_2);
  initPin(PIN_DATA_3);
  initPin(PIN_DATA_4);
  initPin(PIN_DATA_5);
  initPin(PIN_DATA_6);
  initPin(PIN_DATA_7);
  
  initPin(PIN_LAYER_SEL_0);
  initPin(PIN_LAYER_SEL_1);
  initPin(PIN_LAYER_SEL_2);
  
  clearAllOutputs();
  
  setLayer(0);
  setGlobalEnable(true);
}

void initPin(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

void setGlobalEnable(boolean enabled) {
  digitalWrite(PIN_GLOBAL_ENABLE, enabled ? HIGH : LOW);
}

// write 'length' bytes across pins
// latch at end
void writeBytesToRegisters(byte* data, int length) {
  for (int i = 0; i < length; i++) {
    writeByteToRegisters(data[i]);
  }
  latch();
}

// set one byte across pins and shift
// no latch
void writeByteToRegisters(byte data) {
  byte lowerBits = data & LOWER_MASK;
  byte upperBits = data & UPPER_MASK;

  PORTD &= ~UPPER_MASK;
  PORTD |= upperBits;

  PORTB &= ~LOWER_MASK;
  PORTB |= lowerBits;

  shift();
}

void setLayerSelectBits(int layer) {
  digitalWrite(PIN_LAYER_SEL_0, layer & LAYER_MASK_0 ? HIGH : LOW);
  digitalWrite(PIN_LAYER_SEL_1, layer & LAYER_MASK_1 ? HIGH : LOW);
  digitalWrite(PIN_LAYER_SEL_2, layer & LAYER_MASK_2 ? HIGH : LOW);
}

void setLayer(int layer) {
  //setGlobalEnable(false);
  setLayerSelectBits(layer);
  //setGlobalEnable(true);
}

// shift 0's into all registers
// latch
void clearAllOutputs() {
  clearReg(PIN_DATA_0);
  clearReg(PIN_DATA_1);
  clearReg(PIN_DATA_2);
  clearReg(PIN_DATA_3);
  clearReg(PIN_DATA_4);
  clearReg(PIN_DATA_5);
  clearReg(PIN_DATA_6);
  clearReg(PIN_DATA_7);
}

// shift 0's into all registers at specified pin
// latch
void clearReg(int pin) {
  fillRegWithBoolean(pin, LOW);
}

// shift 'value' into all registers at specified pin
// latch
void fillRegWithBoolean(int pin, boolean value) {
  fillRegWithByte(pin, value ? 0xff : 0x00);
}

// shift a byte of data into a register at specified pin
// latch
void fillRegWithByte(int pin, byte data) {
  for (int i = 0; i < 8; i++) {
    int writeVal = (data & (1 << i)) ? HIGH : LOW;
    setDataPin(pin, writeVal);
    shift();
  }
  latch();
}

// set a pin to 'value'
// no latch
void setDataPin(int pin, int value) {
  digitalWrite(pin, value);
}

// toggle the shift clock high and low once
// no latch
void shift() {
  hitHiLow(PIN_SHIFT_CLK);
}

// toggle the latch register high and low once
void latch() {
  hitHiLow(PIN_LATCH_CLK);
}

// toggle the specified pin high and low once
void hitHiLow(int pin) {
  digitalWrite(pin, HIGH);
  digitalWrite(pin, LOW);
}
