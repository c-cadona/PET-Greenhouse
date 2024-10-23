#include <Arduino.h>
#include "dhtRead.h"
#include <DHT.h>

//  Objects define
#define DHT_TYPE DHT11
DHT dht(27, DHT_TYPE);

//  Função que inicia o DHT
void setupDHT()
{
    dht.begin();
}

float readDHT()
{
    return dht.readTemperature();
}
