//path: src/display/widgets/common/card/ui_card.h
#pragma once

struct UICardLayout
{
    int x;
    int y;
    int w;
    int h;
};

void UI_DrawCard(const UICardLayout& l);