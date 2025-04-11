/**
 * @file display.h
 * @brief Header file for the SSD1306 OLED display module.
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include "hardware/i2c.h"
#include "ssd1306.h"

/** @brief Width of the OLED display (in pixels). */
#define SCREEN_WIDTH 128
/** @brief Height of the OLED display (in pixels). */
#define SCREEN_HEIGHT 64
/** @brief I2C address of the SSD1306 display. */
#define SCREEN_ADDRESS 0x3C
/** @brief GPIO pin used for I2C data (SDA). */
#define I2C_SDA 14
/** @brief GPIO pin used for I2C clock (SCL). */
#define I2C_SCL 15

/** @brief Global variable representing the SSD1306 display. */
extern ssd1306_t display;

/** @brief Initializes the I2C interface. */
void initI2C();

/** @brief Initializes the SSD1306 display. */
void initDisplay();

/** @brief Clears the SSD1306 display. */
void clearDisplay();

/** @brief Displays the content on the SSD1306 display. */
void showDisplay();

/** @brief Inverts the display colors. */
void invertDisplay(uint8_t invert);

#endif // DISPLAY_H