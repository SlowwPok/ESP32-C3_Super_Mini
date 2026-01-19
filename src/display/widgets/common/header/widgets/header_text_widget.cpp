// path: src/display/widgets/common/header/widgets/header_text_widget.cpp
#include "header_text_widget.h"

#include "display/LovyanGFX/display_LovyanGFX.h"
#include "res/ui_theme/ui_theme.h"

static const char* TEXT = "ESP32-C3 Super Mini";

void HeaderTextWidget::Draw(int x, int y, int h)
{
    const auto& theme = UI_GetTheme();

    int textH = Display_GetFontHeight(theme.font_small);
    int ty = y + (h - textH) / 2;

    Display_DrawTextEx(
        x,
        ty,
        TEXT,
        theme.header_text,
        theme.bg,
        false,
        theme.font_small,
        0
    );
}