#pragma once
#include "system/system_state.h"
#include "rgb/strip/rgb_types.h"

void RGB_Runtime_Init();
void RGB_Runtime_Update(const SystemState& state);

const RGB* RGB_Runtime_GetStrip1();
const RGB* RGB_Runtime_GetStrip2();

uint8_t RGB_Runtime_GetActiveMode();
uint8_t RGB_Runtime_GetBaseMode();
uint8_t RGB_Runtime_GetBrightness();
bool    RGB_Runtime_IsAnimated();

const char* RGB_Runtime_GetActiveModeName();
const char* RGB_Runtime_GetBaseModeName();
uint16_t RGB_Runtime_GetAnimSpeedMs();
uint8_t  RGB_Runtime_GetAnimIntensity();