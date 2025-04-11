#ifndef BUTTONS_H
#define BUTTONS_H

#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Buttons
#define BTA 5
#define BTB 6

void initializeButtons();
void setButtonCallback(void (*handleButtonGpioEvent)(uint gpio, uint32_t events));

#endif