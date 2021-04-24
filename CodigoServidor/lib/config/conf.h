#ifndef CONF_H
    #define CONF_H
    #include <Arduino.h>
    #include <ESP8266WiFi.h>

    //Modo depuración, activa o desactiva la salida del puerto serie
    #define DEBUG


    //////////////////////CONFIGURACIÓN WIFI//////////////////////////
    //Credenciales del punto de acceso
    #define SSID "Jazz54w"
    #define CONTRASENA "A34r87puIZ"


    //////////////////////CONFIGURACIÓN RELÉ//////////////////////////
    #define PIN_RELE D1


    //////////////////////CONFIGURACIÓN HT//////////////////////////
    #include <Wire.h>
    #include "AHT10.h"
    #define PIN_SCL_HT D2
    #define PIN_SDA_HT D3


    //////////////////////CONFIGURACIÓN SUSTRATO//////////////////////////


    //////////////////////CONFIGURACIÓN LUMINOSIDAD//////////////////////////
    

#endif