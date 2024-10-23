//  Pages includes
#include <Arduino.h>
#include <DHT.h>
#include "dhtRead.h"
#include "ldrRead.h"
#include "soilRead.h"
#include "relays.h"

// CONSTANTS
const float MAX_TEMP = 22.0;  // Valor a ser definido pelo botão externo
const float MIN_TEMP = 18.0;  // Valor a ser definido pelo botão externo
const int ENOUGH_LIGHT = 150; // Valor de luminosidade suficiente (Quanto menor o número, mais luminoso)
const int DRY = 700;          // Valor lido quando o solo está totalmente seco
const int WET = 370;          // Valor lido quando o solo está submerso na água

//  Digital Pin's
extern const int hotLightPin = 12;
extern const int ledLightPin = 14;
extern const int dhtPin = 27;
extern const int fanPin = 26;
extern const int valvePin = 25;

//  Analog Pin's
extern const int ldrPins[2] = {33, 32};
extern const int capacitiveSensor = 35;

//  Objects define
#define DHT_TYPE DHT11
DHT dht(dhtPin, DHT_TYPE);

//  Arrays de armazenamento
float measuresDHT[3] = {0};
int measuresLDR[3] = {0};
int measuresSOIL[3] = {0};

//  Variáveis de armazenamento
float averageDHT = 0;
int averageLDR = 0;
int averageSOIL = 0;

//  Flags
bool threeMeasures = 0;

//---------------------------------------------------------------------------------
// Setup:
void setup()
{

  Serial.begin(921600);

  setupLDR(ldrPins);
}

//---------------------------------------------------------------------------------
// Loop:
void loop()
{
}