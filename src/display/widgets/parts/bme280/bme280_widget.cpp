#include "bme280_widget.h"

#include "display/LovyanGFX/display_LovyanGFX.h"
#include "display/widgets/ui_widget.h"
#include "display/widgets/common/card/ui_value_row.h"
#include "res/ui_theme/ui_theme.h"
#include <stdio.h>

void BME280Widget_DrawTitle(const BME280WidgetLayout& l)
{
    const auto& theme = UI_GetTheme();

    int padding = UI_Padding();

    int titleH = Display_GetFontHeight(theme.font_body);
    int titleW = Display_GetTextWidth("BME280", theme.font_body);

    int x = l.x + padding;
    int y = l.y - titleH / 2;

    // 🔲 чорний фон під тайтл
    Display_FillRect(
        x - 4,
        y - 2,
        titleW + 8,
        titleH + 4,
        0x0000        // чорний
    );

    // ✍️ текст поверх
    Display_DrawTextEx(
        x,
        y,
        "BME280",
        theme.sensor_title_color,  // білий
        0x0000,
        false,
        theme.font_body,
        0
    );
}

void BME280Widget_DrawValues(
    const BME280Data& data,
    const BME280WidgetLayout& l
)
{
    const auto& theme = UI_GetTheme();

    int rowH = Display_GetFontHeight(theme.font_small);
    int rowsH = rowH * 3 + 2 * 2;

    // 🔥 центр КАРТКИ, без тайтла
    int y = l.y + (l.h - rowsH) / 2;

    int x = l.x + UI_Padding();
    int w = l.w - UI_Padding() * 2;

    UIValueRowLayout row = {
        .labelX = x,
        .valueX = x + w / 2,
        .y = y,
        .valueW = w / 2
    };

    char buf[16];

    if (!data.valid)
    {
        UIValueRow_Draw("—", "No data", row, theme.text_dim, true);
        return;
    }

    snprintf(buf, sizeof(buf), "%.1f C", data.temperature);
    UIValueRow_Draw("Temp", buf, row, theme.text, true);
    row.y += rowH + 2;

    snprintf(buf, sizeof(buf), "%.1f %%", data.humidity);
    UIValueRow_Draw("Hum", buf, row, theme.text, true);
    row.y += rowH + 2;

    snprintf(buf, sizeof(buf), "%.0f hPa", data.pressure);
    UIValueRow_Draw("Pres", buf, row, theme.text, true);
}