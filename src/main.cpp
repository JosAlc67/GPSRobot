#include <Arduino.h>
#include "Bluetooth.h"
#include "Compass.h"
#include "GPS.h"
#include "Motor.h"
#include "Navigation.h"
#include "Ultrasonic.h"

void setup() {
    Serial.begin(115200);
    setupBluetooth();
    setupMotors();
    setupCompass();
    setupGPS();
    setupUltrasonic();
}

void loop() {
    handleBluetooth();
    getGPS();
    getCompass();
}
