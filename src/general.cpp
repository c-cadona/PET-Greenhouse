#include <Arduino.h>
#include "general.h"

float moving_average(float values[], int size)
{
    float sum = 0.0;
    for (int i = 0; i < size; i++)
    {
        sum += values[i];
    }
    return sum / size;
}
