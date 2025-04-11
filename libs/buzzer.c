#include "buzzer.h"

// Inicializa o PWM no pino do buzzer
void initBuzzerPWM()
{
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.0f); // Ajusta divisor de clock
    pwm_init(slice_num, &config, true);
    pwm_set_gpio_level(BUZZER_PIN, 0); // Desliga o PWM inicialmente
}

void beep(int duration)
{
    gpio_put(BUZZER_PIN, 1); // Liga o buzzer
    sleep_ms(duration);      // Aguarda o tempo especificado
    gpio_put(BUZZER_PIN, 0); // Desliga o buzzer
}

void playTone(uint frequency, uint duration_ms)
{
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);
    uint32_t clock_freq = clock_get_hz(clk_sys);
    uint32_t top = clock_freq / frequency - 1;

    pwm_set_wrap(slice_num, top);
    pwm_set_gpio_level(BUZZER_PIN, top / 2); // 50% de duty cycle

    sleep_ms(duration_ms);

    pwm_set_gpio_level(BUZZER_PIN, 0); // Desliga o som após a duração
}
