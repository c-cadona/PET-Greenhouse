//  Pages includes
#include <Arduino.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <time.h>
#include <BluetoothSerial.h>
#include "ldrRead.h"
#include "soilRead.h"
#include "relays.h"
#include "general.h"
#include "bluetooth.h"
#include "control.h"

// CONSTANTS
extern const float MAX_TEMP = 24.0;
extern const float MIN_TEMP = 18.0;
extern const int ENOUGH_LIGHT = 1200; // Valor de luminosidade suficiente (Quanto menor o número, mais luminoso)
extern const int DRY = 3000;          // Valor lido quando o solo está totalmente seco
extern const int WET = 1700;          // Valor lido quando o solo está submerso na água

//  Digital Pin's
extern const int hotLightPin = 12;
extern const int ledLightPin = 14;
extern const int fanPin = 26;
extern const int valvePin = 25;

//  Analog Pin's
extern const int ldrPins[2] = {33, 32};
extern const int soilPin = 35;

// temp sensor:
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

//  Arrays de armazenamento
float measuresTemp[10] = {0};
float measuresLDR[10] = {0};
float measuresSOIL[10] = {0};

//  Variáveis de armazenamento
float averageTemp = 0;
float averageLDR = 0;
float averageSOIL = 0;

//---------------------------------------------------------------------------------
// Setup:
void setup()
{
  Serial.begin(115200);
  Wire.begin();

  setupBluetooth();
  setupLDR(ldrPins);
  setupSOIL(soilPin);
  setupRelays(valvePin, fanPin, ledLightPin, hotLightPin);
  sensors.begin();

  Serial.println();
}

// Controle de tempo sem RTC
unsigned long lastLoopTime = 0;          // Armazena o tempo da última execução
const unsigned long loopInterval = 3000; // Intervalo de 5 segundos

void loop()
{
  // Verifica se já passaram 5 segundos desde a última execução
  if (millis() - lastLoopTime >= loopInterval)
  {
    lastLoopTime = millis(); // Atualiza o tempo da última execução

    Serial.println();

    // Leitura do sensor LDR
    float readSensor_LDR = readLDR(ldrPins);
    averageLDR = movAverage(measuresLDR, readSensor_LDR);
    Serial.print("Média LDR: ");
    Serial.println(averageLDR);

    // Controle de luz baseado apenas na luminosidade
    lightControl(ledLightPin, averageLDR, ENOUGH_LIGHT);

    // Leitura do sensor de temperatura DS18B20
    sensors.requestTemperatures();
    float readSensor_DS18B20 = sensors.getTempCByIndex(0);

    if (readSensor_DS18B20 != DEVICE_DISCONNECTED_C)
    {
      averageTemp = movAverage(measuresTemp, readSensor_DS18B20);
      Serial.print("Média DS18B20: ");
      Serial.print(averageTemp);
      Serial.println("°C");

      // Controle de temperatura
      tempControl(hotLightPin, fanPin, averageTemp, MAX_TEMP, MIN_TEMP);
    }
    else
    {
      Serial.println("Erro no DS18B20");
    }

    // Leitura do sensor de umidade do solo
    float readSensor_SOIL = readSOIL(soilPin);
    averageSOIL = movAverage(measuresSOIL, readSensor_SOIL);
    Serial.print("Média SOIL: ");
    Serial.println(averageSOIL);

    // Controle de umidade do solo
    humControl(valvePin, averageSOIL, DRY, WET);

    // Envia dados via Bluetooth
    sendData(averageTemp, averageLDR, averageSOIL);

    Serial.println();
  }
}