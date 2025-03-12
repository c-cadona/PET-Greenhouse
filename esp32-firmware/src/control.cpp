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
    static unsigned long valveStartTime = 0;  // Tempo em que a válvula foi ligada
    const unsigned long valveDuration = 3000; // Tempo que a válvula fica ligada (3 segundos)
    static bool valveState = false;           // Armazena o estado atual da válvula

    if (averageSOIL > max && !valveState)
    {
        valveON(valve); // Liga a válvula
        valveState = true;
        valveStartTime = millis(); // Marca o tempo em que a válvula foi ligada
        Serial.println("Valve ON");
    }
    else if (averageSOIL < min && valveState)
    {
        valveOFF(valve); // Desliga a válvula
        valveState = false;
        valveStartTime = 0; // Reseta o tempo
        Serial.println("Valve OFF");
    }
    else if (valveState && (millis() - valveStartTime >= valveDuration)) // Se passaram 3 segundos
    {
        valveOFF(valve); // Desliga a válvula
        valveState = false;
        valveStartTime = 0; // Reseta o tempo
        Serial.println("Valve OFF");
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