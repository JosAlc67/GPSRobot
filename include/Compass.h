#ifndef COMPASS_H
#define COMPASS_H

#include <QMC5883LCompass.h>

void setupCompass();
void getCompass();
void setHeading();
void calibrateCompass();

#endif
