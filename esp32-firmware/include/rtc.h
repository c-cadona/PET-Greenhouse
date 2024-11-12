#ifndef rtc_h
#define rtc_h

void setupRTC();
bool isDayTime();
void rtcDelay(unsigned long intervalSeconds);

#endif