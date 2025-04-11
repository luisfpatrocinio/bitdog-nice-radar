/**
 * @file text.h
 * @brief Header file for the text drawing module.
 *
 * This module provides functions for drawing text on the SSD1306 display.
 */

 #ifndef TEXT_H
 #define TEXT_H
 
 #define TEXT_HEIGHT 8 // Height of the text in pixels
 #define TEXT_WIDTH 6  // Width of the text in pixels
 
 #include "display.h"
 #include <math.h>
 
 /**
  * @brief Draws text for a header.
  * @param x X-coordinate of the text.
  * @param y Y-coordinate of the text.
  * @param text The text to draw.
  */
 void drawHeader(int x, int y, char *text);
 
 /**
  * @brief Draws text to the screen.
  * @param x X-coordinate of the text.
  * @param y Y-coordinate of the text.
  * @param text The text to draw.
  */
 void drawText(int x, int y, char *text);
 
 /**
  * @brief Draws centered text to the screen.
  * @param text The text to draw.
  * @param _y The Y-coordinate of the text, -1 to center.
  */
 void drawTextCentered(char *text, int _y);
 
 /**
  * @brief Draws a wave to the screen.
  * @param y Y-coordinate of the wave.
  * @param speed Speed of the wave animation.
  * @param amplitude Amplitude of the wave.
  */
 void drawWave(int y, float speed, float amplitude);
 
 #endif