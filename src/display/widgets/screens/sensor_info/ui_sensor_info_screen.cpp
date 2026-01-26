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
    // для початку — завжди dirty
    // пізніше оптимізуємо
    cachedState = state;
    dirty = true;
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

    int cardH = bodyH / 4;
    int cardW = Display_Width() / 2;

    BME280WidgetLayout layout = {
        .x = padding,
        .y = bodyTop + padding,
        .w = cardW,
        .h = cardH
    };

    BME280Widget_Draw(cachedState, layout);

    dirty = false;
}