/**
 * @file display.c
 * @brief Driver for initializing and controlling the SSD1306 display using I2C.
 *
 * This file contains functions to initialize the I2C interface and the SSD1306 display,
 * clear the display, show content on the display, and invert display colors.
 *
 * @note Ensure that the I2C peripheral and GPIO pins are correctly defined and available in your hardware setup.
 */

#include "display.h"
ssd1306_t display;

/**
 * @brief Initializes the I2C interface with a specified frequency and configures the GPIO pins.
 *
 * This function sets up the I2C interface on the specified I2C peripheral (i2c1) with a frequency of 400 kHz.
 * It configures the GPIO pins for I2C data (SDA) and clock (SCL) functions and enables the pull-up resistors
 * on these pins. After initialization, it prints a confirmation message to the console.
 *
 * @note Ensure that the I2C peripheral and GPIO pins are correctly defined and available in your hardware setup.
 */
void initI2C()
{
    i2c_init(i2c1, 400 * 1000); // 400 kHz
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    printf("I2C inicializado\n");
}

/**
 * @brief Initializes the SSD1306 display.
 *
 * This function initializes the SSD1306 display with the specified parameters.
 * It checks if the initialization is successful and prints a message accordingly.
 *
 * @note The function uses the global variables `display`, `SCREEN_WIDTH`, `SCREEN_HEIGHT`,
 * `SCREEN_ADDRESS`, and `i2c1` for initialization.
 *
 * @return void
 */
void initDisplay()
{
    if (!ssd1306_init(&display, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_ADDRESS, i2c1))
    {
        printf("Falha ao inicializar o display SSD1306\n");
    }
    else
    {
        printf("Display SSD1306 inicializado\n");
    }
}

/**
 * @brief Clears the SSD1306 display.
 *
 * This function clears the contents of the SSD1306 display by calling the
 * ssd1306_clear function and passing the display instance.
 */
void clearDisplay()
{
    ssd1306_clear(&display);
}

/**
 * @brief Displays the content on the SSD1306 display.
 *
 * This function calls the ssd1306_display function with the global display
 * variable to update the content shown on the SSD1306 OLED display.
 */
void showDisplay()
{
    ssd1306_show(&display);
}
/**
 * @brief Inverts the display colors.
 *
 * This function inverts the colors of the display. When the invert parameter
 * is set to a non-zero value, the display colors will be inverted. When the
 * invert parameter is set to zero, the display colors will return to normal.
 *
 * @param invert A uint8_t value indicating whether to invert the display colors.
 *               - 0: Normal display colors.
 *               - Non-zero: Inverted display colors.
 */

void invertDisplay(uint8_t invert)
{
    ssd1306_invert(&display, invert);
}