#include "servidor.h"
#include "paginaPrincipal.h"
#include <ArduinoJson.h>

ESP8266WebServer server(80);

void inicializaServidorHttp()
{
    // Receptor para raíz
    server.on("/", receptorRaiz);

    // Receptor para URL desconocida
    server.onNotFound(receptorNoEncontrado);

    // Receptor para un nodo que busca una configuración
    server.on("/configuracion",receptorConfiguracion);

    // Iniciar servidor
    server.begin();

    //#ifdef DEBUG
        Serial.println("Servidor HTTP iniciado");
    //#endif
}

void atiendeServidorHttp(){
      server.handleClient();
}

void receptorConfiguracion()
{
    if(server.hasArg("idNodo") && server.arg("idNodo") == "nuevo"){
        String ret;
        StaticJsonDocument<300> configuracion;
        configuracion["idNodo"] = "nodo" + (String)rand();
        
        serializeJson(configuracion, ret);
        server.send(200, "text/plain", ret);
    }

}

void receptorRaiz()
{
   server.send(200, "text/html", paginaPrincipal());
}

void receptorNoEncontrado()
{
   server.send(404, "text/html", ("<meta charset=\"utf-8\"><h1 style=\"text-align:center\">Página no encontrada</h1>"));
}