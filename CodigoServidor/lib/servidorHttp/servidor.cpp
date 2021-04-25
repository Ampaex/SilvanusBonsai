#include "servidor.h"
#include "paginaPrincipal.h"

ESP8266WebServer server(80);

void inicializaServidorHttp()
{
    // Receptor para raíz
    server.on("/", receptorRaiz);

    // Receptor para URL desconocida
    server.onNotFound(receptorNoEncontrado);

    // Iniciar servidor
    server.begin();

    //#ifdef DEBUG
        Serial.println("Servidor HTTP iniciado");
    //#endif
}

void atiendeServidorHttp(){
      server.handleClient();
}

void receptorRaiz()
{
   server.send(200, "text/html", paginaPrincipal());
}

void receptorNoEncontrado()
{
   server.send(404, "text/html", ("<meta charset=\"utf-8\"><h1 style=\"text-align:center\">Página no encontrada</h1>"));
}