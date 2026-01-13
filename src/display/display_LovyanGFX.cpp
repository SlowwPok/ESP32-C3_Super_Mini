#include "display/display_LovyanGFX.h"
#include "display/display_LovyanGFX_config.h"
#include <LovyanGFX.hpp>

// ===== INTERNAL DISPLAY CLASS =====
class LGFX_Impl : public lgfx::LGFX_Device {
  // тут твій Bus_SPI, Panel_ST7789 і т.д.
};

// ❗ ЄДИНИЙ ЕКЗЕМПЛЯР
static LGFX_Impl lcd;

// ===== PUBLIC API =====

void Display_Init()
{
  lcd.init();
  lcd.setRotation(DISPLAY_ROTATION);
  lcd.fillScreen(UI_BLACK);
}

void Display_Clear(uint32_t color)
{
  lcd.fillScreen(color);
}

int Display_Width()  { return lcd.width();  }
int Display_Height() { return lcd.height(); }

void Display_DrawLine(int x0, int y0, int x1, int y1, uint32_t color)
{
  lcd.drawLine(x0, y0, x1, y1, color);
}

void Display_DrawRect(int x, int y, int w, int h, uint32_t color)
{
  lcd.drawRect(x, y, w, h, color);
}

void Display_FillRect(int x, int y, int w, int h, uint32_t color)
{
  lcd.fillRect(x, y, w, h, color);
}

void Display_DrawText(int x, int y, const char* text, uint32_t color)
{
  lcd.setTextColor(color);
  lcd.setCursor(x, y);
  lcd.print(text);
}
