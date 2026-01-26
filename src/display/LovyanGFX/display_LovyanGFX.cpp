//path: src/display/LovyanGFX/display_LovyanGFX.cpp
#include "display/LovyanGFX/display_LovyanGFX_config.h"
#include "display/LovyanGFX/display_LovyanGFX.h"
#include "rgb/strip/rgb_types.h"
#include <LovyanGFX.hpp>

// ===== КЛАС ДЛЯ ІНІЦІАЛІЗАЦІЇ ДИСПЛЕЯ LOVYANGFX =====
class LGFX : public lgfx::LGFX_Device {
  lgfx::Bus_SPI _bus;
  lgfx::Panel_ST7789 _panel;

public:
  LGFX() {
    // --- Конфігурація SPI шини ---
    auto busCfg = _bus.config();
    busCfg.spi_host = SPI2_HOST;   // ❗ ESP32-C3
    busCfg.spi_mode = 0;
    busCfg.freq_write = 8000000;
    busCfg.pin_sclk = PIN_SCLK;
    busCfg.pin_mosi = PIN_MOSI;
    busCfg.pin_miso = -1;
    busCfg.pin_dc   = PIN_DC;
    _bus.config(busCfg);
    _panel.setBus(&_bus);

    // --- Конфігурація панелі дисплея ---
    auto panelCfg = _panel.config();
    panelCfg.pin_cs  = PIN_CS;
    panelCfg.pin_rst = PIN_RST;
    panelCfg.panel_width  = DISP_PANEL_WIDTH;
    panelCfg.panel_height = DISP_PANEL_HEIGHT;
    panelCfg.memory_width  = DISP_MEMORY_WIDTH;
    panelCfg.memory_height = DISP_MEMORY_HEIGHT;
    panelCfg.offset_x = DISP_OFFSET_X;
    panelCfg.offset_y = DISP_OFFSET_Y;
    panelCfg.offset_rotation = 0;
    panelCfg.invert    = DISP_INVERT;
    panelCfg.rgb_order = DISP_RGB_ORDER;

    _panel.config(panelCfg);
    setPanel(&_panel);
  }
};

// ===== СИНГЛТОН ЕКЗЕМПЛЯР ДИСПЛЕЯ =====
static LGFX lcd;

// ===== ФУНКЦІЇ API =====

void Display_Init() {
  lcd.init();
  pinMode(PIN_BL, OUTPUT);
  digitalWrite(PIN_BL, HIGH); // увімкнути підсвітку
  lcd.setColorDepth(16); // RGB565
  lcd.setRotation(DISP_ROTATION);
}

void Display_Clear(uint16_t color) {
  lcd.fillScreen(color);
}

void Display_DrawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
  lcd.drawRect(x, y, w, h, color);
}

void Display_FillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
  lcd.fillRect(x, y, w, h, color);
}

void Display_FillRoundRect(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    int16_t radius,
    uint16_t color
)
{
    lcd.fillRoundRect(x, y, w, h, radius, color);
}

void Display_DrawRoundRect(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    int16_t radius,
    uint16_t color
)
{
    lcd.drawRoundRect(x, y, w, h, radius, color);
}

int Display_GetFontHeight(const lgfx::v1::IFont* font)
{
    lcd.setFont(font ? font : &lgfx::fonts::Font0);
    return lcd.fontHeight();
}

/** Просте малювання тексту (bitmap font).
 *
 * @param x     X координата
 * @param y     Y координата
 * @param size  Розмір тексту (1–3)
 * @param text  Текст
 * @param color Колір тексту
 */
void Display_DrawText(
  int16_t x,
  int16_t y,
  uint8_t size,
  const char* text,
  uint16_t color
)
{
  lcd.setCursor(x, y);
  lcd.setFont(&lgfx::fonts::Font0); // стандартний шрифт
  lcd.setTextSize(size);
  lcd.setTextColor(color);          // без фону
  lcd.print(text);
}

/**
 * Розширене малювання тексту.
 *
 * @param x       X координата
 * @param y       Y координата
 * @param text    Текст
 * @param color   Колір тексту
 * @param bg      Колір фону
 * @param use_bg  Малювати фон чи ні
 * @param font    Шрифт (nullptr = Font0)
 * @param size    Розмір bitmap-шрифту (ігнорується для FreeFont)
 */
void Display_DrawTextEx(
  int16_t x,
  int16_t y,
  const char* text,
  uint16_t color,
  uint16_t bg,
  bool use_bg,
  const lgfx::v1::IFont* font,
  uint8_t size
)
{
  lcd.setCursor(x, y);

  if (font)
  {
    lcd.setFont(font);   // FreeFont або FontX
  }
  else
  {
    lcd.setFont(&lgfx::fonts::Font0);
    lcd.setTextSize(size);
  }

  if (use_bg)
    lcd.setTextColor(color, bg);
  else
    lcd.setTextColor(color);

  lcd.print(text);
}

int Display_Width()  { return lcd.width(); }
int Display_Height() { return lcd.height(); }

void Display_DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
  lcd.drawLine(x0, y0, x1, y1, color);
}

void Display_Sleep()
{
  digitalWrite(PIN_BL, LOW);  // ❗ гасимо підсвітку
  lcd.sleep();                // опціонально, не обовʼязково
}

void Display_Wakeup()
{
  lcd.wakeup();               // опціонально
  digitalWrite(PIN_BL, HIGH); // ❗ вмикаємо підсвітку
}

uint16_t Display_ColorFromRGB_ForPreview(const RGB& c)
{
    uint8_t r = c.r;
    uint8_t g = c.g;
    uint8_t b = c.b;

    uint8_t maxc = max(r, max(g, b));

    // якщо дуже темно — піднімаємо для візуалізації
    if (maxc > 0 && maxc < 20)
    {
        float k = 20.0f / maxc;
        uint16_t rr = r * k;
        uint16_t gg = g * k;
        uint16_t bb = b * k;

        r = rr > 255 ? 255 : rr;
        g = gg > 255 ? 255 : gg;
        b = bb > 255 ? 255 : bb;
    }

    return
        ((r & 0xF8) << 8) |
        ((g & 0xFC) << 3) |
        (b >> 3);
}
