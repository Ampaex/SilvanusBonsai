#include "red.h"
#include "servidor.h"
#include "pantalla.h"

void setup() {
  #ifdef DEBUG
    Serial.begin(921600);
  #endif
  //creaPuntoWifi();
  //inicializaServidorHttp();

  //Imagen de introducción
  inicializaPantalla();
  escenaIntro();
  delay(3000);
  limpiaPantalla();
}

void loop() {
  //atiendeServidorHttp();
  //atiendeDNS();
  
}