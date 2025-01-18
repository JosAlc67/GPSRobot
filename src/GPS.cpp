#include "GPS.h"
#include <HardwareSerial.h>
#include <Arduino.h>

TinyGPSPlus gps;
HardwareSerial neogps(1);
double Home_LATarray[50] = {0};
double Home_LONarray[50] = {0};
int wpCount = 0;

void setupGPS() {
    neogps.begin(9600, SERIAL_8N1, 16, 17);
}

void getGPS() {
    while (neogps.available()) {
        char c = neogps.read();
        gps.encode(c);
    }
}

void setWaypoint() {
    if (wpCount < 50) {
        getGPS();
        Home_LATarray[wpCount] = gps.location.lat();
        Home_LONarray[wpCount] = gps.location.lng();
        wpCount++;
        Serial.println("Waypoint establecido.");
    } else {
        Serial.println("Límite de waypoints alcanzado.");
    }
}

void clearWaypoints() {
    memset(Home_LATarray, 0, sizeof(Home_LATarray));
    memset(Home_LONarray, 0, sizeof(Home_LONarray));
    wpCount = 0;
    Serial.println("Waypoints eliminados.");
}
