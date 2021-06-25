#include "perifericos.h"

AHT10 sensorHT(AHT10_ADDRESS_0X38, AHT10_SENSOR);
int entradaAnalogica = 3;

//Mínimas y máximas registradas [0]->mínimas [1]->máxima
int minMaxSust[2] = {1024,-1024};
int minMaxLum[2] = {1024,-1024};
int minMaxHum[2] = {1024,-1024};
float minMaxTemp[2] = {1024.0,-1024.0};

//Llamada a la inicialización de todos los periféricos
void inicializaPerifericos(){
    pinMode(PIN_RELE, OUTPUT);
    pinMode(D5,OUTPUT); //Pin transistor sust
    inicializaMultiplexor();
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

    //Control de máximos y mínimos
    if(minMaxTemp[1] < ret) minMaxTemp[1] = ret;
    if(minMaxTemp[0] > ret) minMaxTemp[0] = ret;

    #ifdef DEBUG
        Serial.println("Lectura de temperatura HT: " + (String)ret + "ºC");
        Serial.println("MaxTemp:" + (String)minMaxTemp[1] + "/MinTemp:" + (String)minMaxTemp[0]);
    #endif
    
    return ret;
}

//Lectura de la humedad del sensor ht
float humedadHT()
{
    float ret = sensorHT.readHumidity();

    //Control de máximos y mínimos
    if(minMaxHum[1] < ret) minMaxHum[1] = ret;
    if(minMaxHum[0] > ret) minMaxHum[0] = ret;

    #ifdef DEBUG
        Serial.println("Lectura de humedad HT: " + (String)ret + "%");
        Serial.println("MaxHum:" + (String)minMaxHum[1] + "/MinHum:" + (String)minMaxHum[0]);
    #endif

    return ret;
}


////////////////////// MULTIPLEXOR //////////////////////////

void inicializaMultiplexor()
{
    pinMode(PIN_MUX0,OUTPUT);
    pinMode(PIN_MUX1, OUTPUT);
    pinMode(A0, INPUT);
}
void seleccionaEntrada(int entrada)
{
    switch (entrada)
    {
        case 0:
            
            digitalWrite(D5,HIGH); //Pin enable activo en bajo
            digitalWrite(PIN_MUX0, 0);
            digitalWrite(PIN_MUX1, 0);
            break;
        case 1:
            digitalWrite(PIN_MUX0, 1);
            digitalWrite(PIN_MUX1, 0);
            break;
        case 2:
            digitalWrite(PIN_MUX0, 0);
            digitalWrite(PIN_MUX1, 1);
            break;
        case 3:
            digitalWrite(PIN_MUX0, 1);
            digitalWrite(PIN_MUX1, 1);
            break;
        
        default:
            break;
    }
}


////////////////////// SUSTRATO //////////////////////////

float humedadSUST()
{
    seleccionaEntrada(SUST);
    delay(50);
    float ret = analogRead(A0);
    delay(300);
    digitalWrite(D5,LOW);

    //Rango 640 - 1024 [384 es la amplitud de la señal]
    ret = ((1024.0 - ret) / 384.0) * 100.0;

    //Control de máximos y mínimos
    if(minMaxSust[1] < ret) minMaxSust[1] = ret;
    if(minMaxSust[0] > ret) minMaxSust[0] = ret;

    #ifdef DEBUG
        Serial.println("Lectura de humedad SUST: " + (String)ret + "%");
        Serial.println("MaxSust:" + (String)minMaxSust[1] + "/MinSust:" + (String)minMaxSust[0]);
    #endif

    return ret;
}


////////////////////// LUMINOSIDAD //////////////////////////

float luminosidad()
{
    seleccionaEntrada(LUM);
    delay(50);
    float ret = analogRead(A0);

    //Rango 0 - 1024
    ret = (ret / 1024.0) * 100.0;

    //Control de máximos y mínimos
    if(minMaxLum[1] < ret) minMaxLum[1] = ret;
    if(minMaxLum[0] > ret) minMaxLum[0] = ret;

    #ifdef DEBUG
        Serial.println("Lectura de luminosidad: " + (String)ret + "%");
        Serial.println("MaxLum:" + (String)minMaxLum[1] + "/MinLum:" + (String)minMaxLum[0]);
    #endif

    return ret;
}

void reiniciaMinMax()
{
    minMaxSust[0] = 1024;
    minMaxSust[1] = -1024;

    minMaxLum[0] = 1024;
    minMaxLum[1] = -1024;

    minMaxTemp[0] = 1024.0;
    minMaxTemp[1] = -1024.0;

    minMaxHum[0] = 1024;
    minMaxHum[1] = -1024;
}

////////Funciones para recoger los valores máximos y mínimos
float* getMinMaxTemp()
{
    return minMaxTemp;
}
int* getMinMaxHum()
{
    return minMaxHum;
}
int* getMinMaxLum()
{
    return minMaxLum;
}
int* getMinMaxSust()
{
    return minMaxSust;
}

