#include "red.h"

IPAddress ip(192, 168, 3, 1);
IPAddress gateway(192, 168, 3, 1);
IPAddress subnet(255, 255, 255, 0);

DNSServer dnsServer;

void creaPuntoWifi()
{
    WiFi.mode(WIFI_AP);

    #ifdef DEBUG
    Serial.println("[WiFi]Estableciendo el punto de acceso " + (String)SSID); 
    #endif

    //Establecer i p estática
    if(USAR_IP_ESTATICA)
    {
        #ifdef DEBUG
            Serial.println("USANDO IP ESTÁTICA");
        #endif
        WiFi.softAPConfig(ip, gateway, subnet);
    }

    WiFi.softAP(SSID, CONTRASENA);

    #ifdef DEBUG
        Serial.println("Punto de acceso establecido");
        Serial.println("SSID: " + (String)SSID);
        Serial.print("IP:");
        Serial.println(WiFi.softAPIP());
    #endif
    
    dnsServer.start(DNS_PORT, "silvanus", WiFi.softAPIP());

}

void atiendeDNS(){
    dnsServer.processNextRequest();
}