#include "system/system_state.h"
#include "system/system_control.h"
#include "system/time/time_service.h"
#include "system/time/rtc_service.h"
#include "system/serial_commands.h"
#include "controls/controls.h"
#include "rgb/runtime/rgb_runtime.h"
#include "rgb/strip/rgb_strip.h"
#include "display/display_ui.h"
#include "display/LovyanGFX/display_LovyanGFX.h"
#include "res/ui_color_palette.h"

void setup()
{
    SerialCommands_Init();

    Serial.println("BOOT");
    Serial.println("System_Init");
    System_Init();

    Serial.println("Controls_Init");
    Controls_Init();

    Serial.println("RTC_Init");
    RTC_Init();
        if (RTC_IsOk()) {
            Serial.println("✓ RTC OK");
        } else {
            Serial.println("❌ RTC FAILED - time will not be accurate!");
        }

    SystemState& state = System_GetMutable();
    RTC_Update(state);

    Serial.println("RGB_Runtime_Init");
    RGB_Runtime_Init();

    Serial.println("RGB_strip_Init");
    RGB_strip_Init();

    Serial.println("Display_Init");
    Display_Init();

        // Тестовий вивід на дисплей
    Display_Clear(UI_COLOR_BG);
    Display_DrawText(10, 10, 1, "System Ready", UI_COLOR_TEXT);
    delay(1000);

    Serial.println("SETUP DONE");
    Serial.println("");

    // Показуємо довідку
    SerialCommands_PrintHelp();
}   

void loop()
{
    SerialCommands_Process();

    ControlEvent ev = Controls_Update();
    switch (ev)
    {
        case CTRL_BTN_POWER_HOLD:
            System_TogglePower();
            break;
        case CTRL_BTN_POWER_TAP:
            System_NextMode();
            break;
        default:
            break;
    }

    SystemState& state = System_GetMutable();
    RTC_Update(state);
    RGB_Runtime_Update(state);
    DisplayUI_Render(state);
    RGB_strip_Render(
        RGB_Runtime_GetStrip1(),
        RGB_Runtime_GetStrip2(),
        RGB_Runtime_GetBrightness()
    );
}
