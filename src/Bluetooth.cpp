#include "Bluetooth.h"
#include "Motor.h"
#include "Compass.h"
#include "GPS.h"
#include "Navigation.h"

BluetoothSerial SerialBT;
int blueToothVal;
String str;

void setupBluetooth() {
    SerialBT.begin("ESP32_Car");
    Serial.println("Bluetooth initialized");
}

void handleBluetooth() {
    while (SerialBT.available()) {
        str = SerialBT.readStringUntil('\n');
        blueToothVal = str.toInt();
        Serial.print("Valor Bluetooth recibido: ");
        Serial.println(blueToothVal);
    }

    switch (blueToothVal) {
        case 1:
            SerialBT.println("Forward");
            forward();
            break;
        case 2:
            SerialBT.println("Reverse");
            reverse();
            break;
        case 3:
            SerialBT.println("Left");
            // Lógica para giro a la izquierda
            break;
        case 4:
            SerialBT.println("Right");
            // Lógica para giro a la derecha
            break;
        case 5:
            SerialBT.println("Stop Car");
            stopCar();
            break;
        case 6:
            SerialBT.println("Set Waypoint");
            setWaypoint();
            break;
        case 7:
            SerialBT.println("Go Waypoint");
            goWaypoint();
            break;
        case 8:
            SerialBT.println("Turn Around");
            // Lógica para girar en U
            break;
        case 9:
            SerialBT.println("Compass Forward");
            Compass_Forward();
            break;
        case 10:
            SerialBT.println("Set Heading");
            setHeading();
            break;
        case 11:
            SerialBT.println("GPS Info");
            // Obtener información del GPS
            break;
        default:
            SerialBT.println("Comando no reconocido");
            break;
    }
}
