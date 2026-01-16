#include "controls.h"

#define BTN_POWER_PIN      4
#define LONG_PRESS_TIME    800
#define DEBOUNCE_DELAY     50

struct ButtonFSM
{
    uint8_t pin;
    bool lastReading;
    bool stableState;
    unsigned long lastDebounce;
    unsigned long pressStart;
    bool longDone;
};

static ButtonFSM btnPower;

void Controls_Init()
{
    btnPower = {
        .pin = BTN_POWER_PIN,
        .lastReading = false,
        .stableState = false,
        .lastDebounce = 0,
        .pressStart = 0,
        .longDone = false
    };

    pinMode(btnPower.pin, INPUT);
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
    bool reading = digitalRead(b.pin);
    unsigned long now = millis();

    ButtonEvent ev = { id, BTN_EVENT_NONE };

    if (reading != b.lastReading)
        b.lastDebounce = now;

    if ((now - b.lastDebounce) > DEBOUNCE_DELAY)
    {
        if (reading != b.stableState)
        {
            b.stableState = reading;

            if (b.stableState)
            {
                b.pressStart = now;
                b.longDone = false;
            }
            else if (!b.longDone)
            {
                ev.type = BTN_EVENT_TAP;
            }
        }
    }

    if (b.stableState && !b.longDone &&
        now - b.pressStart >= LONG_PRESS_TIME)
    {
        ev.type = BTN_EVENT_HOLD;
        b.longDone = true;
    }

    b.lastReading = reading;
    return ev;
}

ControlEvent Controls_Update()
{
    ButtonEvent bev = Button_Update(btnPower, BTN_ID_POWER);

    if (bev.type == BTN_EVENT_NONE)
        return CTRL_NONE;

    if (bev.id == BTN_ID_POWER)
    {
        if (bev.type == BTN_EVENT_TAP)
            return CTRL_BTN_POWER_TAP;

        if (bev.type == BTN_EVENT_HOLD)
            return CTRL_BTN_POWER_HOLD;
    }

    return CTRL_NONE;
}