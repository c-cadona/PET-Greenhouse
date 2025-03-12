#ifndef control_h
#define control_h

void tempControl(const int hotLight, const int fan, const float average, const float max, const float min);
void humControl(const int valve, float averageSOIL, const float min, const float max);
void lightControl(const int ledLight, const float average, const int enough);

#endif