#include "buttons.h"

void initializeButtons() {
    // Configura os pinos dos botões como entradas com pull-up
    gpio_init(BTA);
    gpio_set_dir(BTA, GPIO_IN);
    gpio_pull_up(BTA);

    gpio_init(BTB);
    gpio_set_dir(BTB, GPIO_IN);
    gpio_pull_up(BTB);
}

void setButtonCallback(void (*handleButtonGpioEvent)(uint gpio, uint32_t events)) {
    // Configura a interrupção para os botões
    gpio_set_irq_enabled_with_callback(BTA, GPIO_IRQ_EDGE_RISE, true, handleButtonGpioEvent);
    gpio_set_irq_enabled_with_callback(BTB, GPIO_IRQ_EDGE_RISE, true, handleButtonGpioEvent);
}