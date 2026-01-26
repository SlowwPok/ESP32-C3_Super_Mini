//path: src/display/widgets/screens/sensor_info/ui_sensor_info_screen.cpp
#include "ui_sensor_info_screen.h"
#include "display/widgets/common/card/ui_card.h"
#include "display/LovyanGFX/display_LovyanGFX.h"
#include "display/widgets/ui_widget.h"
#include "res/ui_theme/ui_theme.h"

// widgets
#include "display/widgets/parts/bme280/bme280_widget.h"

static bool layoutDirty = true;
static bool dataDirty   = true;

static BME280Data cachedBME;

void UI_SensorInfoScreen_Init()
{
    cachedBME = {};
    cachedBME.valid = false;

    layoutDirty = true;
    dataDirty   = true;
}

void UI_SensorInfoScreen_Update(const SystemState& state)
{
    if (state.bme.valid       != cachedBME.valid ||
        state.bme.temperature != cachedBME.temperature ||
        state.bme.humidity    != cachedBME.humidity ||
        state.bme.pressure    != cachedBME.pressure)
    {
        cachedBME = state.bme;
        dataDirty = true;
    }
}

void UI_SensorInfoScreen_Render()
{
    const auto& theme = UI_GetTheme();

    int bodyTop    = UI_BodyTop();
    int bodyBottom = UI_BodyBottom();
    int bodyH      = bodyBottom - bodyTop;

    int padding = UI_Padding();
    int bodyW = Display_Width();

    int cellW = (bodyW - padding * 3) / 2;
    int cellH = (bodyH - padding * 3) / 2;

    static UICardLayout cards[4];
    
    if (layoutDirty)
    {
        Display_FillRect(
            0,
            bodyTop,
            Display_Width(),
            bodyH,
            theme.bg
        );

        cards[0] = { padding, bodyTop + padding, cellW, cellH };
        cards[1] = { padding * 2 + cellW, bodyTop + padding, cellW, cellH };
        cards[2] = { padding, bodyTop + padding * 2 + cellH, cellW, cellH };
        cards[3] = { padding * 2 + cellW, bodyTop + padding * 2 + cellH, cellW, cellH };

        for (int i = 0; i < 4; i++)
            UI_DrawCard(cards[i]);

        layoutDirty = false;
        dataDirty   = true; // після layout треба оновити дані
    }
    if (dataDirty)
    {
        BME280WidgetLayout bmeLayout = {
            cards[0].x,
            cards[0].y,
            cards[0].w,
            cards[0].h
        };

        BME280Widget_Draw(cachedBME, bmeLayout);

        dataDirty = false;
    }
}