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
