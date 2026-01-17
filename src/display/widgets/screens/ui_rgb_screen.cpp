#include "ui_rgb_screen.h"

#include "display/LovyanGFX/display_LovyanGFX.h"
#include "rgb/runtime/rgb_runtime.h"
#include "rgb/modes/rgb_modes.h"
#include "rgb/strip/rgb_config.h"

static RGB previewStrip1[RGB_STRIP_LENGTH];
static RGB previewStrip2[RGB_STRIP_LENGTH];

// dirty state
static uint8_t lastMode       = 0xFF;
static bool    lastAnimated   = false;
static uint8_t lastBrightness = 0xFF;
static uint8_t lastBaseMode   = 0xFF;

static bool dirty = true;

// layout
static const int BODY_TOP   = 30;
static const int PADDING    = 10;
static const int COLOR_BOX  = 14;

void UI_RGBScreen_Init()
{
    dirty = true;
}

static void BuildRGBPreview(
    const RGBMode& mode,
    RGB* outStrip1,
    RGB* outStrip2
)
{
    if (mode.type == MODE_SOLID)
    {
        for (int i = 0; i < RGB_STRIP_LENGTH; i++)
        {
            outStrip1[i] = mode.solid.strip1;
            outStrip2[i] = mode.solid.strip2;
        }
        return;
    }

    if (mode.type == MODE_PER_PIXEL)
    {
        for (int i = 0; i < RGB_STRIP_LENGTH; i++)
        {
            outStrip1[i] = mode.perPixel.strip1[i];
            outStrip2[i] = mode.perPixel.strip2[i];
        }
        return;
    }

    if (mode.type == MODE_ANIMATED)
    {
        const RGBMode& base = RGB_modes_Get(mode.animated.baseModeIndex);

        if (base.type == MODE_SOLID)
        {
            for (int i = 0; i < RGB_STRIP_LENGTH; i++)
            {
                outStrip1[i] = base.solid.strip1;
                outStrip2[i] = base.solid.strip2;
            }
        }
        else if (base.type == MODE_PER_PIXEL)
        {
            for (int i = 0; i < RGB_STRIP_LENGTH; i++)
            {
                outStrip1[i] = base.perPixel.strip1[i];
                outStrip2[i] = base.perPixel.strip2[i];
            }
        }
    }
}

void UI_RGBScreen_Update(const SystemState&)
{
    uint8_t activeMode = RGB_Runtime_GetActiveMode();
    bool animated      = RGB_Runtime_IsAnimated();
    uint8_t brightness = RGB_Runtime_GetBrightness();
    uint8_t baseMode   = RGB_Runtime_GetBaseMode();

    if (activeMode != lastMode ||
        animated   != lastAnimated ||
        brightness != lastBrightness ||
        baseMode   != lastBaseMode)
    {
        lastMode       = activeMode;
        lastAnimated   = animated;
        lastBrightness = brightness;
        lastBaseMode   = baseMode;

        const RGBMode& mode = RGB_modes_Get(activeMode);
        BuildRGBPreview(mode, previewStrip1, previewStrip2);


        dirty = true;
    }
}

static void DrawRGBPreview(
    int x,
    int y,
    const RGB* strip,
    int count,
    int boxSize,
    int gap
)
{
    for (int i = 0; i < count; i++)
    {
        uint16_t c565 = Display_ColorFromRGB_ForPreview(strip[i]);
        Display_FillRect(x, y, boxSize, boxSize, c565);
        Display_DrawRect(x, y, boxSize, boxSize, COLOR_WHITE);
        x += boxSize + gap;
    }
}

void UI_RGBScreen_Render()
{
    if (!dirty)
        return;

    int y = BODY_TOP;

    Display_DrawText(PADDING, y, 1, "STRIP 1", COLOR_WHITE);
    y += 12;

    DrawRGBPreview(
        PADDING,
        y,
        previewStrip1,
        RGB_STRIP_LENGTH,
        COLOR_BOX,
        4
    );

    y += COLOR_BOX + 8;
    Display_DrawText(PADDING, y, 1, "STRIP 2", COLOR_WHITE);
    y += 12;

    DrawRGBPreview(
        PADDING,
        y,
        previewStrip2,
        RGB_STRIP_LENGTH,
        COLOR_BOX,
        4
    );

    dirty = false;
}
