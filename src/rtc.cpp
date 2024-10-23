#include <Arduino.h>
#include "rtc.h"
#include <Wire.h>
#include <RTClib.h>

//  Object define
RTC_DS1307 rtc;

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
