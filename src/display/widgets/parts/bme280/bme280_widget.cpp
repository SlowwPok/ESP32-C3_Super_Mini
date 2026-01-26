#include "bme280_widget.h"

#include "display/LovyanGFX/display_LovyanGFX.h"
#include "display/widgets/ui_widget.h"
#include "res/ui_theme/ui_theme.h"
#include <stdio.h>

static constexpr int CARD_RADIUS = 8;

void BME280Widget_Draw(
    const BME280Data& data,
    const BME280WidgetLayout& l
)
{
    const auto& theme = UI_GetTheme();

    // Card background
    Display_FillRoundRect(
    l.x, l.y, l.w, l.h,
    CARD_RADIUS,
    theme.bg
    );

    Display_DrawRoundRect(
        l.x, l.y, l.w, l.h,
        CARD_RADIUS,
        theme.lines_color
    );

    int cx = l.x + UI_Padding();
    int cy = l.y + UI_Padding();

    // Title
    Display_DrawTextEx(
        cx,
        cy,
        "BME280",
        theme.text,
        theme.bg,
        false,
        theme.font_body,
        0
    );

    cy += Display_GetFontHeight(theme.font_body) + 4;

    char buf[32];

    if (!data.valid)
    {
        Display_DrawTextEx(
            cx,
            cy,
            "No data",
            theme.text_dim,
            theme.bg,
            false,
            theme.font_small,
            0
        );
        return;
    }

    // Temperature
    snprintf(buf, sizeof(buf), "Temp: %.1f C", data.temperature);
    Display_DrawTextEx(
        cx,
        cy,
        buf,
        theme.text,
        theme.bg,
        false,
        theme.font_small,
        0
    );
    cy += Display_GetFontHeight(theme.font_small) + 2;

    // Humidity
    snprintf(buf, sizeof(buf), "Hum:  %.1f %%", data.humidity);
    Display_DrawTextEx(
        cx,
        cy,
        buf,
        theme.text,
        theme.bg,
        false,
        theme.font_small,
        0
    );
    cy += Display_GetFontHeight(theme.font_small) + 2;

    // Pressure
    snprintf(buf, sizeof(buf), "Pres: %.0f hPa", data.pressure);
    Display_DrawTextEx(
        cx,
        cy,
        buf,
        theme.text,
        theme.bg,
        false,
        theme.font_small,
        0
    );
}