#include <Arduino.h>
#include "relays.h"
#include "dhtRead.h"
#include "rtc.h"

//  Função que inicia os relés
void setupRelays(const int valve, const int fan, const int ledLight, const int hotLight)
{
    pinMode(valve, OUTPUT);
    pinMode(fan, OUTPUT);
    pinMode(ledLight, OUTPUT);
    pinMode(hotLight, OUTPUT);

    digitalWrite(valve, HIGH);
    digitalWrite(fan, HIGH);
    digitalWrite(ledLight, HIGH);
    digitalWrite(hotLight, HIGH);
}

//  Função responsável por ligar a FAN
void fanON(const int fan)
{
    digitalWrite(fan, LOW);
    Serial.println("FAN ON");
}

//  Função responsável por desligar a FAN
void fanOFF(const int fan)
{
    digitalWrite(fan, HIGH);
    Serial.println("FAN OFF");
}

//  Função responsável por ligar a lâmpada de secagem
void hotLightON(const int hotLight)
{
    digitalWrite(hotLight, LOW);
    Serial.println("Hot Light ON");
}

//  Função responsável por desligar a lâmpada de secagem
void hotLightOFF(const int hotLight)
{
    digitalWrite(hotLight, HIGH);
    Serial.println("Hot Light OFF");
}

//  Função responsável por ligar a lâmpada led
void ledLightON(const int ledLight)
{
    digitalWrite(ledLight, LOW);
}

//  Função responsável por desligar a lâmpada led
void ledLightOFF(const int ledLight)
{
    digitalWrite(ledLight, HIGH);
}

//  Função responsável por ligar a válvula solenoide
void valveON(const int valve)
{
    digitalWrite(valve, LOW);
}
//  Função responsável por desligar a válvula solenoide
void valveOFF(const int valve)
{
    digitalWrite(valve, HIGH);
}

void tempControl(const int hotLight, const int fan, const float average, const float max, const float min)
{
    if (average > max)
    {
        fanON(fan);
        hotLightOFF(hotLight);
    }

    else if (average < min)
    {
        fanOFF(fan);
        hotLightON(hotLight);
    }
    else
    {
        fanOFF(fan);
        hotLightOFF(hotLight);
    }
}

void humControl(const int valve, float averageSOIL, const float min)
{
    if (averageSOIL < min)
    {
        valveOFF(valve);
        Serial.println("Valve OFF");
    }
    else if (averageSOIL > min)
    {
        valveON(valve);
        Serial.println("Valve ON");
        delay(5000);
        valveOFF(valve);
        Serial.println("Valve OFF");
    }
}

void lightControl(const int ledLight, const float average, const int enough)
{
    if (average > enough)
    {
        ledLightON(ledLight);
        Serial.println("Led ON");
    }
    else
    {
        ledLightOFF(ledLight);
        Serial.println("Led OFF");
    }
}