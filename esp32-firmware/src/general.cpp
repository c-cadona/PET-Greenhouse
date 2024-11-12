#include <Arduino.h>
#include "general.h"

float simpleAvg(float values[], int size)
{
    float sum = 0.0;
    for (int i = 0; i < size; i++)
    {
        sum += values[i];
    }
    return sum / size;
}

float movAverage(float values[], float measure)
{
    // Inicializa os valores se estiverem em zero
    for (int i = 0; i < 10; i++)
    {
        if (values[i] == 0)
        {
            values[i] = measure;
            return simpleAvg(values, i + 1); // Calcula a média dos valores disponíveis
        }
    }

    // Quando o array estiver cheio, mova todos os valores
    for (int i = 0; i < 10; i++)
    {
        values[i] = values[i + 1];
    }
    values[9] = measure;

    // Retorna a média dos 10 valores
    return simpleAvg(values, 10);
}