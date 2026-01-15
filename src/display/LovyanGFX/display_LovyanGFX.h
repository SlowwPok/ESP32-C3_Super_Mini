#pragma once
#include <Arduino.h>
#include <stdint.h>
#include <LovyanGFX.hpp>

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
void Display_DrawText(
  int16_t x,
  int16_t y,
  uint8_t size,
  const char* text,
  uint16_t color
);

void Display_DrawTextEx(
  int16_t x,
  int16_t y,
  const char* text,
  uint16_t color,
  uint16_t bg,
  bool use_bg,
  const lgfx::v1::IFont* font,
  uint8_t size
);

// ===== POWER =====
void Display_Sleep();
void Display_Wakeup();

// ===== ДЕБАГ =====
void Display_DrawGrid();
