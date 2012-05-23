
int PIN_SHIFT_CLK = 2;
int PIN_LATCH_CLK = 3;
int PIN_DATA = 6;

void setup() {
  pinMode(PIN_SHIFT_CLK, OUTPUT);
  pinMode(PIN_LATCH_CLK, OUTPUT);
  pinMode(PIN_DATA, OUTPUT);
  
  digitalWrite(PIN_SHIFT_CLK, LOW);
  digitalWrite(PIN_LATCH_CLK, LOW);
  digitalWrite(PIN_DATA, LOW);
  
  clearAll();
  set(0xaa);
}

void clearAll() {
  setAll(LOW);
}

void setAll(int value) {
  digitalWrite(PIN_DATA, value);
  for (int i = 0; i < 8; i++) {
    hitHiLow(PIN_SHIFT_CLK);
  }
  hitHiLow(PIN_LATCH_CLK);
}

void set(unsigned char data) {
  for (int i = 0; i < 8; i++) {
    int writeVal = (data & (1 << i)) ? HIGH : LOW;
    setDataPin(writeVal);
    hitHiLow(PIN_SHIFT_CLK);
  }
  hitHiLow(PIN_LATCH_CLK);
}

void setDataPin(int value) {
  digitalWrite(PIN_DATA, value);
}

void hitHiLow(int pin) {
  digitalWrite(pin, HIGH);
  digitalWrite(pin, LOW);
}

void loop() {
  
}
