//path: src/display/widgets/parts/bme280/bme280_widget.cpp
#include "bme280_widget.h"

#include "display/LovyanGFX/display_LovyanGFX.h"
#include "display/widgets/ui_widget.h"
#include "res/ui_theme/ui_theme.h"
#include "display/widgets/common/card/ui_value_row.h"
#include <stdio.h>

static constexpr int CARD_RADIUS = 8;

static float lastTemp = NAN;
static float lastHum  = NAN;
static float lastPres = NAN;
static bool  lastValid = false;

void BME280Widget_Draw(
    const BME280Data& data,
    const BME280WidgetLayout& l
)
{
    const auto& theme = UI_GetTheme();

    // ---- розміри ----
    int titleH = Display_GetFontHeight(theme.font_body);
    int rowH   = Display_GetFontHeight(theme.font_small);

    int contentH =
        titleH + 4 +
        rowH * 3 + 2 * 2; // 3 рядки + відступи

    // ---- центрування В КАРТЦІ ----
    int cx = l.x + UI_Padding();
    int cy = l.y + (l.h - contentH) / 2;

    int rowW = l.w - UI_Padding() * 2;

    // ---- title ----
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

    cy += titleH + 4;

    // ---- рядки ----
    char buf[16];

    if (!data.valid)
    {
        UIValueRow_Draw(
            "",
            "No data",
            {
                cx,
                cy,
                rowW,
                cx,          // valueX
                rowW         // valueW
            },
            theme.text_dim,
            true
        );
        return;
    }

    snprintf(buf, sizeof(buf), "%.1f C", data.temperature);
    UIValueRow_Draw(
        "Temp",
        buf,
        {
            cx,
            cy,
            rowW,
            cx,
            rowW
        },
        theme.text,
        true
    );

    cy += rowH + 2;

    snprintf(buf, sizeof(buf), "%.1f %%", data.humidity);
    UIValueRow_Draw(
        "Hum",
        buf,
        {
            cx,
            cy,
            rowW,
            cx,
            rowW
        },
        theme.text,
        true
    );

    cy += rowH + 2;

    snprintf(buf, sizeof(buf), "%.0f hPa", data.pressure);
    UIValueRow_Draw(
        "Pres",
        buf,
        {
            cx,
            cy,
            rowW,
            cx,
            rowW
        },
        theme.text,
        true
    );
}