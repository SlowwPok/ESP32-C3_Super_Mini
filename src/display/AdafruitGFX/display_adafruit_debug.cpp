#include "display_adafruit_debug.h"
#include "display_adafruit_config.h"
#include "display_adafruit.h"

// ===== ФУНКЦІЯ МАЛЮВАННЯ ДЕБАГ ПАТЕРНУ =====
void Display_DebugPattern()
{
  // 1️⃣ Жорсткий reset картинки
  Display_Clear(COLOR_BLACK); //RGB(0, 0, 0)

  // 2️⃣ ПОВНА рамка дисплея (критично)
  Display_DrawRect(0, 0, DISP_WIDTH, DISP_HEIGHT, COLOR_WHITE); //RGB(255, 255, 255)

  // 3️⃣ ЛІВА та ПРАВА крайові смуги
  Display_FillRect(0, 0, 6, DISP_HEIGHT, COLOR_RED);                         //RGB(255, 0, 0) // LEFT EDGE
  Display_FillRect(DISP_WIDTH - 6, 0, 6, DISP_HEIGHT, COLOR_BLUE);           //RGB(0, 0, 255) // RIGHT EDGE

  // 4️⃣ Верхня та нижня крайові смуги
  Display_FillRect(0, 0, DISP_WIDTH, 6, COLOR_GREEN);                        //RGB(0, 255, 0) // TOP EDGE
  Display_FillRect(0, DISP_HEIGHT - 6, DISP_WIDTH, 6, COLOR_MAGENTA);        //RGB(255, 0, 255) // BOTTOM EDGE

  // 5️⃣ Вертикальні мітки кожні 10px по ширині
  for (int x = 0; x < DISP_WIDTH; x += 10)
  {
    Display_DrawLine(x, 0, x, 12, COLOR_YELLOW); //RGB(255, 255, 0)
    Display_DrawLine(x, DISP_HEIGHT - 12, x, DISP_HEIGHT, COLOR_YELLOW); //RGB(255, 255, 0)
  }

  // 6️⃣ Горизонтальні мітки кожні 10px по висоті
  for (int y = 0; y < DISP_HEIGHT; y += 10)
  {
    Display_DrawLine(0, y, 12, y, COLOR_CYAN); //RGB(0, 255, 255)
    Display_DrawLine(DISP_WIDTH - 12, y, DISP_WIDTH, y, COLOR_CYAN); //RGB(0, 255, 255)
  }

  // 7️⃣ Центр
  Display_DrawLine(DISP_WIDTH / 2, 0, DISP_WIDTH / 2, DISP_HEIGHT, COLOR_WHITE); //RGB(255, 255, 255)
  Display_DrawLine(0, DISP_HEIGHT / 2, DISP_WIDTH, DISP_HEIGHT / 2, COLOR_WHITE); //RGB(255, 255, 255)

  // 8️⃣ ЯВНІ ТЕКСТОВІ МІТКИ КРАЇВ
  Display_DrawText(8, 8, "LEFT EDGE", COLOR_RED, 1); //RGB(255, 0, 0)
  Display_DrawText(DISP_WIDTH - 80, 8, "RIGHT EDGE", COLOR_BLUE, 1); //RGB(0, 0, 255)
  Display_DrawText(8, DISP_HEIGHT - 16, "BOTTOM", COLOR_MAGENTA, 1); //RGB(255, 0, 255)
  Display_DrawText(8, DISP_HEIGHT / 2 - 8, "CENTER", COLOR_WHITE, 1); //RGB(255, 255, 255)

  // 9️⃣ Діагностика
  char buf[32];
  sprintf(buf, "W=%d H=%d", DISP_WIDTH, DISP_HEIGHT);
  Display_DrawText(8, 30, buf, COLOR_WHITE, 1); //RGB(255, 255, 255)
}
