#pragma once
#include <stdint.h>

struct UIValueRowLayout
{
    int labelX;
    int valueX;
    int y;
    int valueW;
};

void UIValueRow_Draw(
    const char* label,
    const char* value,
    const UIValueRowLayout& l,
    uint16_t color,
    bool drawLabel
);