#include "red.h"
#include "servidor.h"
#include "pantalla.h"

void espera(unsigned int esperaMillis)
{
  unsigned long initMillis = millis();
  while(millis() - initMillis < esperaMillis){wdt_reset();};
}

void setup() {
  #ifdef DEBUG
    Serial.begin(921600);
  #endif
  creaPuntoWifi();
  inicializaServidorHttp();

  //Imagen de introducción
  inicializaPantalla();
  escenaIntro();
  delay(3000);
  limpiaPantalla();
  muestraNodo("Populus alba", 24, 60, 40, 25);
}

void loop() {
  atiendeServidorHttp();
  atiendeDNS();
  delay(200);
}