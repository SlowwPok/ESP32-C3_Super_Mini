//path src/display/LovyanGFX/display_LovyanGFX.h
#pragma once
#include <Arduino.h>
#include <stdint.h>
#include <LovyanGFX.hpp>

#include "display/LovyanGFX/display_LovyanGFX_config.h"
#include "rgb/strip/rgb_types.h"
#include "rgb/modes/rgb_modes.h"


// ===== INIT / CLEAR =====
void Display_Init();
void Display_Clear(uint16_t color = 0x0000);

// ===== GEOMETRY =====
int Display_Width();
int Display_Height();

// ===== COLORS =====
uint16_t Display_ColorFromRGB_ForPreview(const RGB& c);

// ===== DRAW PRIMITIVES =====
void Display_DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
void Display_DrawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void Display_FillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

int Display_GetFontHeight(
  const lgfx::v1::IFont* font
);

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

void Display_FillRoundRect(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    int16_t radius,
    uint16_t color
);

void Display_DrawRoundRect(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    int16_t radius,
    uint16_t color
);

// ===== POWER =====
void Display_Sleep();
void Display_Wakeup();