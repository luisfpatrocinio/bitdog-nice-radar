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

    // Calcula o "top" (máximo valor de contagem do PWM)
    float div = 16.0f; // Usar divisor 1.0 para maior resolução
    uint32_t top = (uint32_t)(CLOCK_PWM / (frequency * div)) - 1;

    pwm_set_clkdiv(slice_num, div);          // Configura divisor corretamente
    pwm_set_wrap(slice_num, top);            // Define topo
    pwm_set_gpio_level(BUZZER_PIN, top / 2); // 50% duty cycle

    sleep_ms(duration_ms);

    pwm_set_gpio_level(BUZZER_PIN, 0); // Para o som
}
