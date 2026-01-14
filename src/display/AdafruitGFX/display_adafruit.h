#pragma once
#include <Arduino.h>

// ===== ІНІЦІАЛІЗАЦІЯ / ОЧИСТКА =====
void Display_Init();
void Display_Clear(uint16_t color);

// ===== ДОПОМІЖНІ ФУНКЦІЇ МАЛЮВАННЯ =====
void Display_FillRect(int x, int y, int w, int h, uint16_t color);
void Display_DrawRect(int x, int y, int w, int h, uint16_t color);
void Display_DrawLine(int x0, int y0, int x1, int y1, uint16_t color);
void Display_DrawText(int x, int y, const char* text, uint16_t color, uint8_t size);