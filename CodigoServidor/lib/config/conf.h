#ifndef CONF_H
    #define CONF_H
    #include <Arduino.h>
    #include <ESP8266WiFi.h>

    //Modo depuración, activa o desactiva la salida del puerto serie
    #define DEBUG

    //////////////////////CONFIGURACIÓN WIFI//////////////////////////
    //Credenciales de establecimiento del punto de acceso
    #define SSID "SilvanusOrigen"
    #define CONTRASENA "puntoDeAcceso"

    #define USAR_IP_ESTATICA true //Configuración de ip en red.cpp
    #define DNS_PORT 53

#endif