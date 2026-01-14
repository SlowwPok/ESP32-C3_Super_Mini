#pragma once
#include <Arduino.h>
#include <stdint.h>

// ===== ІНІЦІАЛІЗАЦІЯ / ОЧИСТКА =====
void Display_Init();
void Display_Clear(uint16_t color = 0x0000); //RGB(0, 0, 0)

// ===== ГЕОМЕТРІЯ =====
int Display_Width();
int Display_Height();

// ===== ПРИМІТИВИ МАЛЮВАННЯ =====
void Display_DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
void Display_DrawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void Display_FillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void Display_DrawText(int16_t x, int16_t y, const char* text, uint16_t color);

// ===== ДЕБАГ =====
void Display_DrawGrid();
