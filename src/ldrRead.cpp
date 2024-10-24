#include <Arduino.h>
#include "ldrRead.h"

//  Função que inicia os LDRs
void setupLDR(const int pins[])
{
    for (int i = 0; i < 2; i++)
    {
        pinMode(pins[i], INPUT); // Configura os pinos recebidos como entrada
    }
}

int readLDR(const int pins[])
{
    int ldr1 = analogRead(pins[0]);
    int ldr2 = analogRead(pins[1]);

    int simpleAverage = (ldr1 + ldr2) / 2;

    return simpleAverage;
}
