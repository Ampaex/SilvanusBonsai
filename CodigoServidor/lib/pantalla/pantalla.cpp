#include  "pantalla.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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