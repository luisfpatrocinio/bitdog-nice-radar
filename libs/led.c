#include "led.h"

void initLeds()
{
    // Initialize the LED pins
    int led_pins[] = {LED_RED_PIN, LED_GREEN_PIN, LED_BLUE_PIN};
    for (int i = 0; i < 3; i++)
    {
        gpio_init(led_pins[i]);
        gpio_set_dir(led_pins[i], GPIO_OUT);
        gpio_set_function(led_pins[i], GPIO_FUNC_PWM);

        uint slice_num = pwm_gpio_to_slice_num(led_pins[i]);
        pwm_set_clkdiv(slice_num, PWM_DIVIDER); // Divider for the PWM clock
        pwm_set_wrap(slice_num, PWM_PERIOD);    // Set the wrap value for the PWM
        pwm_set_gpio_level(led_pins[i], 0);     // Set initial duty cycle to 0
        pwm_set_enabled(slice_num, true);       // Enable the PWM output
    }
}

void setLedColor(int red, int green, int blue)
{
    // Set the color of the RGB LED
    gpio_put(LED_RED_PIN, red);
    gpio_put(LED_GREEN_PIN, green);
    gpio_put(LED_BLUE_PIN, blue);
}

void turnOffLeds()
{
    setLedColor(0, 0, 0); // Turn off all LEDs
}

void manageLed(int led, int state)
{
    gpio_put(led, state);
}

void setLedBrightness(int led, int brightness)
{
    uint slice_num = pwm_gpio_to_slice_num(led);
    pwm_set_gpio_level(led, brightness); // Set the PWM level for the LED
}

void setAllLedsBrightness(int brightness)
{
    setLedBrightness(LED_RED_PIN, brightness);
    setLedBrightness(LED_GREEN_PIN, brightness);
    setLedBrightness(LED_BLUE_PIN, brightness);
}