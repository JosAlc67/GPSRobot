#include "Navigation.h"
#include "Compass.h"
#include "GPS.h"
#include "Motor.h"
#include <Arduino.h>

// Declarar variables externas necesarias
extern int compass_heading;
extern int desired_heading;
extern TinyGPSPlus gps;
extern double Home_LATarray[50];
extern double Home_LONarray[50];
extern int wpCount;

// Función para ir a un waypoint
void goWaypoint() {
    Serial.println("Navegando hacia el waypoint...");

    if (wpCount == 0) {
        Serial.println("No hay waypoints definidos.");
        return;
    }

    for (int i = 0; i < wpCount; i++) {
        Serial.print("Navegando hacia Waypoint ");
        Serial.println(i + 1);

        double distanceToWaypoint;
        int courseToWaypoint;

        while (true) {
            getCompass();
            getGPS();

            distanceToWaypoint = TinyGPSPlus::distanceBetween(
                gps.location.lat(), gps.location.lng(),
                Home_LATarray[i], Home_LONarray[i]
            );

            courseToWaypoint = TinyGPSPlus::courseTo(
                gps.location.lat(), gps.location.lng(),
                Home_LATarray[i], Home_LONarray[i]
            );

            if (distanceToWaypoint < 1.0) { // Consideramos que llegamos si la distancia es <1 metro
                Serial.println("Waypoint alcanzado.");
                stopCar();
                break;
            }

            if (abs(courseToWaypoint - compass_heading) <= 10) {
                forward();
            } else if ((courseToWaypoint - compass_heading + 360) % 360 < 180) {
                // Ajustar hacia la derecha
                Serial.println("Ajustando hacia la derecha.");
                stopCar();
                delay(500);
            } else {
                // Ajustar hacia la izquierda
                Serial.println("Ajustando hacia la izquierda.");
                stopCar();
                delay(500);
            }
        }
    }
}

// Función para avanzar hacia adelante con base en la brújula
void Compass_Forward() {
    Serial.println("Avanzando hacia adelante usando brújula...");
    while (true) {
        getCompass();
        if (abs(desired_heading - compass_heading) <= 5) {
            forward();
        } else {
            stopCar();
            break;
        }
    }
    Serial.println("Destino alcanzado.");
}
