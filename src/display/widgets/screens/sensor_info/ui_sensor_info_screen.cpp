#include "ui_sensor_info_screen.h"

#include "display/LovyanGFX/display_LovyanGFX.h"
#include "display/widgets/ui_widget.h"
#include "res/ui_theme/ui_theme.h"

// widgets
#include "display/widgets/parts/bme280/bme280_widget.h"

static bool dirty = true;
static SystemState cachedState;

void UI_SensorInfoScreen_Init()
{
    dirty = true;
}

void UI_SensorInfoScreen_Update(const SystemState& state)
{
    static float lastT = 0;
    static float lastH = 0;
    static float lastP = 0;
    static bool  lastValid = false;
    static bool  first = true;

    if (first ||
        state.bme.valid       != lastValid ||
        state.bme.temperature != lastT ||
        state.bme.humidity    != lastH ||
        state.bme.pressure    != lastP)
    {
        cachedState = state;
        dirty = true;

        lastValid = state.bme.valid;
        lastT = state.bme.temperature;
        lastH = state.bme.humidity;
        lastP = state.bme.pressure;
        first = false;
    }
}

void UI_SensorInfoScreen_Render()
{
    if (!dirty)
        return;

    const auto& theme = UI_GetTheme();

    int bodyTop    = UI_BodyTop();
    int bodyBottom = UI_BodyBottom();
    int bodyH      = bodyBottom - bodyTop;

    // очистити body
    Display_FillRect(
        0,
        bodyTop,
        Display_Width(),
        bodyH,
        theme.bg
    );

    // ===== Layout =====
    int padding = UI_Padding();

    int bodyW = Display_Width();

    int cellW = (bodyW - padding * 3) / 2;
    int cellH = (bodyH - padding * 3) / 2;

    // TOP-LEFT card
    BME280WidgetLayout layout = {
        .x = padding,
        .y = bodyTop + padding,
        .w = cellW,
        .h = cellH
    };

    BME280Widget_Draw(cachedState, layout);

    dirty = false;
}