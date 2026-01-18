//path: src/display/widgets/screens/ui_rgb_screen.cpp
#include "ui_rgb_screen.h"

#include "display/LovyanGFX/display_LovyanGFX.h"
#include "display/widgets/ui_widget.h"

#include "rgb/runtime/rgb_runtime.h"
#include "rgb/modes/rgb_modes.h"
#include "rgb/strip/rgb_config.h"

#include "res/ui_color_palette.h"
#include "res/fonts/ui_fonts.h"

static RGB previewStrip1[RGB_STRIP_LENGTH];
static RGB previewStrip2[RGB_STRIP_LENGTH];

// dirty state
static uint8_t lastMode       = 0xFF;
static bool    lastAnimated   = false;
static uint8_t lastBrightness = 0xFF;
static uint8_t lastBaseMode   = 0xFF;

static bool dirty = true;

static constexpr int COLOR_BOX = 14;
static constexpr int COLOR_GAP = 4;
static constexpr uint8_t UI_PREVIEW_BRIGHTNESS = 255;

static RGB ApplyBrightness(const RGB& c, uint8_t brightness)
{
    RGB out;
    out.r = (uint16_t)c.r * brightness / 255;
    out.g = (uint16_t)c.g * brightness / 255;
    out.b = (uint16_t)c.b * brightness / 255;
    return out;
}

void UI_RGBScreen_Init()
{
    dirty = true;
}

static void BuildRGBPreview(
    const RGBMode& mode,
    uint8_t uiBrightness,
    RGB* outStrip1,
    RGB* outStrip2
)
{
    if (mode.type == MODE_SOLID)
    {
        for (int i = 0; i < RGB_STRIP_LENGTH; i++)
        {
            outStrip1[i] = ApplyBrightness(mode.solid.strip1, uiBrightness);
            outStrip2[i] = ApplyBrightness(mode.solid.strip2, uiBrightness);
        }
        return;
    }

    if (mode.type == MODE_PER_PIXEL)
    {
        for (int i = 0; i < RGB_STRIP_LENGTH; i++)
        {
            outStrip1[i] = ApplyBrightness(mode.perPixel.strip1[i], uiBrightness);
            outStrip2[i] = ApplyBrightness(mode.perPixel.strip2[i], uiBrightness);
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
                outStrip1[i] = ApplyBrightness(base.solid.strip1, uiBrightness);
                outStrip2[i] = ApplyBrightness(base.solid.strip2, uiBrightness);
            }
        }
        else if (base.type == MODE_PER_PIXEL)
        {
            for (int i = 0; i < RGB_STRIP_LENGTH; i++)
            {
                outStrip1[i] = ApplyBrightness(base.perPixel.strip1[i], uiBrightness);
                outStrip2[i] = ApplyBrightness(base.perPixel.strip2[i], uiBrightness);
            }
        }
    }
}

void UI_RGBScreen_Update(const SystemState&)
{
    uint8_t activeMode = RGB_Runtime_GetActiveMode();
    uint8_t brightness = RGB_Runtime_GetBrightness();
    uint8_t baseMode   = RGB_Runtime_GetBaseMode();
    const RGBMode& mode = RGB_modes_Get(activeMode);
    bool animated = (mode.type == MODE_ANIMATED);
    uint8_t uiBrightness = UI_PREVIEW_BRIGHTNESS;

    if (activeMode != lastMode ||
        animated   != lastAnimated ||
        baseMode   != lastBaseMode)
    {
        lastMode       = activeMode;
        lastAnimated   = animated;
        lastBrightness = brightness;
        lastBaseMode   = baseMode;

        const RGBMode& mode = RGB_modes_Get(activeMode);
        BuildRGBPreview(mode, uiBrightness, previewStrip1, previewStrip2);

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
        Display_DrawRect(x, y, boxSize, boxSize, UI_COLOR_TEXT);
        x += boxSize + gap;
    }
}

void UI_RGBScreen_Render()
{
    if (!dirty)
        return;

    int y = UI_BodyTop() + UI_PADDING;
    int bodyTop    = UI_BodyTop();
    int bodyBottom = UI_BodyBottom();

    Display_FillRect(
        0,
        bodyTop,
        Display_Width(),
        bodyBottom - bodyTop,
        UI_COLOR_BG
    );

    // ---- MODE TITLE ----
    char title[32];

    snprintf(
        title,
        sizeof(title),
        "[%02d] %s",
        RGB_Runtime_GetActiveMode(),
        RGB_Runtime_GetActiveModeName()
    );

    Display_DrawTextEx(
        UI_PADDING,
        y,
        title,
        UI_COLOR_TEXT,
        UI_COLOR_BG,
        false,
        UIFonts::Title_16pt7b(),
        0
    );

    y += 12;

    // ---- MODE DETAILS ----
    char buf[32];

    const RGBMode& mode = RGB_modes_Get(RGB_Runtime_GetActiveMode());

    if (mode.type == MODE_ANIMATED)
    {
        const RGBMode& base = RGB_modes_Get(mode.animated.baseModeIndex);

        snprintf(
            buf,
            sizeof(buf),
            "%s | Base: %s",
            mode.name,
            base.name
        );
    }
    else
    {
        snprintf(
            buf,
            sizeof(buf),
            "%s",
            mode.name
        );
    }

    Display_DrawTextEx(
        UI_PADDING,
        y,
        buf,
        UI_COLOR_DIM_TEXT,
        UI_COLOR_BG,
        false,
        UIFonts::Body_10pt7b(),
        0
    );

    y += 12;

    // ---- BRIGHTNESS ----
    snprintf(
        buf,
        sizeof(buf),
        "Brightness: %d",
        RGB_Runtime_GetBrightness()
    );

    Display_DrawTextEx(
        UI_PADDING,
        y,
        buf,
        UI_COLOR_DIM_TEXT,
        UI_COLOR_BG,
        false,
        UIFonts::Small_8pt7b(),
        0
    );
    
    y += 16;

    Display_DrawTextEx(
        UI_PADDING,
        y,
        "STRIP 1",
        UI_COLOR_TEXT,
        UI_COLOR_BG,
        false,
        UIFonts::Small_8pt7b(),
        0
    );
    y += 12;

    DrawRGBPreview(
        UI_PADDING,
        y,
        previewStrip1,
        RGB_STRIP_LENGTH,
        COLOR_BOX,
        4
    );

    y += COLOR_BOX + 8;
    Display_DrawTextEx(
        UI_PADDING,
        y,
        "STRIP 2",
        UI_COLOR_TEXT,
        UI_COLOR_BG,
        false,
        UIFonts::Small_8pt7b(),
        0
    );
    y += 12;

    DrawRGBPreview(
        UI_PADDING,
        y,
        previewStrip2,
        RGB_STRIP_LENGTH,
        COLOR_BOX,
        4
    );

    dirty = false;
}
