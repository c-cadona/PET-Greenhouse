#include <Arduino.h>
#include <BluetoothSerial.h>
#include "bluetooth.h"

// Instância:
BluetoothSerial SerialBT;

// Função que inicia o Bluetooth no setup:
void setupBluetooth()
{
    SerialBT.begin("PetGreenhouse");
}

// Função que manda os dados em CSV se tem um cliente
void sendData(float dhtData, float lightData, float soilData)
{
    if (SerialBT.hasClient())
    {
        // Formata os dados em CSV
        String data = String(dhtData, 2) + "," + String(lightData, 2) + "," + String(soilData, 2) + "\n";

        // Envia a string CSV via Bluetooth
        SerialBT.print(data);
        Serial.print("Dados enviados: ");
        Serial.println(data); // Para monitoramento no Serial Monitor
    }
    else
    {
        Serial.println("Aguardando conexão");
    }
}
