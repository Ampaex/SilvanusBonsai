#include "conf.h" //Configuración general

void inicializaPerifericos();

//RELÉ

void activaRele();          
void desactivaRele();


//SENSORHT

void htBegin();     
float temperaturaHT();
float humedadHT();

//MULTIPLEXOR
//Selecciona el dispositivo analógico a leer
void inicializaMultiplexor();
void seleccionaEntrada(int entrada);

//SUSTRATO

float humedadSUST();


//LUMINOSIDAD

float luminosidad();