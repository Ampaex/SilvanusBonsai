#include "conf.h"
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

void inicializaServidorHttp();
void atiendeServidorHttp();

//Receptores

void receptorRaiz();
void receptorNoEncontrado();
void receptorRegistro();
void receptorObtenerConfiguracion();
void receptorSensor();
void receptorSelnodo();
void receptorCompruebaConfiguracion();

DynamicJsonDocument getdatosNodos();
String* getListaNombreNodos();
