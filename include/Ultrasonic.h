#ifndef ULTRASONIC_H
#define ULTRASONIC_H

void setupUltrasonic();
long getDistance(int trigPin, int echoPin);
void Ping();

#endif
