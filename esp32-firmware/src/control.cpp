#include <Arduino.h>
#include "control.h"
#include "relays.h" 

// Controle de temperatura
void tempControl(const int hotLight, const int fan, const float average, const float max, const float min)
{
    const float maxHysteresis = max + 1.0; // Margem superior
    const float minHysteresis = min - 1.0; // Margem inferior

    if (average > maxHysteresis)
    {
        fanON(fan);            // Liga o ventilador
        hotLightOFF(hotLight); // Desliga o aquecedor
        Serial.println("FAN ON (Temperature too high)");
    }
    else if (average < minHysteresis)
    {
        fanOFF(fan);          // Desliga o ventilador
        hotLightON(hotLight); // Liga o aquecedor
        Serial.println("Hot Light ON (Temperature too low)");
    }
    else
    {
        fanOFF(fan);           // Desliga o ventilador
        hotLightOFF(hotLight); // Desliga o aquecedor
        Serial.println("Temperature within range");
    }
}

// Controle de umidade do solo
void humControl(const int valve, float averageSOIL, const float min, const float max)
{
    static bool valveState = false; // Estado atual da válvula

    // Caso 1: Solo está muito seco, liga a válvula
    if (averageSOIL > max && !valveState)
    {
        valveON(valve);    // Liga a válvula
        valveState = true; // Atualiza o estado da válvula
        Serial.println("Valve ON");
    }
    // Caso 2: Solo está suficientemente úmido, desliga a válvula
    else if (averageSOIL < min && valveState)
    {
        valveOFF(valve);    // Desliga a válvula
        valveState = false; // Atualiza o estado da válvula
        Serial.println("Valve OFF");
    }
    // Caso 3: Solo está na faixa ideal, desliga a válvula
    else if (valveState && averageSOIL >= min && averageSOIL <= max)
    {
        valveOFF(valve);    // Desliga a válvula
        valveState = false; // Atualiza o estado da válvula
        Serial.println("Valve OFF - Soil in optimal range");
    }
}

// Controle de luz
void lightControl(const int ledLight, const float average, const int enough)
{
    static bool ledState = false; // Armazena o estado atual do LED
    const int hysteresis = 100;   // Margem de histerese

    if (average > (enough + hysteresis) && !ledState)
    {
        ledLightON(ledLight); // Liga a luz LED
        ledState = true;
        Serial.println("Led ON");
    }
    else if (average < (enough - hysteresis) && ledState)
    {
        ledLightOFF(ledLight); // Desliga a luz LED
        ledState = false;
        Serial.println("Led OFF");
    }
}