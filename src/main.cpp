//  Pages includes
#include <Arduino.h>
#include <DHT.h>
#include <Wire.h>
#include <RTClib.h>
#include <WiFi.h>
#include <time.h>
#include "dhtRead.h"
#include "ldrRead.h"
#include "soilRead.h"
#include "relays.h"
#include "rtc.h"
#include "general.h"

// CONSTANTS
extern const float MAX_TEMP = 22.5;  // Valor a ser definido pelo botão externo
extern const float MIN_TEMP = 18.0;  // Valor a ser definido pelo botão externo
extern const float MIN_HUM = 300;    // Valor a ser definido
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
DateTime previousTime;

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

  setupRTC();                                              //  Inicializa o RTC
  setupLDR(ldrPins);                                       //  Inicializa os LDRs
  setupSOIL(soilPin);                                      //  Inicializa o Sensor Capacitivo
  setupDHT();                                              //  Inicializa o DHT
  setupRelays(valvePin, fanPin, ledLightPin, hotLightPin); //  Inicializa os relés
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
  }

  float readSensor_DHT = readDHT();
  averageDHT = movAverage(measuresDHT, readSensor_DHT);
  Serial.print("Média DHT: ");
  Serial.println(averageDHT);
  tempControl(fanPin, hotLightPin, averageDHT, MAX_TEMP, MIN_TEMP);

  float readSensor_SOIL = readSOIL(soilPin);
  averageSOIL = movAverage(measuresSOIL, readSensor_SOIL);
  Serial.print("Média SOIL: ");
  Serial.println(averageSOIL);
  humControl(valvePin, averageSOIL, MIN_HUM);

  Serial.println();

  delay(5000);
}