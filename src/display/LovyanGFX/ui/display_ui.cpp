#include "display_ui.h"

#include "display/LovyanGFX/display_LovyanGFX.h"
#include "display/LovyanGFX/display_LovyanGFX_config.h"
#include "rgb_strip/rgb_modes.h"

// layout constants
static const int PADDING = 10;
static const int COLOR_BOX = 14;

static void drawStripColors(
    int y,
    const RGB* colors,
    int count
)
{
    int x = PADDING;

    for (int i = 0; i < count; i++)
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

void DisplayUI_Render(const SystemState& state)
{
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

    const RGBMode& mode = RGB_modes_Get(state.currentMode);

    char title[32];
    snprintf(title, sizeof(title), "MODE %d", state.currentMode);

    Display_DrawText(PADDING, PADDING, 2, title, COLOR_WHITE);

    int y = PADDING + 30;

    if (mode.type == MODE_ANIMATED)
    {
        Display_DrawText(PADDING, y, 1, "ANIMATED", COLOR_GRAY);
        y += 16;

        const RGBMode& base = RGB_modes_Get(mode.animated.baseModeIndex);

        Display_DrawText(PADDING, y, 1, "STRIP 1", COLOR_WHITE);
        y += 12;
        drawStripColors(y, base.perPixel.strip1, NUMPIXELS);

        y += COLOR_BOX + 8;
        Display_DrawText(PADDING, y, 1, "STRIP 2", COLOR_WHITE);
        y += 12;
        drawStripColors(y, base.perPixel.strip2, NUMPIXELS);
    }
    else
    {
        Display_DrawText(PADDING, y, 1, "STRIP 1", COLOR_WHITE);
        y += 12;
        drawStripColors(y, mode.perPixel.strip1, NUMPIXELS);

        y += COLOR_BOX + 8;
        Display_DrawText(PADDING, y, 1, "STRIP 2", COLOR_WHITE);
        y += 12;
        drawStripColors(y, mode.perPixel.strip2, NUMPIXELS);
    }
}
