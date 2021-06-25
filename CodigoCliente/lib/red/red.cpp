#include "red.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>


HTTPClient http;
WiFiClient wificlient;


//////////////////////////////Parámetros de configuración/////////////////////////////////////
//Se aplica una configuración por defecto por si el servidor no se encontrara operativo

//Datos almacenados en Json
//  "idNodo":       Identificador del sensor
//  "luminosidad":  A partir de qué nivel se considera iluminado (%)
//  "hluminosidad": Cuantas horas mínimas de sol diarias necesita (h)
//  "temp1":    Límite de temperatura de riesgo (ºC)
//  "temp2":    Límite de temperatura de riesgo (ºC)
//  "hum1":     Límite de humedad de riesgo (ºC)
//  "hum2":     Límite de humedad de riesgo (ºC)
//  "sust":     A partir de qué nivel se considera el sustrato húmedo (%)
//  "bomb":     Cuantos segundos ha de tener encendido el motor (s)
StaticJsonDocument<260> configuracion;
bool configuracionAplicada = false;


//Conecta el módulo wifi al punto establecido
void conectaWiFi()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, CONTRASENA);

    WiFi.setAutoReconnect(true);
    #ifdef DEBUG
        Serial.println("[WiFi]Conectando al punto de acceso " + (String)SSID);  
    #endif

    #if CONEXION_OBLIGATORIA
    Serial.print("Connecting...");
        while (!WiFi.isConnected())
        {
            delay(500);
            Serial.print(".");
        }
    #endif
    

}

//@return true si se encuentra conectado / false si no.
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

//Función para obtener una nueva configuración del servidor (llamar a esta función eliminará la configuración del servidor)
//@return Puntero a la configuracion
StaticJsonDocument<260>* obtenerConfiguracion()
{
    //Si todavía no tiene configuración la intenta obtener del servidor
    #if CONEXION_OBLIGATORIA
    while(!configuracionAplicada){
    #else
    if(!configuracionAplicada){
    #endif
        String contenidoURL = URL_SERVIDOR;
        contenidoURL += "/obtenerconfiguracion";

        //Si se encuentra conectado al WiFi y puede iniciar http se obtiene una configuración
        if(compruebaConexion() && http.begin(wificlient,contenidoURL))
        {
            // Enviar petición GET
            int respuestaHttp = http.GET();

            if (respuestaHttp>0) 
            {
                //Abortamos si no existe la configuración
                if(respuestaHttp == 200)
                {
                    String payload = http.getString();
                    deserializeJson(configuracion, payload);
                    configuracionAplicada = true;
                    #ifdef DEBUG
                        Serial.print("Respuesta HTTP a recepción de configuracion: ");
                        Serial.println(respuestaHttp);
                        Serial.print("Configuracion recogida");
                        String res = "-->";
                        serializeJson(configuracion, res);
                        Serial.println(res);
                    #endif
                }

            }
            else 
            {
                #ifdef DEBUG
                    Serial.print("Error (" + respuestaHttp);
                    Serial.println(") al obtener la configuracion");
                #endif
            }
            
            http.end();
        }

    }

    //Si la configuración sigue sin haberse aplicado, entonces se establece una por defecto
    if(!configuracionAplicada)
    {
        configuracion["idNodo"] = rand();
        configuracion["luminosidad"] = 50;
        configuracion["hluminosidad"] = 8;
        configuracion["temp1"] = 25;
        configuracion["temp2"] = 10;
        configuracion["hum1"] = 10;
        configuracion["hum2"] = 75;
        configuracion["sust"] = 20;
        configuracion["bomb"] = 5;
        configuracionAplicada = true;
    }

    return &configuracion;
    
}

//Comprueba si se dispone de una nueva configuración en el servidor
bool hayConfiguracion()
{
    String contenidoURL = URL_SERVIDOR;
    contenidoURL += "/hayconfiguracion";
    if(compruebaConexion() && http.begin(wificlient,contenidoURL))
    {
        // Enviar petición GET
        int respuestaHttp = http.GET();

        if (respuestaHttp==200) 
        {
            http.end();
            return true;
        }
        else http.end(); return false;
    }
    else return false;
}

void enviaSensores()
{
    String contenidoURL = URL_SERVIDOR;
    contenidoURL += "/sensor";
    contenidoURL += "?idNodo=" + configuracion["idNodo"].as<String>();
    contenidoURL += "&temperaturaht=" + (String)temperaturaHT();
    contenidoURL += "&humedadht=" + (String)humedadHT();
    contenidoURL += "&humedadSUST=" + (String)humedadSUST();
    contenidoURL += "&luminosidad=" + (String)luminosidad();

    Serial.println(contenidoURL);
    //Si se encuentra conectado al WiFi
    if(compruebaConexion() && http.begin(wificlient,contenidoURL))
    {
        // Send HTTP GET request
        int respuestaHttp = http.GET();

        if (respuestaHttp>0) 
        {
            #ifdef DEBUG
                Serial.print("Respuesta HTTP a envío de sensores: ");
                Serial.println(respuestaHttp);
                Serial.print("Payload: ");
                Serial.println(http.getString());
            #endif
        }
        else 
        {
            Serial.print("Error (" + respuestaHttp);
            Serial.println(") al enviar datos de sensores");
        }
        // Free resources
        http.end();
    }
}

StaticJsonDocument<260>* getConfiguracion()
{
    return &configuracion;
}

void compruebaBomba()
{
    if(humedadSUST() <= configuracion["sust"].as<float>())
    {
        activaRele();
        delay(configuracion["bomb"].as<int>()*1000);
        desactivaRele();
    }
}