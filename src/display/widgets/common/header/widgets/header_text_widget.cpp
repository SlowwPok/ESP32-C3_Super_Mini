// path: src/display/widgets/common/header/widgets/header_text_widget.cpp
#include "header_text_widget.h"
#include "display/LovyanGFX/display_LovyanGFX.h"
#include "res/fonts/ui_fonts.h"
#include "res/ui_color_palette.h"

static const char* TEXT = "ESP32-C3 Super Mini";

void HeaderTextWidget::Draw(int x, int y, int h)
{
    auto font = UIFonts::Small_8pt7b();
    int textH = Display_GetFontHeight(font);
    int ty = y + (h - textH) / 2;

    Display_DrawTextEx(
        x,
        ty,
        TEXT,
        UI_COLOR_TEXT,
        UI_COLOR_BG,
        false,
        font,
        0
    );
}