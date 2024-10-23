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

//  Função que lê a temperatura pelo DHT
float readDHT()
{
    return dht.readTemperature();
}
