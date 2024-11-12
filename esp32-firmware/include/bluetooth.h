#ifndef bluetooth_h
#define bluetooth_h

// Declaração da função para inicializar o Bluetooth
void setupBluetooth();

// Declaração da função para enviar dados via Bluetooth
void sendData(float dhtData, float lightData, float soilData);

#endif
