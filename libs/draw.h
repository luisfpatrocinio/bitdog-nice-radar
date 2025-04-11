/**
 * @file draw.h
 * @brief Header file for the drawing functions.
 *
 * This module provides function for draw images.
 */

#ifndef DRAW_H
#define DRAW_H

#include "display.h"

/**
 * @brief Draws an image on the SSD1306 display.
 *
 * @param data Pointer to the image data (bitmap).
 * @param size Size of the image data in bytes.
 * @param x X-coordinate of the top-left corner of the image.
 * @param y Y-coordinate of the top-left corner of the image.
 */
void drawImage(const uint8_t *data, const long size, int x, int y);

void drawLine(int x1, int y1, int x2, int y2);

void drawClearRectangle(int x, int y, int width, int height);
void drawRectangle(int x, int y, int width, int height);
void drawEmptyRectangle(int x, int y, int width, int height);

void drawPixel(int x, int y);

#endif // DRAW_H