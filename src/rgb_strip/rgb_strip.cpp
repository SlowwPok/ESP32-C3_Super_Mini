#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "system/system_state.h"
#include "rgb_strip/rgb_strip.h"
#include "rgb_strip/rgb_modes.h"
#include "rgb_strip/animation_engine.h"


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

// Стани анімацій для кожного режиму
// [режим][смуга] - кожен режим має 2 стани для синхронізованих та окремих смуг
// animStates[currentMode][0] - стан для першої смуги або синхронізований стан
// animStates[currentMode][1] - стан для другої смуги (при несинхронізованих смугах)
static AnimationState animStates[RGB_MODES_MAX][2];

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
    const SystemState& sys = System_Get();

    // Встановлення яскравості для обох смуг
    strip_1.setBrightness(m.brightness);
    strip_2.setBrightness(m.brightness);

        if (m.type == MODE_ANIMATED)
        {
            // Оновлення стану анімації залежно від налаштувань синхронізації
            if (m.animated.anim.syncStrips)
            {
                // Синхронізовані смуги: використовуємо один стан для обох
                Animation_Update(animStates[sys.currentMode][0], m.animated.anim);
            }
            else
            {
                // Окремі смуги: оновлюємо стан для кожної смуги окремо
                Animation_Update(animStates[sys.currentMode][0], m.animated.anim);
                Animation_Update(animStates[sys.currentMode][1], m.animated.anim);
            }
        }

    // Прохід по всіх пікселях (від 0 до NUMPIXELS-1)
    for (int i = 0; i < NUMPIXELS; i++)
    {
        RGB c1 = { 0, 0, 0 }; // Колір для першої смуги (за замовчуванням чорний)
        RGB c2 = { 0, 0, 0 }; // Колір для другої смуги (за замовчуванням чорний)

        if (!sys.powerOn)
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

            // Захист від помилки конфігурації: базовий режим повинен бути MODE_PER_PIXEL
            if (base.type != MODE_PER_PIXEL)
            {
                // Якщо базовий режим не MODE_PER_PIXEL, показуємо чорний колір (сигнал помилки)
                c1 = {0, 0, 0};
                c2 = {0, 0, 0};
            }
            else
            {
                // Отримання станів анімацій для обох смуг
                AnimationState& s1 = animStates[sys.currentMode][0];
                AnimationState& s2 = m.animated.anim.syncStrips
                    ? animStates[sys.currentMode][0] // Синхронізовані: використовуємо один стан
                    : animStates[sys.currentMode][1]; // Окремі: кожна смуга має свій стан

                // Отримання базових кольорів для поточного пікселя
                RGB base1 = base.perPixel.strip1[i];
                RGB base2 = base.perPixel.strip2[i];

                // Застосування анімації до базових кольорів
                // Параметр isSecondStrip дозволяє анімації змінювати ефект для другої смуги
                c1 = Animation_Apply(s1, m.animated.anim, base1, i, false);
                c2 = Animation_Apply(s2, m.animated.anim, base2, i, true);
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
    const SystemState& sys = System_Get();

    // Ініціалізація об'єктів NeoPixel
    strip_1.begin();
    strip_2.begin();

    // Ініціалізація станів анімацій для всіх режимів
    for (uint8_t i = 0; i < RGB_modes_Count(); i++)
    {
        Animation_Init(animStates[i][0]);
        Animation_Init(animStates[i][1]);
    }

    // Початкове відображення поточного режиму
    renderMode(RGB_modes_Get(sys.currentMode));
}

/**
 * Основний цикл оновлення стану смуг.
 * Обробляє введення користувача та оновлює відображення.
 * Викликається регулярно в loop().
 */
void RGB_strip_Update()
{
    const SystemState& sys = System_Get();

    if (!sys.powerOn)
    {
        strip_1.clear();
        strip_2.clear();
        strip_1.show();
        strip_2.show();
        return;
    }
    // Відображення поточного режиму з урахуванням нових змін
    renderMode(RGB_modes_Get(sys.currentMode));
}
