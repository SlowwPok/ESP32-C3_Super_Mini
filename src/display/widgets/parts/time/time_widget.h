#pragma once
#include "system/system_state.h"

enum TimeWidgetFormat
{
    TIME_FULL_12H   // Sat 24 Jan 2026 10:07 PM
};

void TimeWidget_SetFormat(TimeWidgetFormat format);
void TimeWidget_MarkDirty();

void TimeWidget_Update(const SystemState& state);
void TimeWidget_Draw(int x, int y, int h);

int TimeWidget_EstimatedWidth();