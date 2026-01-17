#pragma once
#include "system/system_state.h"

struct UIWidget
{
    void Init() {}
    void Update(const SystemState& state) {}
    void Render() {}
};
