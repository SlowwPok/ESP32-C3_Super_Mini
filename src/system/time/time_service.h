#pragma once
#include "system/system_state.h"

/*
    TimeService
    -----------
    • Оновлює час раз на секунду
    • Пише ТІЛЬКИ в SystemState
    • НЕ знає про UI
    • НЕ знає про RTC (поки)
*/

void TimeService_Init();
void TimeService_Update(SystemState& state);