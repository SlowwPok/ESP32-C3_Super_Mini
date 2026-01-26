#include "controls.h"
#include "system/system_pin_setup.h"

#define BTN_POWER_PIN      PIN_BTN_POWER_UI
//#define BTN_UI_PIN         PIN_BTN_UI    // ❗ недійсний пін (поки немає кнопки UI)

#define LONG_PRESS_TIME    800
#define DEBOUNCE_DELAY     50

struct ButtonFSM
{
    uint8_t pin;
    bool lastReading;
    bool stable;
    uint32_t lastDebounce;
    uint32_t pressStart;
    bool holdFired;
};

static ButtonFSM btnPower;
static ButtonFSM btnUI;

void Controls_Init()
{
    delay(50);

    btnPower.pin = BTN_POWER_PIN;
    btnPower.lastReading = false;
    btnPower.stable = false;
    btnPower.lastDebounce = 0;
    btnPower.pressStart = 0;
    btnPower.holdFired = false;

    pinMode(btnPower.pin, INPUT_PULLUP);

    // ---- UI BUTTON (ЗАГЛУШКА) ----
    btnUI.pin = 0xFF;
    btnUI.lastReading = false;
    btnUI.stable = false;
    btnUI.lastDebounce = 0;
    btnUI.pressStart = 0;
    btnUI.holdFired = false;
}

enum ButtonId
{
    BTN_ID_POWER,
    BTN_ID_UI,   // на майбутнє
};

enum ButtonEventType
{
    BTN_EVENT_NONE,
    BTN_EVENT_TAP,
    BTN_EVENT_HOLD
};

struct ButtonEvent
{
    ButtonId id;
    ButtonEventType type;
};

static ButtonEvent Button_Update(ButtonFSM& b, ButtonId id)
{
    if (b.pin == 0xFF)
        return { id, BTN_EVENT_NONE };

    bool reading = !digitalRead(b.pin);
    uint32_t now = millis();
    ButtonEvent ev = { id, BTN_EVENT_NONE };

    if (reading != b.lastReading)
        b.lastDebounce = now;

    if ((now - b.lastDebounce) > DEBOUNCE_DELAY)
    {
        if (reading != b.stable)
        {
            b.stable = reading;

            if (b.stable)
            {
                b.pressStart = now;
                b.holdFired = false;
            }
            else
            {
                if (!b.holdFired)
                    ev.type = BTN_EVENT_TAP;
            }
        }
    }

    if (b.stable && !b.holdFired &&
        now - b.pressStart >= LONG_PRESS_TIME)
    {
        ev.type = BTN_EVENT_HOLD;
        b.holdFired = true;
    }

    b.lastReading = reading;
    return ev;
}

ControlEvent Controls_Update()
{
    static uint32_t startMs = 0;
    static bool ready = false;

    if (!ready)
    {
        if (startMs == 0)
            startMs = millis();

        if (millis() - startMs < 1500)
            return CTRL_NONE;

        ready = true;
    }

    // 1️⃣ POWER button
    ButtonEvent ev = Button_Update(btnPower, BTN_ID_POWER);
    if (ev.type != BTN_EVENT_NONE)
    {
        if (ev.type == BTN_EVENT_TAP)
            return CTRL_BTN_POWER_TAP;
        if (ev.type == BTN_EVENT_HOLD)
            return CTRL_BTN_POWER_HOLD;
    }

    // 2️⃣ UI button (поки завжди NONE)
    ev = Button_Update(btnUI, BTN_ID_UI);
    if (ev.type != BTN_EVENT_NONE)
    {
        if (ev.type == BTN_EVENT_TAP)
            return CTRL_BTN_UI_TAP;
        if (ev.type == BTN_EVENT_HOLD)
            return CTRL_BTN_UI_HOLD;
    }

    return CTRL_NONE;
}