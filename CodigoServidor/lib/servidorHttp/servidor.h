#include "config.h"
#include <ESP8266WebServer.h>

void inicializaServidorHttp();
void atiendeServidorHttp();

//Receptores

void receptorRaiz();
void receptorNoEncontrado();
void receptorConfiguracion();