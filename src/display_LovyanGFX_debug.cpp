#include "display_LovyanGFX.h"
#include "display_LovyanGFX_config.h"

void Display_DrawGrid() {
  int w = Display_Width();
  int h = Display_Height();

  Display_Clear(UI_BLACK);

  for (int x = 0; x <= w; x += GRID_STEP) {
    Display_DrawLine(x, 0, x, h, UI_DARKGREY);
  }

  for (int y = 0; y <= h; y += GRID_STEP) {
    Display_DrawLine(0, y, w, y, UI_DARKGREY);
  }

  Display_DrawRect(0, 0, w, h, UI_WHITE);
  Display_DrawText(5, 5, "0,0", UI_YELLOW);
}
