#pragma once
#include <stdint.h>

struct UIValueRowLayout
{
    int x;
    int y;
    int w;

    int valueX;
    int valueW;
};

void UIValueRow_Draw(
    const char* label,
    const char* value,
    const UIValueRowLayout& l,
    uint16_t color,
    bool force = false
);