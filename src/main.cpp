#include "system/system_state.h"
#include "system/system_control.h"
#include "system/time/rtc_service.h"
#include "system/serial_commands.h"
#include "controls/controls.h"
#include "bme280/bme280_service.h"
#include "rgb/runtime/rgb_runtime.h"
#include "rgb/strip/rgb_strip.h"
#include "display/display_ui.h"
#include "display/LovyanGFX/display_LovyanGFX.h"
#include "res/ui_color_palette.h"

void setup()
{
    SerialCommands_Init();  // ✅ 1. Serial (має бути першим!)

    Serial.println("BOOT");
    Serial.println("System_Init");
    System_Init();  // ✅ 2. I2C ініціалізація

    Serial.println("Controls_Init");
    Controls_Init();  // ✅ 3. Кнопки (НЕ залежать від I2C)

    Serial.println("Display_Init");
    Display_Init();  // ✅ 4. Дисплей (SPI, НЕ I2C)
    Display_Wakeup();

    Serial.println("RGB_Runtime_Init");
    RGB_Runtime_Init();  // ✅ 5. RGB логіка

    Serial.println("RGB_strip_Init");
    RGB_strip_Init();  // ✅ 6. RGB ленти

    // ⚠️ I2C пристрої ОСТАННІМИ (можуть затримувати)
    Serial.println("RTC_Init");
    RTC_Init();
    if (RTC_IsOk()) {
        Serial.println("✓ RTC OK");
    } else {
        Serial.println("❌ RTC FAILED");
    }
    
    Serial.println("BME280_Init");
    BME280_Init();  // ✅ 7. BME280 останнім (може затримувати)

    SystemState& state = System_GetMutable();
    BME280_Update(state);
    RTC_Update(state);

    // ✅ Показуємо стартовий екран
    Display_Clear(UI_COLOR_BG);
    Display_DrawText(10, 10, 1, "System Ready", UI_COLOR_TEXT);
    delay(1000);

    Serial.println("SETUP DONE");
    Serial.println("");

    SerialCommands_PrintHelp();
} 

void loop()
{
    SerialCommands_Process();

    ControlEvent ev = Controls_Update();

    // ✅ Обробка кнопок
    switch (ev)
    {
        case CTRL_BTN_POWER_TAP:
        {
            Serial.println("BTN: TAP -> NextMode");
            System_NextMode();
            break;
        }

        case CTRL_BTN_POWER_HOLD:
        {
            Serial.println("BTN: HOLD -> TogglePower");
            System_TogglePower();
            break;
        }

        default:
            break;
    }

    SystemState& state = System_GetMutable();

    // ✅ Синхронізація екрану з powerOn
    static bool lastPowerOn = true;
    
    if (state.powerOn != lastPowerOn)
    {
        Serial.printf(
            "[POWER CHANGE] %d -> %d (millis=%lu)\n",
            lastPowerOn,
            state.powerOn,
            millis()
        );

        lastPowerOn = state.powerOn;

        if (!state.powerOn)
        {
            Serial.println("POWER OFF -> Sleep Display");
            Display_Sleep();
            state.displayOn = false;
        }
        else
        {
            Serial.println("POWER ON -> Wake Display");
            Display_Wakeup();
            state.displayOn = true;
        }
    }

    // ✅ Оновлення компонентів
    BME280_Update(state);
    RTC_Update(state);
    RGB_Runtime_Update(state);
    DisplayUI_Render(state);
    RGB_strip_Render(
        RGB_Runtime_GetStrip1(),
        RGB_Runtime_GetStrip2(),
        RGB_Runtime_GetBrightness()
    );
}