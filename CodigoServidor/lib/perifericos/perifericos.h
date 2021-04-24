#include "conf.h" //Configuración general


void inicializaPerifericos();

//RELÉ

void activaRele();          
void desactivaRele();       


//SENSORHT

void htBegin();     
float temperaturaHT();
float humedadHT();


//SUSTRATO

float humedadSUST();


//LUMINOSIDAD

float luminosidad();