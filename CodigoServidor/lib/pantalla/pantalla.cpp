#include  "pantalla.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSerif9pt7b.h>

#define OLED_RESET D4
Adafruit_SSD1306 display(OLED_RESET);

static const unsigned char PROGMEM bonsai_logo[] =
{ 
    B00000000,   B00000000,
    B00000000,   B00000000,
    B00000000,   B00000000,
    B00000000,   B00000000,
    B00000000,   B11000000,
    B00000001,   B11100000,
    B00000011,   B11111000,
    B00000000,   B11000000,
    B00001101,   B10000000,
    B00111111,   B00000000,
    B00000001,   B10110000,
    B00000000,   B11111100,
    B00000001,   B10000000,
    B00011111,   B11111000,
    B00001111,   B11100000,
    B00000000,   B00000000
};

void inicializaPantalla()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    //display.display();
    //delay(2000);
    Serial.println("Arrancando pantalla");

    // Clear the buffer.
    display.clearDisplay();
}

void limpiaPantalla()
{
    display.clearDisplay();
    display.display();
}

void escenaIntro()
{
    display.setTextSize(0.5);
    display.setTextColor(WHITE);
    display.setCursor(8,6);
    display.write("Silvanus");
    display.setCursor(15,18);
    display.write("Bonsai");
    display.drawBitmap(24, 28,  bonsai_logo, 16, 16, 1);
    display.display();
}

void muestraNodo(const char * idNodo, int temperaturaht, int humedadht, int humedadSUST, int luminosidad)
{
    display.setTextSize(1);
    display.setFont(NULL);
    display.setTextColor(WHITE);
    display.setTextWrap(false);
    //Nombre del nodo
    display.setCursor(0,0);
    display.write(idNodo);

    //Temperaturaht
    display.setCursor(0,12);
    display.write("Temp:");
    display.setCursor(30,12);
    char numeros[10];
    itoa(temperaturaht,numeros,10);
    display.write(numeros);
    display.setCursor(42,12);
    display.write("C");

    //Humedadht
    display.setCursor(0,21);
    display.write("Humed:");
    display.setCursor(36,21);
    memset(numeros, 0, sizeof(char)*10); //Borrado de números
    itoa(humedadht,numeros,10);
    display.write(numeros);
    display.setCursor(48,21);
    display.write("%");

    //Sustrato
    display.setCursor(0,30);
    display.write("Sust:");
    display.setCursor(30,30);
    memset(numeros, 0, sizeof(char)*10); //Borrado de números
    itoa(humedadSUST,numeros,10);
    display.write(numeros);
    display.setCursor(42,30);
    display.write("%");

    //Luminosidad
    display.setCursor(0,39);
    display.write("Lum:");
    display.setCursor(24,39);
    memset(numeros, 0, sizeof(char)*10); //Borrado de números
    itoa(luminosidad,numeros,10);
    display.write(numeros);
    display.setCursor(36,39);
    display.write("%");

    display.display();
}