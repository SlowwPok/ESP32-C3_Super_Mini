#include "display_LovyanGFX.h"
#include "display_LovyanGFX_config.h"

// ===== ДОПОМІЖНА ФУНКЦІЯ =====
static void drawCross(int x, int y, uint16_t c)
{
  Display_DrawLine(x - 6, y, x + 6, y, c);
  Display_DrawLine(x, y - 6, x, y + 6, c);
}

// ===== ФУНКЦІЯ МАЛЮВАННЯ СІТКИ =====
void Display_DrawGrid()
{
  int w = Display_Width();
  int h = Display_Height();

  Display_Clear(COLOR_BLACK); //RGB(0, 0, 0)

  // ===== СІТКА =====
  for (int x = 0; x < w; x += 20)
    Display_DrawLine(x, 0, x, h, COLOR_GRAY); //RGB(128, 64, 128)

  for (int y = 0; y < h; y += 20)
    Display_DrawLine(0, y, w, y, COLOR_GRAY); //RGB(128, 64, 128)

  // ===== РАМКА =====
  Display_DrawRect(0, 0, w - 1, h - 1, COLOR_WHITE); //RGB(255, 255, 255)

  // ===== ХРЕСТИКИ ПО КУТАХ =====
  drawCross(0, 0, COLOR_RED); //RGB(255, 0, 0)
  drawCross(w - 1, 0, COLOR_GREEN); //RGB(0, 255, 0)
  drawCross(0, h - 1, COLOR_BLUE); //RGB(0, 0, 255)
  drawCross(w - 1, h - 1, COLOR_MAGENTA); //RGB(255, 0, 255)

  // ===== ЦЕНТРАЛЬНИЙ ХРЕСТИК =====
  drawCross(w / 2, h / 2, COLOR_YELLOW); //RGB(255, 255, 0)

  // ===== ПАЛІТРА КОЛЬОРІВ =====
  const uint16_t colors[] = {
    COLOR_RED,    //RGB(255, 0, 0)
    COLOR_GREEN,  //RGB(0, 255, 0)
    COLOR_BLUE,   //RGB(0, 0, 255)
    COLOR_YELLOW, //RGB(255, 255, 0)
    COLOR_MAGENTA,//RGB(255, 0, 255)
    COLOR_WHITE   //RGB(255, 255, 255)
  };

  const int sw = 30;
  const int sh = 30;
  const int startX = 10;
  const int startY = h - sh - 10;

  for (int i = 0; i < 6; i++) {
    Display_FillRect(
      startX + i * (sw + 5),
      startY,
      sw,
      sh,
      colors[i]
    );
  }

  // ===== ТЕКСТОВА ІНФОРМАЦІЯ =====
  Display_DrawText(5, 5, 1, "DISPLAY TEST", COLOR_WHITE); //RGB(255, 255, 255)

  char buf[32];
  snprintf(buf, sizeof(buf), "%dx%d rot=%d", w, h, DISP_ROTATION);
  Display_DrawText(5, 20, 1, buf, COLOR_YELLOW); //RGB(255, 255, 0)
}

// ===== ФУНКЦІЯ МАЛЮВАННЯ ДЕБАГ ПАТЕРНУ =====
void Display_DrawDebugPattern()
{
  int w = Display_Width();
  int h = Display_Height();

  // Фон
  Display_Clear(COLOR_BLACK); //RGB(0, 0, 0)

  // ─── ШАХМАТНА РАМКА ───
  int cell = 10;
  for (int y = 0; y < h; y += cell) {
    for (int x = 0; x < w; x += cell) {
      if (((x / cell) + (y / cell)) & 1) {
        Display_FillRect(x, y, cell, cell, COLOR_WHITE); //RGB(255, 255, 255)
      }
    }
  }

  // ─── КОЛЬОРОВА СМУГА ───
  uint16_t colors[] = {
    COLOR_WHITE,  //RGB(255, 255, 255)
    COLOR_YELLOW, //RGB(255, 255, 0)
    COLOR_CYAN,   //RGB(0, 255, 255)
    COLOR_GREEN,  //RGB(0, 255, 0)
    COLOR_MAGENTA,//RGB(255, 0, 255)
    COLOR_RED,    //RGB(255, 0, 0)
    COLOR_BLUE,   //RGB(0, 0, 255)
    COLOR_BLACK   //RGB(0, 0, 0)
  };

  int barH = h / 12;
  int barY = h / 2 - barH / 2;
  int barW = w / 7;

  for (int i = 0; i < 7; i++) {
    Display_FillRect(i * barW, barY, barW, barH, colors[i]);
  }

  // ─── ХРЕСТИКИ ПО КУТАХ ───
  drawCross(0, 0, COLOR_RED); //RGB(255, 0, 0)
  drawCross(w - 1, 0, COLOR_GREEN); //RGB(0, 255, 0)
  drawCross(0, h - 1, COLOR_BLUE); //RGB(0, 0, 255)
  drawCross(w - 1, h - 1, COLOR_YELLOW); //RGB(255, 255, 0)

  // ─── ТЕКСТ ───
  Display_DrawTextEx(10, 10, "LovyanGFX Library", COLOR_BLACK, COLOR_RED, true, nullptr, 2); //RGB(255, 0, 255)
  Display_DrawText(10, 26, 1, "ST7789 DEBUG", COLOR_BLACK); //RGB(255, 0, 255)
  Display_DrawText(10, 42, 1, "RGB565 OK", COLOR_BLACK); //RGB(255, 0, 255)
  Display_DrawText(10, 58, 1, "ROTATION = 3", COLOR_BLACK); //RGB(255, 0, 255)
}