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
}

//  Função responsável por ligar a FAN
void fanON(const int fan)
{
    digitalWrite(fan, LOW);
}

//  Função responsável por desligar a FAN
void fanOFF(const int fan)
{
    digitalWrite(fan, LOW);
}

//  Função responsável por ligar a lâmpada de secagem
void hotLightON(const int hotLight)
{
    digitalWrite(hotLight, LOW);
}

//  Função responsável por desligar a lâmpada de secagem
void hotLightOFF(const int hotLight)
{
    digitalWrite(hotLight, HIGH);
}

//  Função responsável por ligar a lâmpada led
void ledLightON(const int ledLight)
{
    digitalWrite(ledLight, LOW);
}

//  Função responsável por desligar a lâmpada de secagem
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
        Serial.println("Fan ON - Hot Light OFF");
    }
    else if (average < min)
    {
        fanOFF(fan);
        hotLightON(hotLight);
        Serial.println("Fan OFF - Hot Light ON");
    }
    else
    {
        fanOFF(fan);
        hotLightOFF(hotLight);
        Serial.println("Fan OFF - Hot Light OFF");
    }
}

void humControl(const int valve, const int average, const int max)
{
    if (average < max)
    {
        valveON(valve);
        Serial.println("Válvula ligada");
        rtcDelay(4);
        valveOFF(valve);
        Serial.println("Válvula desligada");
    }
}