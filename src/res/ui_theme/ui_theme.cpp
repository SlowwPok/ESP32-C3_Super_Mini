// path: src/res/ui_theme/ui_theme.cpp
#include "ui_theme.h"

#include "res/fonts/ui_fonts.h"
#include "res/ui_color_palette.h"

static UITheme defaultTheme = {
    // colors
    UI_COLOR_BG,
    UI_COLOR_TEXT,
    UI_COLOR_DIM_TEXT,
    UI_COLOR_HEADER_TEXT,
    UI_COLOR_FOOTER_TEXT,
    UI_COLOR_TIME_TEXT,
    UI_COLOR_LINES,
    UI_COLOR_SENSOR_TITLE,

    // fonts
    UIFonts::Ubuntu_Bold_10(), // title font
    UIFonts::Ubuntu_Medium_8(), // body font
    UIFonts::Ubuntu_Bold_6(), // small font

    // layout
    10,   // padding
    22,   // header height
    18    // footer height
};

const UITheme& UI_GetTheme()
{
    return defaultTheme;
}