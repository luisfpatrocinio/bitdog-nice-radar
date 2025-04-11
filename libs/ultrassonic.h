#ifndef ULTRASSONIC_H
#define ULTRASSONIC_H

#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "time.h"

// Ultrassonic Sensor
#define TRIGGER_PIN 16
#define ECHO_PIN 17
void initUltrassonicSensor();
float measureDistance();

#endif