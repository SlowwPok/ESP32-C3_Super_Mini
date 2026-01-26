#include "ui_value_row.h"

#include "display/LovyanGFX/display_LovyanGFX.h"
#include "display/widgets/ui_widget.h"
#include "res/ui_theme/ui_theme.h"

void UIValueRow_Draw(
    const char* label,
    const char* value,
    const UIValueRowLayout& l,
    uint16_t color,
    bool drawLabel
)
{
    const auto& theme = UI_GetTheme();
    int h = Display_GetFontHeight(theme.font_small);

    if (drawLabel)
    {
        Display_DrawTextEx(
            l.x,
            l.y,
            label,
            theme.text_dim,
            theme.bg,
            false,
            theme.font_small,
            0
        );
    }

    // чистимо ТІЛЬКИ value
    Display_FillRect(
        l.valueX,
        l.y,
        l.valueW,
        h,
        theme.bg
    );

    int valueWidth = Display_GetTextWidth(value, theme.font_small);

    Display_DrawTextEx(
        l.valueX + l.valueW - valueWidth,
        l.y,
        value,
        color,
        theme.bg,
        false,
        theme.font_small,
        0
    );
}