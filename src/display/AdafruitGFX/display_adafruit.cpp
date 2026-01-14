#include "display_adafruit.h"
#include "display_adafruit_config.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

// ===== СИНГЛТОН ЕКЗЕМПЛЯР ДИСПЛЕЯ =====
static Adafruit_ST7789 tft(TFT_CS, TFT_DC, TFT_RST);

// ===== ІНІЦІАЛІЗАЦІЯ ДИСПЛЕЯ =====
void Display_Init()
{
  // Ініціалізація SPI шини
  SPI.begin(
    TFT_SCK,    // SCK
    -1,         // MISO (ST7789 не використовує)
    TFT_MOSI,   // MOSI
    TFT_CS      // CS
  );
  delay(10); // Затримка для стабілізації

  // Ініціалізація дисплея з розмірами (висота, ширина для ST7789)
  tft.init(DISP_HEIGHT, DISP_WIDTH);
  tft.setRotation(DISP_ROTATION);
  tft.fillScreen(COLOR_BLACK); //RGB(0, 0, 0)
}

// ===== ОЧИСТКА ЕКРАНУ =====
void Display_Clear(uint16_t color)
{
  tft.fillScreen(color);
}

// ===== ЗАПОВНЕНИЙ ПРЯМОКУТНИК =====
void Display_FillRect(int x, int y, int w, int h, uint16_t color)
{
  tft.fillRect(x, y, w, h, color);
}

// ===== КОНТУР ПРЯМОКУТНИКА =====
void Display_DrawRect(int x, int y, int w, int h, uint16_t color)
{
  tft.drawRect(x, y, w, h, color);
}

// ===== ЛІНІЯ =====
void Display_DrawLine(int x0, int y0, int x1, int y1, uint16_t color)
{
  tft.drawLine(x0, y0, x1, y1, color);
}

// ===== ТЕКСТ =====
void Display_DrawText(int x, int y, const char* text, uint16_t color, uint8_t size)
{
  tft.setTextColor(color);
  tft.setTextSize(size);
  tft.setCursor(x, y);
  tft.print(text);
}
