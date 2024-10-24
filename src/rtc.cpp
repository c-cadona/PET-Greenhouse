#include <Arduino.h>
#include "rtc.h"
#include <Wire.h>
#include <RTClib.h>

//  Object define
RTC_DS1307 rtc;

//  Inicializando o RTC
void setupRTC()
{
    DateTime now = rtc.now();
    Serial.println("Horario atual: ");
    Serial.print(now.hour());
    Serial.print(": ");
    Serial.print(now.minute());
    Serial.print(": ");
    Serial.print(now.second());
}

//  Função para conferir se é dia - para controle da luz fria.
bool isDayTime()
{
    DateTime now = rtc.now();
    return (now.hour() >= 6 && now.hour() < 18);
}
