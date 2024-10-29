#include <Arduino.h>
#include "rtc.h"
#include <Wire.h>
#include <RTClib.h>

//  Object define
RTC_DS1307 rtc;

//  Inicializando o RTC
void setupRTC()
{
    if (!rtc.begin())
    {
        Serial.println("RTC não encontrado!");
        while (true)
            ; // Se o RTC não for encontrado, trava o código
    }

    if (!rtc.isrunning())
    {
        Serial.println("RTC não está funcionando, ajustando para o horário de compilação...");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Ajusta o RTC para o horário de compilação
    }

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
