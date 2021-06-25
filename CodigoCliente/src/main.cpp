#include "perifericos.h"
#include "red.h"
#include <EEPROM.h>
#include <StreamUtils.h>

int confGuardada = 0;

void espera(unsigned int esperaMillis)
{
  unsigned long initMillis = millis();
  while(millis() - initMillis < esperaMillis){wdt_reset();};
}

void setup() {
  #ifdef DEBUG
    Serial.begin(921600);
  #endif

  //Iniciamos la EEPROM
  EEPROM.begin(512);

  //El primer byte indica si hay una configuración guardada
  confGuardada = EEPROM.read(0);
  #ifdef DEBUG
    if(confGuardada)Serial.println("Detectada configuración en EEPROM");
  #endif

  //Stream dedicado a la configuración
  EepromStream eepromStream(1, 512);

  inicializaPerifericos();
  conectaWiFi();

  //Indica si hay una configuración en linea.
  bool hayconfiguracion = hayConfiguracion();

  //Se procede a comprobar todas las opciones posibles de configuraciones local y en línea.
  if(confGuardada && hayconfiguracion)
  {
    #ifdef DEBUG
      Serial.println("#Se dispone de una configuracion pero se va a descargar una nueva del servidor");
    #endif
    serializeJson(*obtenerConfiguracion(), eepromStream);
    EEPROM.write(0,1); //Pone la bandera que indica que hay configuracion guardada en alto
  }
  else if(!confGuardada && hayconfiguracion)
  {
    #ifdef DEBUG
      Serial.println("#No se dispone de una configuracion, se va a descargar una nueva del servidor");
    #endif
    serializeJson(*obtenerConfiguracion(), eepromStream);
    EEPROM.write(0,1); //Pone la bandera que indica que hay configuracion guardada en alto
  }
  else if(!confGuardada && !hayconfiguracion)
  {
    #ifdef DEBUG
      Serial.print("#No se dispone de una configuracion local, se procede a ");
      if(CONEXION_OBLIGATORIA) Serial.print("esperar a la conexión");
      else Serial.print("continuar con el programa en configuración por defecto");
    #endif
    serializeJson(*obtenerConfiguracion(), eepromStream);
    EEPROM.write(0,1); //Pone la bandera que indica que hay configuracion guardada en alto
  }
  else if (confGuardada && !hayconfiguracion)
  {
    #ifdef DEBUG
      Serial.print("#Se dispone de una configuracion local y ninguna en línea, se utiliza la local");
    #endif
    deserializeJson(*getConfiguracion(), eepromStream);
    EEPROM.write(0,1); //Pone la bandera que indica que hay configuracion guardada en alto
  }

  #ifdef DEBUG
    Serial.println("Configuración actual:");
    serializeJsonPretty(*getConfiguracion(),Serial);
  #endif

  EEPROM.commit();
  

}

void loop() {
  Serial.println("------------------------------------------------");
  delay(3000);
  enviaSensores();
  compruebaBomba();
  ESP.deepSleep(10e6);
}
