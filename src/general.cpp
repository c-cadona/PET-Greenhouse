#include <Arduino.h>
#include "general.h"

float simpleAvg(float values[])
{
    float sum = 0.0;
    for (int i = 0; i < 3; i++)
    {
        sum += values[i];
    }
    return sum / 3;
}

float movAverage(float values[], float measure)
{
    if (values[0] == 0)
    {
        values[0] = measure;
        return values[0];
    }
    else if (values[1] == 0)
    {
        values[1] = measure;
        return (values[0] + values[1]) / 2;
    }
    else if (values[2] == 0)
    {
        values[2] = measure;
        float avg = simpleAvg(values);
        return avg;
    }
    else
    {
        values[0] = values[1];
        values[1] = values[2];
        values[2] = measure;
        float avg = simpleAvg(values);
        return avg;
    }
}
