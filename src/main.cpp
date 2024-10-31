//  Pages includes
#include <Arduino.h>
#include <DHT.h>
#include <Wire.h>
#include <RTClib.h>
#include <WiFi.h>
#include <time.h>
#include <LiquidCrystal_I2C.h>
#include "dhtRead.h"
#include "ldrRead.h"
#include "soilRead.h"
#include "relays.h"
#include "rtc.h"
#include "general.h"
#include "lcdDisplay.h"

// CONSTANTS
extern const float MAX_TEMP = 22.0;  // Valor a ser definido pelo botão externo
extern const float MIN_TEMP = 18.0;  // Valor a ser definido pelo botão externo
extern const int ENOUGH_LIGHT = 600; // Valor de luminosidade suficiente (Quanto menor o número, mais luminoso)
extern const int DRY = 700;          // Valor lido quando o solo está totalmente seco
extern const int WET = 370;          // Valor lido quando o solo está submerso na água

//  Digital Pin's
extern const int hotLightPin = 12;
extern const int ledLightPin = 14;
extern const int dhtPin = 27;
extern const int fanPin = 26;
extern const int valvePin = 25;

//  Analog Pin's
extern const int ldrPins[2] = {33, 32};
extern const int soilPin = 35;

//  External objects
extern DHT dht;
extern RTC_DS1307 rtc;
// extern LiquidCrystal_I2C lcd(0x27, 20, 4);

//  Arrays de armazenamento
float measuresDHT[10] = {0};
float measuresLDR[10] = {0};
float measuresSOIL[10] = {0};

//  Variáveis de armazenamento
float averageDHT = 0;
float averageLDR = 0;
float averageSOIL = 0;

//  Flags
bool threeMeasures = false;

//---------------------------------------------------------------------------------
// Setup:
void setup()
{
  Serial.begin(921600);
  Wire.begin();

  setupRTC();
  setupLDR(ldrPins);
  setupSOIL(soilPin);
  setupDHT();
  setupRelays(valvePin, fanPin, ledLightPin, hotLightPin);
  // setupLCD();
}

//---------------------------------------------------------------------------------
// Loop:
void loop()
{
  DateTime now = rtc.now();
  Serial.println(now.timestamp());

  float readSensor_LDR = readLDR(ldrPins);
  averageLDR = movAverage(measuresLDR, readSensor_LDR);
  Serial.print("Média LDR: ");
  Serial.println(averageLDR);

  float readSensor_DHT = readDHT();
  averageDHT = movAverage(measuresDHT, readSensor_DHT);
  Serial.print("Média DHT: ");
  Serial.println(averageDHT);

  float readSensor_SOIL = readSOIL(soilPin);
  averageSOIL = movAverage(measuresSOIL, readSensor_SOIL);
  Serial.print("Média SOIL: ");
  Serial.println(averageSOIL);

  Serial.println();

  rtcDelay(5);
}