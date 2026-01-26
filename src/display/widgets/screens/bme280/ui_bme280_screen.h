#pragma once
#include "system/system_state.h"

void UI_BME280Screen_Init();
void UI_BME280Screen_Update(const SystemState& state);
void UI_BME280Screen_Render();