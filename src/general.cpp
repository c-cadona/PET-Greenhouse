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
    if (values[0] == 0)
    {
        values[0] = measure;
        return values[0];
    }
    else if (values[1] == 0)
    {
        values[1] = measure;
        return simpleAvg(values, 2); // Média dos dois primeiros valores
    }
    else if (values[2] == 0)
    {
        values[2] = measure;
        return simpleAvg(values, 3); // Média dos três primeiros valores
    }
    else if (values[3] == 0)
    {
        values[3] = measure;
        return simpleAvg(values, 4); // Média dos quatro primeiros valores
    }
    else if (values[4] == 0)
    {
        values[4] = measure;
        return simpleAvg(values, 5); // Média dos cinco primeiros valores
    }
    else
    {
        // Move os valores para criar espaço para o novo valor
        for (int i = 0; i < 4; i++)
        {
            values[i] = values[i + 1];
        }
        values[4] = measure;

        // Retorna a média dos 5 valores
        return simpleAvg(values, 5);
    }
}