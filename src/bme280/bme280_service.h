#pragma once
#include "system/system_state.h"

void BME280_Init();
void BME280_Update(SystemState& state);
bool BME280_IsOk();