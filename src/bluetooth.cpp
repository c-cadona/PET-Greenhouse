#include <Arduino.h>
#include <BluetoothSerial.h>
#include "bluetooth.h"

// Objects:
BluetoothSerial SerialBT;

//função que inicia o bluetooth:
void setupBluetooth (){
    SerialBT.begin("PetGreenhouse");
}

 