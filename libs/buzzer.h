#ifndef BUZZER_H
#define BUZZER_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#define BUZZER_PIN 21

void initBuzzerPWM();
void beep(int duration);
void playTone(uint frequency, uint duration_ms);

#endif // BUZZER_H