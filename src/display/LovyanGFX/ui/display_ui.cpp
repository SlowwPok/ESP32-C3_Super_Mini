#include "display_ui.h"

#include "display/LovyanGFX/display_LovyanGFX.h"
#include "display/LovyanGFX/display_LovyanGFX_config.h"
#include "rgb_runtime/rgb_runtime.h"
#include "rgb_strip/rgb_config.h"   // RGB_STRIP_LENGTH

static bool     lastPowerOn   = false;
static uint8_t  lastMode      = 0xFF;
static bool     lastAnimated  = false;

// ===== Layout =====
static const int PADDING   = 10;
static const int COLOR_BOX = 14;

// ===== Helpers =====
static void drawStripColors(int y, const RGB* colors)
{
    int x = PADDING;

    for (int i = 0; i < RGB_STRIP_LENGTH; i++)
    {
        uint16_t c565 =
            ((colors[i].r & 0xF8) << 8) |
            ((colors[i].g & 0xFC) << 3) |
            (colors[i].b >> 3);

        Display_FillRect(x, y, COLOR_BOX, COLOR_BOX, c565);
        Display_DrawRect(x, y, COLOR_BOX, COLOR_BOX, COLOR_WHITE);
        x += COLOR_BOX + 4;
    }
}

// ===== Main UI =====
void DisplayUI_Render(const SystemState& state)
{
    uint8_t activeMode = RGB_Runtime_GetActiveMode();
    bool animated      = RGB_Runtime_IsAnimated();

    bool needRedraw =
        state.powerOn != lastPowerOn ||
        activeMode    != lastMode    ||
        animated      != lastAnimated;

    if (!needRedraw)
        return;

    lastPowerOn  = state.powerOn;
    lastMode     = activeMode;
    lastAnimated = animated;

    Display_Clear(COLOR_BLACK);

    if (!state.powerOn)
    {
        Display_DrawText(
            Display_Width() / 2 - 20,
            Display_Height() / 2,
            2,
            "OFF",
            COLOR_GRAY
        );
        return;
    }

    const RGB* strip1 = RGB_Runtime_GetStrip1();
    const RGB* strip2 = RGB_Runtime_GetStrip2();

    char title[32];
    snprintf(title, sizeof(title),
             animated ? "ANIM %d" : "MODE %d",
             activeMode);

    Display_DrawText(PADDING, PADDING, 2, title, COLOR_WHITE);

    int y = PADDING + 30;

    Display_DrawText(PADDING, y, 1, "STRIP 1", COLOR_WHITE);
    y += 12;
    drawStripColors(y, strip1, RGB_STRIP_LENGTH);

    y += COLOR_BOX + 8;
    Display_DrawText(PADDING, y, 1, "STRIP 2", COLOR_WHITE);
    y += 12;
    drawStripColors(y, strip2, RGB_STRIP_LENGTH);
}
