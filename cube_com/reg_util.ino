// reg_util

#include "pins.h"

// shift 0's into all registers
// latch
void clearAllOutputs() {
  clearReg(PIN_DATA_0);
  clearReg(PIN_DATA_1);
  clearReg(PIN_DATA_2);
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
// nolatch
void setDataPin(int pin, int value) {
  digitalWrite(pin, value);
}

// toggle the shift clock high and low once
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
