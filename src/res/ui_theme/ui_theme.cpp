// path: src/res/ui_theme/ui_theme.cpp
#include "ui_theme.h"

#include "res/fonts/ui_fonts.h"
#include "res/ui_color_palette.h"

static UITheme defaultTheme = {
    // colors
    UI_COLOR_BG,
    UI_COLOR_TEXT,
    UI_COLOR_DIM_TEXT,
    UI_COLOR_BOUNDARY,

    // fonts
    UIFonts::Body_10pt7b(), // title font
    UIFonts::Small_8pt7b(), // body font
    UIFonts::Small_8pt7b(), // small font

    // layout
    10,   // padding
    22,   // header height
    18    // footer height
};

const UITheme& UI_GetTheme()
{
    return defaultTheme;
}