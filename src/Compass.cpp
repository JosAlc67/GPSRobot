#include "Compass.h"
#include <Wire.h>
#include <Arduino.h>

QMC5883LCompass compass;
int compass_heading;
int desired_heading;
int compass_dev = 5;

void setupCompass() {
    Wire.begin(21, 22);
    compass.init();
    compass.setMode(0x01, 0x04, 0x00, 0x00);
}

void getCompass() {
    compass.read();
    int16_t mx = compass.getX();
    int16_t my = compass.getY();
    float heading = atan2(my, mx);

    if (heading < 0)
        heading += 2 * M_PI;

    compass_heading = (int)(heading * 180 / M_PI);
}

void setHeading() {
    getCompass();
    desired_heading = compass_heading;
}

void calibrateCompass() {
    int minX = 0, maxX = 0, minY = 0, maxY = 0;

    for (int i = 0; i < 1000; i++) {
        compass.read();
        minX = min(minX, compass.getX());
        maxX = max(maxX, compass.getX());
        minY = min(minY, compass.getY());
        maxY = max(maxY, compass.getY());
        delay(10);
    }

    compass.setCalibration(minX, maxX, minY, maxY, 0, 0);
    Serial.print("Calibración de brújula: ");
    Serial.print("X["); Serial.print(minX); Serial.print(", "); Serial.print(maxX); Serial.print("] ");
    Serial.print("Y["); Serial.print(minY); Serial.print(", "); Serial.print(maxY); Serial.println("]");
}
