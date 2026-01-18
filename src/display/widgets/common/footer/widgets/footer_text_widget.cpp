// path: src/display/widgets/common/footer/widgets/footer_text_widget.cpp
#include "footer_text_widget.h"

#include "display/LovyanGFX/display_LovyanGFX.h"
#include "res/fonts/ui_fonts.h"
#include "res/ui_theme/ui_theme.h"
#include "res/ui_color_palette.h"

void FooterTextWidget::SetText(const char* text)
{
    _text = text ? text : "";
}

void FooterTextWidget::Draw(int x, int y, int h)
{
    const auto& theme = UI_GetTheme();

    int textH = Display_GetFontHeight(theme.font_small);
    int ty = y + (h - textH) / 2;

    Display_DrawTextEx(
        x,
        ty,
        _text,
        theme.text_dim,
        theme.bg,
        false,
        theme.font_small,
        0
    );
}