#pragma once
#include "system/system_state.h"

void RTC_Init();
void RTC_Update(SystemState& state);

void RTC_SetTime(int year, int month, int day, int hour, int minute, int second);