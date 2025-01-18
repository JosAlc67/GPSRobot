#include "Ultrasonic.h"
#include <Arduino.h>

// Pines de los sensores ultrasónicos
#define TRIG_FRONT_LEFT 14
#define ECHO_FRONT_LEFT 27
#define TRIG_FRONT_RIGHT 18
#define ECHO_FRONT_RIGHT 23

// Variables para la detección
long distanceLeft, distanceRight;
bool pingOn = false; // Activar/Desactivar detección de colisiones
unsigned long previousMillis = 0;
const long interval = 200; // Intervalo entre mediciones (ms)

void setupUltrasonic() {
    pinMode(TRIG_FRONT_LEFT, OUTPUT);
    pinMode(ECHO_FRONT_LEFT, INPUT);
    pinMode(TRIG_FRONT_RIGHT, OUTPUT);
    pinMode(ECHO_FRONT_RIGHT, INPUT);
}

long getDistance(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    return (duration / 2) / 29.1; // Convertir tiempo en distancia (cm)
}

void Ping() {
    unsigned long currentMillis = millis();

    if (pingOn && (currentMillis - previousMillis >= interval)) {
        previousMillis = currentMillis;

        // Medir distancias
        distanceLeft = getDistance(TRIG_FRONT_LEFT, ECHO_FRONT_LEFT);
        distanceRight = getDistance(TRIG_FRONT_RIGHT, ECHO_FRONT_RIGHT);

        // Mostrar distancias para depuración
        Serial.print("Izquierda: ");
        Serial.print(distanceLeft);
        Serial.print(" cm, Derecha: ");
        Serial.println(distanceRight);

        // Comprobar colisiones
        if ((distanceLeft < 12 || distanceRight < 12)) {
            Serial.println("¡Obstáculo detectado!");
            // Acciones específicas (como detener el motor)
        }
    }
}
