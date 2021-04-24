#include "red.h"

void conectaWiFi()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, CONTRASENA);

    WiFi.setAutoReconnect(true);
    #ifdef DEBUG
        Serial.println("[WiFi]Conectando al punto de acceso " + (String)SSID);  
    #endif


}

bool compruebaConexion()
{   
    if(WiFi.isConnected()){
        #ifdef DEBUG
            Serial.println("[COMPROBACIÓN WiFi / MODO ESTACIÓN] Se encuentra conectado al punto de acceso "  + (String)SSID);
            Serial.println("IP:" + WiFi.localIP().toString());
        #endif
        return 1;
    }
    else
    {
        #ifdef DEBUG
            Serial.println("[COMPROBACIÓN WiFi]No se encuentra conectado al punto de acceso");
            Serial.println("IP:" + WiFi.localIP().toString());
        #endif
        return 0;
    }
}
