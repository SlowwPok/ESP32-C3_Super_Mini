#include "system/system_state.h"
#include "system/system_control.h"
#include "system/time/time_service.h"
#include "system/time/rtc_service.h"

#include "controls/controls.h"

#include "rgb/runtime/rgb_runtime.h"
#include "rgb/strip/rgb_strip.h"

#include "display/display_ui.h"
#include "display/LovyanGFX/display_LovyanGFX.h"

void setup()
{
    Serial.begin(115200);
    delay(3000);   // ⬅️ ОБОВʼЯЗКОВО для ESP32-C3 + PlatformIO

    Serial.println("BOOT");

    Serial.println("System_Init");
    System_Init();

    Serial.println("Controls_Init");
    Controls_Init();

    Serial.println("RTC_Init");
    RTC_Init();
    Serial.println("RTC_Init DONE");

    Serial.println("RTC_Update first sync");
    SystemState& state = System_GetMutable();
    RTC_Update(state);   // ← ОДИН РАЗ
    Serial.println("RTC_Update first sync = done");

    Serial.println("RGB_Runtime_Init");
    RGB_Runtime_Init();

    Serial.println("RGB_strip_Init");
    RGB_strip_Init();
    Serial.println("RGB_strip_Init DONE");

    Serial.println("Display_Init");
    Display_Init();
    Serial.println("Display_Init DONE");

    Serial.println("SETUP DONE");
}   

void loop()
{
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

    TimeService_Update();

    RGB_Runtime_Update(state);
    DisplayUI_Render(state);

    RGB_strip_Render(
        RGB_Runtime_GetStrip1(),
        RGB_Runtime_GetStrip2(),
        RGB_Runtime_GetBrightness()
    );
}
