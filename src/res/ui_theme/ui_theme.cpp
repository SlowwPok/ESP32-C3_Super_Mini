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
    UIFonts::Title_16pt7b(),
    UIFonts::Body_10pt7b(),
    UIFonts::Small_8pt7b(),

    // layout
    10,   // padding
    24,   // header height
    20    // footer height
};

const UITheme& UI_GetTheme()
{
    return defaultTheme;
}