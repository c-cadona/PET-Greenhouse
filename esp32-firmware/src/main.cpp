//  Pages includes
#include <Arduino.h>
#include <DHT.h>
#include <Wire.h>
#include <RTClib.h>
#include <WiFi.h>
#include <time.h>
#include <BluetoothSerial.h>
#include "dhtRead.h"
#include "ldrRead.h"
#include "soilRead.h"
#include "relays.h"
#include "rtc.h"
#include "general.h"
#include "bluetooth.h"

// CONSTANTS
extern const float MAX_TEMP = 22.0;  // Valor a ser definido pelo botão externo
extern const float MIN_TEMP = 18.0;  // Valor a ser definido pelo botão externo
extern const int ENOUGH_LIGHT = 600; // Valor de luminosidade suficiente (Quanto menor o número, mais luminoso)
extern const int DRY = 1000;         // Valor lido quando o solo está totalmente seco
extern const int WET = 3000;         // Valor lido quando o solo está submerso na água
extern const int HUMIDITY = 0.75 * DRY;

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
  setupBluetooth();
  // setupLCD();
}

//---------------------------------------------------------------------------------
// Loop:
void loop()
{
  DateTime now = rtc.now();
  Serial.println(now.timestamp());

  if (isDayTime())
  {
    float readSensor_LDR = readLDR(ldrPins);
    averageLDR = movAverage(measuresLDR, readSensor_LDR);
    Serial.print("Média LDR: ");
    Serial.println(averageLDR);
    lightControl(ledLightPin, averageLDR, ENOUGH_LIGHT);
  }

  float readSensor_DHT = readDHT();
  if (readSensor_DHT != -1)
  {
    averageDHT = movAverage(measuresDHT, readSensor_DHT);
    Serial.print("Média DHT: ");
    Serial.println(averageDHT);
    tempControl(hotLightPin, fanPin, averageDHT, MAX_TEMP, MIN_TEMP);
  }

  float readSensor_SOIL = readSOIL(soilPin);
  averageSOIL = movAverage(measuresSOIL, readSensor_SOIL);
  Serial.print("Média SOIL: ");
  Serial.println(averageSOIL);
  humControl(valvePin, averageSOIL, HUMIDITY);

  sendData(averageDHT, averageLDR, averageSOIL);

  Serial.println();

  rtcDelay(5);
}