#include "ui_rgb_preview.h"

#include "display/LovyanGFX/display_LovyanGFX.h"
#include "rgb/runtime/rgb_runtime.h"
#include "rgb/modes/rgb_modes.h"
#include "rgb/strip/rgb_config.h"

static RGB previewStrip1[RGB_STRIP_LENGTH];
static RGB previewStrip2[RGB_STRIP_LENGTH];

// dirty state
static uint8_t lastMode      = 0xFF;
static bool    lastAnimated  = false;
static uint8_t lastBrightness = 0xFF;
static uint8_t lastBaseMode   = 0xFF;

static bool dirty = true;

// layout (локально, не в UI)
static const int PADDING   = 10;
static const int COLOR_BOX = 14;

void UI_RGBPreview_Init()
{
    dirty = true;
}

void UI_RGBPreview_Update(const SystemState&)
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
        Display_BuildRGBPreview(mode, previewStrip1, previewStrip2);

        dirty = true;
    }
}

void UI_RGBPreview_Render()
{
    if (!dirty)
        return;

    int y = 80; // тимчасово, пізніше винесемо layout

    Display_DrawText(PADDING, y, 1, "STRIP 1", COLOR_WHITE);
    y += 12;

    Display_DrawRGBPreview(
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

    Display_DrawRGBPreview(
        PADDING,
        y,
        previewStrip2,
        RGB_STRIP_LENGTH,
        COLOR_BOX,
        4
    );

    dirty = false;
}
