#ifndef relays_h
#define relays_h

void setupRelays(const int valve, const int fan, const int ledLight, const int hotLight);
void tempControl(const int fan, const int hotLight, float averageDHT, const float max, const float min);
void humControl(const int valve, float averageSOIL, const float min);

void fanON(const int fan);
void fanOFF(const int fan);

void hotLightON(const int hotLight);
void hotLightOFF(const int hotLight);

void ledLightON(const int ledLight);
void ledLightOFF(const int ledLight);

void valveON(const int valve);
void valveOFF(const int valve);

void tempControl(const int hotLight, const int fan, const float average, const float max, const float min);
void humControl(const int valve, const float average, const float max);
void lightControl(const int ledLight, const float average, const int enough);

#endif