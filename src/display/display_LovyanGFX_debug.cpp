#include "display/display_LovyanGFX.h"
#include "display/display_LovyanGFX_config.h"

void Display_DrawGrid()
{
  int w = Display_Width();
  int h = Display_Height();

  Display_Clear(UI_BLACK);

  for (int x = 0; x <= w; x += GRID_STEP)
    Display_DrawLine(x, 0, x, h, UI_DARKGREY);

  for (int y = 0; y <= h; y += GRID_STEP)
    Display_DrawLine(0, y, w, y, UI_DARKGREY);

  Display_DrawRect(0, 0, w, h, UI_WHITE);
  Display_DrawText(5, 5, "0,0", UI_YELLOW);

  int cx = w / 2;
  int cy = h / 2;
  int s  = TEST_SQUARE_SIZE;

  Display_FillRect(cx - s/2, cy - s/2, s, s, UI_WHITE);
  Display_FillRect(cx - s*2, cy - s/2, s, s, UI_RED);
  Display_FillRect(cx + s,   cy - s/2, s, s, UI_GREEN);
  Display_FillRect(cx - s/2, cy - s*2, s, s, UI_BLUE);
  Display_FillRect(cx - s/2, cy + s,   s, s, UI_MAGENTA);
}
