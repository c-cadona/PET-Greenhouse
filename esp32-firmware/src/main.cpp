//  Pages includes
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <RTClib.h>
#include <WiFi.h>
#include <time.h>
#include <BluetoothSerial.h>
#include "ldrRead.h"
#include "soilRead.h"
#include "relays.h"
#include "rtc.h"
#include "general.h"
#include "bluetooth.h"

// CONSTANTS
extern const float MAX_TEMP = 24.0;   // Valor a ser definido pelo botão externo
extern const float MIN_TEMP = 18.0;   // Valor a ser definido pelo botão externo
extern const int ENOUGH_LIGHT = 1200; // Valor de luminosidade suficiente (Quanto menor o número, mais luminoso)
extern const int DRY = 3000;          // Valor lido quando o solo está totalmente seco
extern const int WET = 1700;          // Valor lido quando o solo está submerso na água
extern const int HUMIDITY = (1.25 * WET);

//  Digital Pin's
extern const int hotLightPin = 12;
extern const int ledLightPin = 14;
#define DHTPIN 4
extern const int fanPin = 26;
extern const int valvePin = 25;

//  Analog Pin's
extern const int ldrPins[2] = {33, 32};
extern const int soilPin = 35;

//  External objects
#define DHTTYPE DHT11
DHT_Unified dht(DHTPIN, DHTTYPE);

extern RTC_DS1307 rtc;

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
  Serial.begin(115200);
  Wire.begin();

  setupBluetooth();

  setupRTC();
  setupLDR(ldrPins);
  setupSOIL(soilPin);

  //  Setup DHT
  dht.begin();

  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.print(sensor.name);
  Serial.println(F("Detectado"));

  setupRelays(valvePin, fanPin, ledLightPin, hotLightPin);

  //  Pula 1 linha apenas
  Serial.println();
}

//---------------------------------------------------------------------------------
// Loop:
void loop()
{
  Serial.println();

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

  sensors_event_t event;
  dht.temperature().getEvent(&event);

  if (!isnan(event.temperature))
  {
    float readSensor_DHT = event.temperature;             // Armazena a leitura da temperatura
    averageDHT = movAverage(measuresDHT, readSensor_DHT); // Calcula a média móvel
    Serial.print("Média DHT: ");
    Serial.print(averageDHT);
    Serial.println("°C");
    tempControl(hotLightPin, fanPin, averageDHT, MAX_TEMP, MIN_TEMP); // Controle de temperatura
  }
  else
  {
    Serial.println(F("Erro no DHT"));
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