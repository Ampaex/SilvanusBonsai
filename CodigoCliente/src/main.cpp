#include "perifericos.h"
#include "red.h"

void espera(int esperaMillis)
{
  unsigned long initMillis = millis();
  while(millis() - initMillis < esperaMillis){wdt_reset();};
}

void setup() {
  #ifdef DEBUG
    Serial.begin(921600);
  #endif
  
  inicializaPerifericos();
  conectaWiFi();
  espera(4000);
  obtenerConfiguracion();
}

void loop() {
  Serial.println("------------------------------------------------");
  delay(1000);
  humedadSUST();
  luminosidad();
}
