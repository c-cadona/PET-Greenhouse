#include <Arduino.h>
#include "lcdDisplay.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setupLCD()
{
    Wire.begin();
    lcd.begin(20, 4); // Inicializa o LCD
    lcd.backlight();  // Ativa a luz de fundo do LCD

    lcd.setCursor(0, 0);
    lcd.print("Hello, ESP32!");

    lcd.setCursor(0, 1);
    lcd.print("LCD I2C Teste");
}
