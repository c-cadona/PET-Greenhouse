#include <Arduino.h>
#include "relays.h"

void setupRelays(const int valve, const int fan, const int ledLight, const int hotLight)
{
    pinMode(valve, OUTPUT);
    pinMode(fan, OUTPUT);
    pinMode(ledLight, OUTPUT);
    pinMode(hotLight, OUTPUT);
}
