#include "ultrassonic.h"

void initUltrassonicSensor()
{
    // Set the trigger pin as output
    gpio_init(TRIGGER_PIN);
    gpio_set_dir(TRIGGER_PIN, GPIO_OUT);

    // Set the echo pin as input
    gpio_init(ECHO_PIN);
    gpio_set_dir(ECHO_PIN, GPIO_IN);
}

float measureDistance()
{
    // Send a 10 microsecond pulse to trigger the sensor
    gpio_put(TRIGGER_PIN, 1);
    sleep_us(10);
    gpio_put(TRIGGER_PIN, 0);

    // Wait for the echo pin to go high
    while (gpio_get(ECHO_PIN) == 0)
        ;

    // Start timing the echo pulse
    absolute_time_t start_time = get_absolute_time();

    // Wait for the echo pin to go low
    while (gpio_get(ECHO_PIN) == 1)
        ;

    // Stop timing the echo pulse
    absolute_time_t end_time = get_absolute_time();

    // Calculate the duration of the echo pulse in microseconds
    uint32_t duration = absolute_time_diff_us(start_time, end_time);

    // Calculate distance in cm (speed of sound is approximately 34300 cm/s)
    float distance = (duration / 2.0) * 0.0343; // Divide by 2 for round trip

    return distance;
}