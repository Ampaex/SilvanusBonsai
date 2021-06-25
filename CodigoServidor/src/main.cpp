#include "red.h"
#include "servidor.h"
#include "pantalla.h"


unsigned int nodoMostrado = 0;
int tamanoPrevio = getdatosNodos().size();
int pantallaActual = 0;

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
}

void loop() {
  atiendeServidorHttp();
  atiendeDNS();
  delay(200);

  if(!getdatosNodos().isNull())
  {
    limpiaPantalla();
    String clave = getListaNombreNodos()[pantallaActual];
    muestraNodo(clave.c_str(), getdatosNodos()[clave]["temperaturaht"], getdatosNodos()[clave]["humedadht"],getdatosNodos()[clave]["humedadSUST"],
    getdatosNodos()[clave]["luminosidad"]);
    if(pantallaActual<getdatosNodos().size()-1){
      pantallaActual++;
    }else{
      pantallaActual = 0;
    }
  }

  //Realiza la función de espera para evitar que cambie la pantalla rápidamente
  int contador = 0;
  while(contador<10){
    atiendeServidorHttp();
    atiendeDNS();
    delay(200);
    contador++;
  }
}