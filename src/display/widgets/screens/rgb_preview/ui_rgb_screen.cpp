//path: src/display/widgets/screens/ui_rgb_screen.cpp
#include "ui_rgb_screen.h"

#include "display/LovyanGFX/display_LovyanGFX.h"
#include "display/widgets/ui_widget.h"

#include "rgb/runtime/rgb_runtime.h"
#include "rgb/modes/rgb_modes.h"
#include "rgb/strip/rgb_config.h"

#include "res/ui_theme/ui_theme.h"

static RGB previewStrip1[RGB_STRIP_LENGTH];
static RGB previewStrip2[RGB_STRIP_LENGTH];

// dirty state
static uint8_t lastMode       = 0xFF;
static bool    lastAnimated   = false;
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
    int gap,
    uint16_t borderColor
)
{
    for (int i = 0; i < count; i++)
    {
        uint16_t c565 = Display_ColorFromRGB_ForPreview(strip[i]);
        Display_FillRect(x, y, boxSize, boxSize, c565);
        Display_DrawRect(x, y, boxSize, boxSize, borderColor);
        x += boxSize + gap;
    }
}

void UI_RGBScreen_Render()
{
    const auto& theme = UI_GetTheme();
    uint8_t activeMode = RGB_Runtime_GetActiveMode();
    const RGBMode& mode = RGB_modes_Get(activeMode);

    if (!dirty)
        return;

    int y = UI_BodyTop() + UI_Padding() - 2;
    int bodyTop    = UI_BodyTop();
    int bodyBottom = UI_BodyBottom();

    Display_FillRect(
        0,
        bodyTop,
        Display_Width(),
        bodyBottom - bodyTop,
        theme.bg
    );

    // ---- MODE TITLE ----
    char title[32];

    snprintf(
        title,
        sizeof(title),
        "[%02d] %s",
        activeMode,
        mode.name
    );

    Display_DrawTextEx(
        UI_Padding(),
        y,
        title,
        theme.text,
        theme.bg,
        false,
        theme.font_title,
        0
    );

    y += Display_GetFontHeight(theme.font_title);

    // ---- MODE DETAILS ----
    char buf[32];

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
        UI_Padding(),
        y,
        buf,
        theme.text_dim,
        theme.bg,
        false,
        theme.font_body,
        0
    );

    y += Display_GetFontHeight(theme.font_body) + 1;

    // ---- BRIGHTNESS ----
    snprintf(
        buf,
        sizeof(buf),
        "Brightness: %d",
        RGB_Runtime_GetBrightness()
    );

    Display_DrawTextEx(
        UI_Padding(),
        y,
        buf,
        theme.text_dim,
        theme.bg,
        false,
        theme.font_small,
        0
    );
    
    y += Display_GetFontHeight(theme.font_small) + 1;

    Display_DrawTextEx(
        UI_Padding(),
        y,
        "STRIP 1",
        theme.text,
        theme.bg,
        false,
        theme.font_small,
        0
    );
    y += Display_GetFontHeight(theme.font_small) + 1;

    DrawRGBPreview(
        UI_Padding(),
        y,
        previewStrip1,
        RGB_STRIP_LENGTH,
        COLOR_BOX,
        COLOR_GAP,
        theme.text
    );

    y += COLOR_BOX + 8;

    int previewHeight =
    Display_GetFontHeight(theme.font_small) + // "STRIP 2"
    4 +
    COLOR_BOX;                                // квадрати

    if (y + previewHeight > bodyBottom)
    {
        // немає місця — НЕ малюємо strip 2
        dirty = false;
        return;
    }

    Display_DrawTextEx(
        UI_Padding(),
        y,
        "STRIP 2",
        theme.text,
        theme.bg,
        false,
        theme.font_small,
        0
    );
    y += Display_GetFontHeight(theme.font_small) + 1;

    DrawRGBPreview(
        UI_Padding(),
        y,
        previewStrip2,
        RGB_STRIP_LENGTH,
        COLOR_BOX,
        COLOR_GAP,
        theme.text
    );

    dirty = false;
}
