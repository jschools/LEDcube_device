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
  
  Serial.begin(38400);
  
  Serial.println("Layer Test");
}

int delayTime = 1000;
int pwm = 0;

void loop() {
  int in = Serial.read();
  
  if (in >= '0' && in <= '7') {
    setLayerSelectBits(in - '0');
  }

/*
  setLayersEnabled(true);
  delay(delayTime);
  setLayersEnabled(false);
  delay(delayTime);
*/

  delay(delayTime);
  analogWrite(LAYER_GLOBAL_ENABLE, pwm);
  pwm += 32;

}

void switchToLayerSafe(int layer) {
    setLayersEnabled(false);
    setLayerSelectBits(layer);
    setLayersEnabled(true);
}

void setLayerSelectBits(int layer) {
  if (layer < 0 || layer > 7) {
    return;
  }
  
  digitalWrite(LAYER_SELECT_0, layer & LAYER_MASK_0 ? HIGH : LOW);
  digitalWrite(LAYER_SELECT_1, layer & LAYER_MASK_1 ? HIGH : LOW);
  digitalWrite(LAYER_SELECT_2, layer & LAYER_MASK_2 ? HIGH : LOW);
}

void setLayersEnabled(boolean enabled) {
  digitalWrite(LAYER_GLOBAL_ENABLE, enabled ? HIGH : LOW);
}
