#include <Arduino.h>
#include "soilRead.h"

//  Função que inicia o Sensor Capacitivo
void setupSOIL(const int pin)
{
    pinMode(pin, INPUT);
}

//  Função que lê a umidade do solo
int readSOIL(const int pin)
{
    return analogRead(pin);
}
