#include "display_LovyanGFX_config.h"
#include "display_LovyanGFX.h"
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
  lcd.setColorDepth(16); // RGB565
  lcd.setRotation(DISP_ROTATION);
  Display_Clear(COLOR_BLACK); //RGB(0, 0, 0)
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

void Display_DrawText(int16_t x, int16_t y, const char* text, uint16_t color) {
  lcd.setCursor(x, y);
  lcd.setTextColor(color, COLOR_BLACK); //RGB(0, 0, 0)
  lcd.print(text);
}

int Display_Width()  { return lcd.width(); }
int Display_Height() { return lcd.height(); }

void Display_DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
  lcd.drawLine(x0, y0, x1, y1, color);
}