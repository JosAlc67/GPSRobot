#include "Motor.h"
#include <Arduino.h>  // Necesario para usar las funciones de Arduino

// Definición de pines de los motores
#define IN1 32
#define IN2 33
#define ENA 12
#define IN3 25
#define IN4 26
#define ENB 13

// Definir las direcciones
#define FORWARD 1
#define BACKWARD 0
#define RELEASE 2  // Agregar estado para detener el motor

class Motor {
public:
    // Constructor que recibe los pines de los motores
    Motor(int in1Pin, int in2Pin, int enPin) {
        _in1Pin = in1Pin;
        _in2Pin = in2Pin;
        _enPin = enPin;

        pinMode(_in1Pin, OUTPUT);
        pinMode(_in2Pin, OUTPUT);
        pinMode(_enPin, OUTPUT);
    }

    // Método para controlar la dirección del motor
    void run(int direction) {
        if (direction == FORWARD) {
            digitalWrite(_in1Pin, HIGH);
            digitalWrite(_in2Pin, LOW);
        } else if (direction == BACKWARD) {
            digitalWrite(_in1Pin, LOW);
            digitalWrite(_in2Pin, HIGH);
        } else if (direction == RELEASE) {
            digitalWrite(_in1Pin, LOW);
            digitalWrite(_in2Pin, LOW);
        }
    }

    // Método para ajustar la velocidad del motor
    void setSpeed(int speed) {
        analogWrite(_enPin, speed);
    }

private:
    int _in1Pin;  // Pin para el primer terminal del motor
    int _in2Pin;  // Pin para el segundo terminal del motor
    int _enPin;   // Pin para el control de velocidad (PWM)
};

Motor motor1(IN1, IN2, ENA);
Motor motor2(IN3, IN4, ENB);

int motorSpeed = 250; // Velocidad predeterminada

void setupMotors() {
    motor1.setSpeed(motorSpeed);
    motor2.setSpeed(motorSpeed);
}

void forward() {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    Serial.println("Moviendo hacia adelante");
}

void reverse() {
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    Serial.println("Moviendo hacia atrás");
}

void stopCar() {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    Serial.println("Deteniendo el auto");
}
