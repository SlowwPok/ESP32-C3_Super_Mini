#pragma once
#include "system/system_state.h"

struct BME280WidgetLayout
{
    int x;
    int y;
    int w;
    int h;
};

void BME280Widget_Draw(
    const SystemState& state,
    const BME280WidgetLayout& layout
);