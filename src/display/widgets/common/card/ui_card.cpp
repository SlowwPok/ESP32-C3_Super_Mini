//path: src/display/widgets/common/card/ui_card.cpp
#include "ui_card.h"

#include "display/LovyanGFX/display_LovyanGFX.h"
#include "res/ui_theme/ui_theme.h"

static constexpr int CARD_RADIUS = 10;

void UI_DrawCard(const UICardLayout& l)
{
    const auto& theme = UI_GetTheme();

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
}