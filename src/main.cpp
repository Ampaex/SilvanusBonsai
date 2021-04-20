#include <Arduino.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  delay(2000);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}