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

void setup()
{
    

  lcd.init();
  lcd.fillScreen(TFT_RED);

  delay(500);

  RGB_strip_Init();
}

void loop()
{
    RGB_strip_Update();
}
