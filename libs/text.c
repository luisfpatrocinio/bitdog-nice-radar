/**
 * @file text.c
 * @brief Implementation for the text drawing module.
 *
 * This module provides functions for drawing text on the SSD1306 display,
 * including headers, regular text, centered text, and animated waves.
 */

#include "text.h"
#include <string.h>
#include <stdio.h>

/**
 * @brief Draws text for a header.
 *
 * Uses ssd1306_draw_string with a scale of 2 for a larger, more prominent text.
 *
 * @param x X-coordinate of the text.
 * @param y Y-coordinate of the text.
 * @param text The text to draw.
 * @note To work with the text in different location in the screen you must
 *  send the local that function use.
 */
void drawHeader(int x, int y, char *text)
{
    ssd1306_draw_string(&display, x, y, 2, text);
}

/**
 * @brief Draws text to the screen.
 *
 * Uses ssd1306_draw_string with a scale of 1 for regular text.
 *
 * @param x X-coordinate of the text.
 * @param y Y-coordinate of the text.
 * @param text The text to draw.
 */
void drawText(int x, int y, char *text)
{
    ssd1306_draw_string(&display, x, y, 1, text);
}

/**
 * @brief Draws centered text to the screen.
 *
 * Calculates the X-coordinate to center the text horizontally and uses
 * ssd1306_draw_string to draw the text.
 *
 * @param text The text to draw.
 * @param _y The Y-coordinate of the text, -1 to center.
 * @note To use a defatul location, change _y to a negative number
 */
void drawTextCentered(char *text, int _y)
{
    if (_y == -1)
    {
        _y = SCREEN_HEIGHT / 2 - 6;
    }
    int _x = SCREEN_WIDTH / 2 - 6 * strlen(text) / 2 - 1;
    drawText(_x, _y, text);
}

/**
 * @brief Draws a wave to the screen.
 *
 * Animates a wave pattern by drawing lines with varying Y-coordinates
 * based on a sine function.
 *
 * @param y Y-coordinate of the wave.
 * @param speed Speed of the wave animation.
 * @param amplitude Amplitude of the wave.
 * @note This function is not generic, because of the static float variable.
 */
void drawWave(int y, float speed, float amplitude)
{
    static float time = 0;
    time += speed / 100.0;
    if (time > 2 * M_PI)
    {
        time = 0;
    }
    int _points = 12;
    for (int i = 0; i < _points; i++)
    {
        int _x1 = SCREEN_WIDTH / _points * i;
        int _x2 = SCREEN_WIDTH / _points * (i + 1);
        int _y1 = y + sin(time + i * 30) * amplitude;
        int _y2 = y + sin(time + (i + 1) * 30) * amplitude;
        ssd1306_draw_line(&display, _x1, _y1, _x2, _y2);
    }
}
