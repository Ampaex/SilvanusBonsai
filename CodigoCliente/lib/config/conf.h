#ifndef CONF_H
    #define CONF_H
    #include <Arduino.h>
    #include <ESP8266WiFi.h>

    //Modo depuración, activa o desactiva la salida del puerto serie
    #define DEBUG


    //////////////////////CONFIGURACIÓN WIFI//////////////////////////
    //Credenciales del punto de acceso
    #define SSID "SilvanusOrigen"
    #define CONTRASENA "puntoDeAcceso"
    #define CONEXION_OBLIGATORIA true       //Indica si es obligatorio que tenga que haber establecido una conexión

    #define URL_SERVIDOR "http://silvanus"


    //////////////////////CONFIGURACIÓN RELÉ//////////////////////////
    #define PIN_RELE D1


    //////////////////////CONFIGURACIÓN HT//////////////////////////
    #include <Wire.h>
    #include "AHT10.h"
    #define PIN_SCL_HT D2
    #define PIN_SDA_HT D3


    //////////////////////CONFIGURACIÓN MULTIPLEXOR//////////////////////////
    //Posiciones del multiplexor en las que se encuentra cada sensor
    #define SUST 0
    #define LUM 1
    #define BAT 2
    //Pines del multiplexor
    #define PIN_MUX0 D7
    #define PIN_MUX1 D6

    

#endif