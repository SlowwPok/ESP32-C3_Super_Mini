#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "rgb_strip/rgb_strip.h"
#include "rgb_strip/rgb_modes.h"
#include "rgb_strip/animation_engine.h"

/* =========================================================
   ВНУТРІШНІ ТИПИ ДАНИХ
   ========================================================= */

/**
 * Перелік подій дотиків для обробки користувацького вводу.
 * Використовується для визначення типу натискання кнопки.
 */
enum TouchEvent
{
    TOUCH_NONE,  // Немає події (кнопка не натиснута)
    TOUCH_TAP,   // Коротке натискання (тап)
    TOUCH_LONG   // Довге натискання (long press)
};

/* =========================================================
   ОБ'ЄКТИ СВІТЛОДІОДНИХ СМУГ
   ========================================================= */

// Перша світлодіодна смуга (лівий канал)
Adafruit_NeoPixel strip_1(NUMPIXELS, LED_1_PIN, NEO_GRB + NEO_KHZ800);

// Друга світлодіодна смуга (правий канал)
Adafruit_NeoPixel strip_2(NUMPIXELS, LED_2_PIN, NEO_GRB + NEO_KHZ800);

/* =========================================================
   ГЛОБАЛЬНИЙ СТАН ПРОГРАМИ
   ========================================================= */

// Чи увімкнені світлодіоди (true - увімкнені, false - вимкнені)
static bool ledsEnabled = false;

// Поточний вибраний режим освітлення (індекс з rgb_modes)
static uint8_t currentMode = 0;

// Стани анімацій для кожного режиму (масив для всіх можливих режимів)
// [mode][0 = strip1, 1 = strip2]
static AnimationState animStates[16][2];

/* =========================================================
   ВИБІР РЕЖИМУ ОСВІТЛЕННЯ
   ========================================================= */

/**
 * Знаходить наступний доступний для вибору режим, починаючи з заданого індексу.
 * Пропускає службові (не selectable) режими.
 *
 * @param from Початковий індекс для пошуку
 * @return uint8_t Індекс наступного доступного режиму
 */
static uint8_t findNextSelectable(uint8_t from)
{
    uint8_t count = RGB_modes_Count(); // Загальна кількість режимів
    uint8_t i = from;                   // Поточний індекс для перевірки

    // Циклічний пошук наступного доступного режиму
    do
    {
        i = (i + 1) % count; // Перехід до наступного індексу (з поверненням на початок)
    } while (!RGB_modes_Get(i).selectable); // Повторювати, поки не знайдемо selectable режим

    return i; // Повернення знайденого індексу
}

/* =========================================================
   ОБРОБКА ДОТИКІВ (ТОРКАНЬ ДО КНОПКИ)
   ========================================================= */

/**
 * Обробляє стан сенсорної кнопки та визначає тип події.
 * Відстежує час натискання для розрізнення короткого та довгого натискання.
 *
 * @return TouchEvent Тип події дотиків (TAP, LONG або NONE)
 */
static TouchEvent handleTouch()
{
    bool pressed = digitalRead(TOUCH_PIN); // Поточний стан кнопки (true - натиснута)

    // Статичні змінні для збереження стану між викликами функції
    static bool lastPressed = false;       // Стан кнопки на попередньому кроці
    static unsigned long pressStart = 0;   // Час початку натискання
    static bool longDone = false;          // Чи вже оброблено довге натискання

    TouchEvent ev = TOUCH_NONE;            // Тип події за замовчуванням
    unsigned long now = millis();          // Поточний час

    // Початок нового натискання
    if (pressed && !lastPressed)
    {
        pressStart = now;  // Запис часу початку
        longDone = false;  // Скидання прапорця довгого натискання
    }

    // Перевірка на довге натискання (якщо час перевищує поріг)
    if (pressed && !longDone && now - pressStart >= LONG_PRESS_TIME)
    {
        ev = TOUCH_LONG;   // Подія: довге натискання
        longDone = true;   // Позначити, що довге натискання оброблено
    }

    // Кінець короткого натискання (відпускання кнопки без довгого натискання)
    if (!pressed && lastPressed && !longDone)
    {
        ev = TOUCH_TAP;    // Подія: коротке натискання
    }

    lastPressed = pressed; // Оновлення стану для наступного виклику
    return ev;             // Повернення типу події
}

/* =========================================================
   РЕНДЕРИНГ (ВІДОБРАЖЕННЯ) РЕЖИМУ
   ========================================================= */

/**
 * Відображає поточний режим на світлодіодних смугах.
 * Обробляє різні типи режимів: суцільний колір, по пікселях, анімований.
 *
 * @param m Структура режиму для відображення
 */
static void renderMode(const RGBMode& m)
{
    // Встановлення яскравості для обох смуг
    strip_1.setBrightness(m.brightness);
    strip_2.setBrightness(m.brightness);

        if (m.type == MODE_ANIMATED)
        {
            if (m.animated.anim.syncStrips)
            {
                Animation_Update(animStates[currentMode][0], m.animated.anim);
            }
            else
            {
                Animation_Update(animStates[currentMode][0], m.animated.anim);
                Animation_Update(animStates[currentMode][1], m.animated.anim);
            }
        }

    // Прохід по всіх пікселях (від 0 до NUMPIXELS-1)
    for (int i = 0; i < NUMPIXELS; i++)
    {
        RGB c1 = { 0, 0, 0 }; // Колір для першої смуги (за замовчуванням чорний)
        RGB c2 = { 0, 0, 0 }; // Колір для другої смуги (за замовчуванням чорний)

        if (!ledsEnabled)
        {
            // Світлодіоди вимкнені - залишаємо чорний колір
        }
        else if (m.type == MODE_SOLID)
        {
            // Суцільний колір: той самий для всіх пікселів
            c1 = m.solid.strip1; // Колір першої смуги
            c2 = m.solid.strip2; // Колір другої смуги
        }
        else if (m.type == MODE_PER_PIXEL)
        {
            // Колір по пікселях: кожен піксель має свій колір
            c1 = m.perPixel.strip1[i]; // Колір i-го пікселя першої смуги
            c2 = m.perPixel.strip2[i]; // Колір i-го пікселя другої смуги
        }
        else if (m.type == MODE_ANIMATED)
        {
            // Анімований режим: використовує базовий режим + анімацію
            const RGBMode& base = RGB_modes_Get(m.animated.baseModeIndex); // Базовий режим

            if (base.type != MODE_PER_PIXEL)
            {
                //захист від помилки конфігурації
                c1 = {0, 0, 0};
                c2 = {0, 0, 0};
            }
            else
            {
                AnimationState& s1 = animStates[currentMode][0];
                AnimationState& s2 = m.animated.anim.syncStrips
                    ? animStates[currentMode][0]
                    : animStates[currentMode][1];

                // Отримання базових кольорів для поточного пікселя
                RGB base1 = base.perPixel.strip1[i];
                RGB base2 = base.perPixel.strip2[i];

                // Застосування анімації до базових кольорів
                c1 = Animation_Apply(s1, m.animated.anim, base1, i);
                c2 = Animation_Apply(s2, m.animated.anim, base2, i);
            }
        }

        // Встановлення кольорів на пікселях смуг
        strip_1.setPixelColor(i, strip_1.Color(c1.r, c1.g, c1.b));
        strip_2.setPixelColor(i, strip_2.Color(c2.r, c2.g, c2.b));
    }

    // Відображення змін на фізичних світлодіодних смугах
    strip_1.show();
    strip_2.show();
}

/* =========================================================
   ПУБЛІЧНИЙ API (ІНТЕРФЕЙС ДЛЯ ЗОВНІШНЬОГО ВИКОРИСТАННЯ)
   ========================================================= */

/**
 * Ініціалізує світлодіодні смуги та пов'язані компоненти.
 * Викликається один раз при запуску програми.
 */
void RGB_strip_Init()
{
    // Ініціалізація об'єктів NeoPixel
    strip_1.begin();
    strip_2.begin();

    // Налаштування піна сенсорної кнопки як вхід
    pinMode(TOUCH_PIN, INPUT);

    // Ініціалізація станів анімацій для всіх режимів
    for (uint8_t i = 0; i < RGB_modes_Count(); i++)
    {
        Animation_Init(animStates[i][0]);
        Animation_Init(animStates[i][1]);
    }

    // Початкове відображення поточного режиму
    renderMode(RGB_modes_Get(currentMode));
}

/**
 * Основний цикл оновлення стану смуг.
 * Обробляє введення користувача та оновлює відображення.
 * Викликається регулярно в loop().
 */
void RGB_strip_Update()
{
    TouchEvent ev = handleTouch(); // Отримання події від сенсорної кнопки

    // Обробка довгого натискання: перемикання увімкнення/вимкнення світлодіодів
    if (ev == TOUCH_LONG)
    {
        ledsEnabled = !ledsEnabled; // Інверсія стану
    }

    // Обробка короткого натискання: перемикання на наступний режим
    if (ev == TOUCH_TAP)
    {
        currentMode = findNextSelectable(currentMode); // Знаходження наступного режиму
    }

    // Відображення поточного режиму з урахуванням нових змін
    renderMode(RGB_modes_Get(currentMode));
}
