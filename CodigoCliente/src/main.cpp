#include "perifericos.h"
#include "red.h"

void setup() {
  #ifdef DEBUG
    Serial.begin(921600);
  #endif
  
  inicializaPerifericos();
  conectaWiFi();
}

void loop() {
  delay(2000);
}