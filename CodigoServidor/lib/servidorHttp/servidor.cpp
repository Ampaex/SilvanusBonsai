#include "servidor.h"
#include "paginaPrincipal.h"
#include "paginaMensaje.h"

ESP8266WebServer server(80);
StaticJsonDocument<260> configuracionRegistrada;
DynamicJsonDocument datosNodos(200*MAX_DATOS_NODOS);
String listaNombreNodos[MAX_DATOS_NODOS];

DynamicJsonDocument getdatosNodos()
{
    return datosNodos;
}

String* getListaNombreNodos()
{
    return listaNombreNodos;
}

void inicializaServidorHttp()
{
    // Receptor para raíz
    server.on("/", receptorRaiz);

    // Receptor para URL desconocida
    server.onNotFound(receptorNoEncontrado);

    // Receptor para registrar un nodo
    server.on("/registranodo",receptorRegistro);
    // Receptor para obtener el nodo registrado almacenado
    server.on("/obtenerconfiguracion",receptorObtenerConfiguracion);
    // Receptor para obtener el nodo registrado almacenado
    server.on("/hayconfiguracion",receptorCompruebaConfiguracion);
    //Receptor para recibir los datos de sensores
    server.on("/sensor",receptorSensor);
    //Receptor para obtener más detalles de sensores
    server.on("/selnodo",receptorSelnodo);

    configuracionRegistrada.clear();

    // Iniciar servidor
    server.begin();

    //#ifdef DEBUG
        Serial.println("Servidor HTTP iniciado");
    //#endif
}

void atiendeServidorHttp()
{
      server.handleClient();
}

void receptorRegistro()
{
    //Comprueba que existan todos los nodos
    if(!server.hasArg("idNodo") || !server.hasArg("luminosidad") || !server.hasArg("hluminosidad") || !server.hasArg("temp1")
        || !server.hasArg("temp2") || !server.hasArg("hum1") || !server.hasArg("hum2") || !server.hasArg("sust") || !server.hasArg("bomb"))
    {
        server.send(406, "text/plain", "Configuración inválida, faltan campos");
        return;
    }

    //Comprueba que no hayan campos vacíos
    if (server.arg("idNodo") == "" || server.arg("temp1") == "" || server.arg("temp2") == "" || server.arg("hum1") == "" || server.arg("hum2") == "")
    {
        server.send(406, "text/plain", "Configuración inválida, el nombre, las temperaturas o las humedades faltan");
        return;
    }

    configuracionRegistrada.clear();
    configuracionRegistrada["idNodo"] = server.arg("idNodo");
    configuracionRegistrada["luminosidad"] = server.arg("luminosidad");
    configuracionRegistrada["hluminosidad"] = server.arg("hluminosidad");
    configuracionRegistrada["temp1"] = server.arg("temp1");
    configuracionRegistrada["temp2"] = server.arg("temp2");
    configuracionRegistrada["hum1"] = server.arg("hum1");
    configuracionRegistrada["hum2"] = server.arg("hum2");
    configuracionRegistrada["sust"] = server.arg("sust");
    configuracionRegistrada["bomb"] = server.arg("bomb");

    String serializado;
    serializeJsonPretty(configuracionRegistrada, serializado);

    server.send(200, "text/html", paginaMensaje("Nuevo nodo registrado: <br><textarea>"+serializado+"</textarea>"));

}

void receptorObtenerConfiguracion()
{
    String serializado;
    if(configuracionRegistrada.isNull())
    {
        server.send(204, "text/plain", "Sin configuracion registrada");
        return;
    }
    else
    {
        serializeJson(configuracionRegistrada, serializado);
        server.send(200, "text/plain", serializado);
        configuracionRegistrada.clear();
        return;
    }
}

//TODO: Comprobar si hay configuración registrada
void receptorCompruebaConfiguracion()
{
    if(!configuracionRegistrada.isNull())
    {
        server.send(200);
    }
    else{
        server.send(204);
    }
}

void receptorSensor()
{
    if(!server.hasArg("idNodo") || !server.hasArg("temperaturaht") || !server.hasArg("humedadht") || !server.hasArg("humedadSUST") 
    || !server.hasArg("luminosidad"))
    {
        server.send(406, "text/plain", "Faltan campos");
        return;
    }
    //Actualizacion de la lista de nodos
    //Comprueba si ya existe el nombre en la lista
    boolean existe = false;
    for(int n = 0; n<MAX_DATOS_NODOS;n++)
    {
        if(listaNombreNodos[n]==server.arg("idNodo"))
        {
            existe = true;
            break;
        }
    }
    //Si no existe lo añade en el primer espacio vacío
    if(!existe)
    {
        for(int n = 0; n<MAX_DATOS_NODOS;n++)
        {
            if(listaNombreNodos[n]=="")
            {
                listaNombreNodos[n] = server.arg("idNodo");
                break;
            }
        }
    }
    
    datosNodos[server.arg("idNodo")]["temperaturaht"] = server.arg("temperaturaht");
    datosNodos[server.arg("idNodo")]["humedadht"] = server.arg("humedadht");
    datosNodos[server.arg("idNodo")]["humedadSUST"] = server.arg("humedadSUST");
    datosNodos[server.arg("idNodo")]["luminosidad"] = server.arg("luminosidad");

    server.send(200, "plain/text", "Recibido");
    #ifdef DEBUG
        Serial.println("Datos del nodo '" + (String)server.arg("idNodo") + "' recibidos");
        serializeJsonPretty(datosNodos, Serial);
        Serial.println("Lista de sensores con información recibida:");
        for(int i = 0;i<MAX_DATOS_NODOS;i++)
        {
            Serial.println(listaNombreNodos[i]);
        }
    #endif

}

void receptorRaiz()
{
    //Página sin configuración registrada
    if(configuracionRegistrada.isNull())
    {
        Serial.println("Mostrando página inicial sin registro");
        server.send(200, "text/html", paginaPrincipal("",datosNodos));
    }
    //Si se encuentra algún registro lo muestra
    else
    {
        Serial.println("Mostrando pagina inicial con registro");
        server.send(200, "text/html", paginaPrincipal(configuracionRegistrada["idNodo"],datosNodos));
    }
}

void receptorNoEncontrado()
{
   server.send(404, "text/html", ("<meta charset=\"utf-8\"><h1 style=\"text-align:center\">Página no encontrada</h1>"));
}

void receptorSelnodo()
{
    if(server.hasArg("nodoelegido") && !datosNodos[server.arg("nodoelegido")].isNull())
    {
        String cadena;
        String nombre = server.arg("nodoelegido");
        cadena += "Nombre del nodo: " + nombre + "<br>";
        cadena += "Temperatura ambiental: " + datosNodos[nombre]["temperaturaht"].as<String>() + "<br>";
        cadena += "Humedad ambiental: " + datosNodos[nombre]["humedadht"].as<String>() + "<br>";
        cadena += "Humedad del sustrato: " + datosNodos[nombre]["humedadSUST"].as<String>() + "<br>";
        cadena += "Luminosidad: " + datosNodos[nombre]["luminosidad"].as<String>() + "<br>";
        server.send(200, "text/html", paginaMensaje(cadena));
    }
}

