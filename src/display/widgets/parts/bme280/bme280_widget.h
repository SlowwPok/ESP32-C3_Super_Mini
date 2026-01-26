#pragma once
#include "system/system_state.h"

struct BME280WidgetLayout
{
    int x;
    int y;
    int w;
    int h;
};

void BME280Widget_DrawTitle(const BME280WidgetLayout& l);
void BME280Widget_DrawValues(
    const BME280Data& data,
    const BME280WidgetLayout& l
);