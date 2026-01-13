#include "display_LovyanGFX.h"
#include <LovyanGFX.hpp>

// ===== LGFX IMPLEMENTATION =====

class LGFX_Impl : public lgfx::LGFX_Device {
  // ...
};

// ❗ ПРИВАТНИЙ ЕКЗЕМПЛЯР
static LGFX_Impl lcd;

// ===== PUBLIC API IMPLEMENTATION =====

// ⬇⬇⬇ ОСЬ СЮДИ ⬇⬇⬇

int Display_Width() {
  return lcd.width();
}

int Display_Height() {
  return lcd.height();
}

void Display_DrawLine(int x0, int y0, int x1, int y1, uint32_t color) {
  lcd.drawLine(x0, y0, x1, y1, color);
}

void Display_DrawRect(int x, int y, int w, int h, uint32_t color) {
  lcd.drawRect(x, y, w, h, color);
}

void Display_FillRect(int x, int y, int w, int h, uint32_t color) {
  lcd.fillRect(x, y, w, h, color);
}

void Display_DrawText(int x, int y, const char* text, uint32_t color) {
  lcd.setTextColor(color);
  lcd.setCursor(x, y);
  lcd.print(text);
}
