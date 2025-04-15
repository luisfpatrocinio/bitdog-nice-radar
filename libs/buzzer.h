#ifndef BUZZER_H
#define BUZZER_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#define BUZZER_PIN 21
#define CLOCK_PWM 125000000.0f   // Clock base do RP2040 em float
#define BUZZER_PWM_DIVIDER 16.0f // Divisor de clock pwm

void initBuzzerPWM();
void beep(int duration);
void playTone(uint frequency, uint duration_ms);

#endif // BUZZER_H