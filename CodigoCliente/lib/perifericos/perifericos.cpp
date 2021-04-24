#include "perifericos.h"

AHT10 sensorHT(AHT10_ADDRESS_0X38, AHT10_SENSOR);

//Llamada a la inicialización de todos los periféricos
void inicializaPerifericos(){
    pinMode(PIN_RELE, OUTPUT);
    pinMode(A0, INPUT);
    htBegin();

}

//////////////////////RELÉ//////////////////////////

//Establece el relé a 1
void activaRele(){
    digitalWrite(PIN_RELE, 1);
    #ifdef DEBUG
        Serial.println("Activando RELÉ");
    #endif
}

//Establece el relé a 0
void desactivaRele(){
    digitalWrite(PIN_RELE, 0);
    #ifdef DEBUG
        Serial.println("Desactivando RELÉ");
    #endif
}

////////////////////// HT //////////////////////////

//Inicialización del sensor de temperatura
void htBegin()
{
    if(sensorHT.begin(PIN_SDA_HT, PIN_SCL_HT) != true)
    {
        #ifdef DEBUG
            Serial.println("AHT10 no conectado o fallo al cargar los coeficientes de calibración");
        #endif
    }
}

//Lectura de la temperatura del sensor ht
float temperaturaHT()
{
    float ret = sensorHT.readTemperature();
    #ifdef DEBUG
        Serial.println("Lectura de temperatura HT: " + (String)ret + "ºC");
    #endif
    
    return ret;
}

//Lectura de la humedad del sensor ht
float humedadHT()
{
    float ret = sensorHT.readHumidity();
    #ifdef DEBUG
        Serial.println("Lectura de humedad HT: " + (String)ret + "%");
    #endif

    return ret;
}


////////////////////// SUSTRATO //////////////////////////

float humedadSUST()
{
    float ret = analogRead(A0);

    //Rango 725 - 1024
    ret = (-(ret - 1024) / 299) * 100;

    #ifdef DEBUG
        Serial.println("Lectura de humedad SUST: " + (String)ret + "%");
    #endif

    return ret;
}


////////////////////// LUMINOISIDAD //////////////////////////

float luminosidad()
{
    float ret = analogRead(A0);

    //Rango 0 - 1024
    ret = (ret / 1024) * 100;

    #ifdef DEBUG
        Serial.println("Lectura de luminosidad: " + (String)ret + "%");
    #endif

    return ret;
}