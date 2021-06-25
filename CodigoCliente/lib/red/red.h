#include "conf.h" //Configuración general
#include "perifericos.h"
#include <ArduinoJson.h>


void conectaWiFi();
bool compruebaConexion();

/////// CLIENTE HTTP ////////
void enviaSensores();
StaticJsonDocument<260>* obtenerConfiguracion();
bool hayConfiguracion();
StaticJsonDocument<260>* getConfiguracion();
void compruebaBomba();