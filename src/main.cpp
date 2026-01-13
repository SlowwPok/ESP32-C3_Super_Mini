#include <Arduino.h>
#include "rgb_strip.h"
#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_ST7789 _panel;
  lgfx::Bus_SPI _bus;

public:
  LGFX() {
    auto cfg = _bus.config();
    cfg.spi_host = SPI2_HOST;
    cfg.spi_mode = 0;
    cfg.freq_write = 8000000;
    cfg.pin_sclk = 9;
    cfg.pin_mosi = 8;
    cfg.pin_miso = -1;
    cfg.pin_dc   = 7;
    _bus.config(cfg);
    _panel.setBus(&_bus);

    auto pcfg = _panel.config();
    pcfg.pin_cs   = 21;
    pcfg.pin_rst  = 10;

    pcfg.memory_width  = 170;
    pcfg.memory_height = 320;
    pcfg.panel_width   = 170;
    pcfg.panel_height  = 320;

    pcfg.offset_x = 35; 
    pcfg.offset_y = 0;

    pcfg.invert = true;
    pcfg.rgb_order = false; // BGR

    _panel.config(pcfg);
    setPanel(&_panel);
  }
};

LGFX lcd;

void drawGrid() {
  int w = lcd.width();
  int h = lcd.height();

  lcd.fillScreen(TFT_BLACK);

  // грід
  for (int x = 0; x <= w; x += 10) {
    lcd.drawLine(x, 0, x, h, TFT_DARKGREY);
  }

  for (int y = 0; y <= h; y += 10) {
    lcd.drawLine(0, y, w, y, TFT_DARKGREY);
  }

  // рамка
  lcd.drawRect(0, 0, w, h, TFT_WHITE);

  // логічний 0,0
  lcd.setTextColor(TFT_YELLOW);
  lcd.setTextSize(1);
  lcd.setCursor(5, 5);
  lcd.print("0,0");

  // центр екрана
  int cx = w / 2;
  int cy = h / 2;
  int s  = 16; // розмір квадрата

  // центральний
  lcd.fillRect(cx - s/2, cy - s/2, s, s, TFT_WHITE);

  // ліво
  lcd.fillRect(cx - s*2, cy - s/2, s, s, TFT_RED);

  // право
  lcd.fillRect(cx + s, cy - s/2, s, s, TFT_GREEN);

  // верх
  lcd.fillRect(cx - s/2, cy - s*2, s, s, TFT_BLUE);

  // низ
  lcd.fillRect(cx - s/2, cy + s, s, s, TFT_MAGENTA);
}

void setup()
{
  lcd.init();
  lcd.setRotation(3);
  drawGrid();


  // Initialize the RGB strip
  RGB_strip_Init();
}

void loop()
{
    RGB_strip_Update();
}
