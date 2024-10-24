#ifndef dhtRead_h
#define dhtRead_h

void setupDHT();
float readDHT();
bool isHot(const int average, const int max);
bool isCold(const int average, const int min);

#endif