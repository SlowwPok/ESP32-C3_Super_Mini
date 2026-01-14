#include "rgb_strip/animation_engine.h"

/* =========================================================
   ВНУТРІШНІ ДОПОМІЖНІ ФУНКЦІЇ
   ========================================================= */

/**
 * Безпечне додавання яскравості без переповнення.
 * Запобігає виходу значення за межі 0-255.
 *
 * @param base Базове значення яскравості
 * @param add Значення для додавання
 * @return uint8_t Результат додавання, обмежений до 255
 */
static uint8_t clampAdd(uint8_t base, uint8_t add)
{
    uint16_t v = base + add;
    return (v > 255) ? 255 : v;
}

/**
 * Приглушення кольору шляхом ділення на дільник.
 * Зменшує яскравість кольору для створення ефекту тіні або фону.
 *
 * @param c Вхідний колір RGB
 * @param div Дільник яскравості (чим більше, тим темніше)
 * @return RGB Приглушений колір
 */
static RGB dim(const RGB& c, uint8_t div)
{
    return RGB{ uint8_t(c.r / div), uint8_t(c.g / div), uint8_t(c.b / div) };
}

/**
 * Зробити колір контрастніше бустанути.
 * Збільшує яскравість кольору для створення ефекту контрасту.
 *
 * @param c Вхідний колір RGB
 * @param strength Множник яскравості (чим більше, тим яскравіше)
 * @return RGB Яскравіший колір
 */
static RGB boost(const RGB& c, uint8_t strength)
{
  return RGB{
    clampAdd(c.r, random(strength, strength * 2)),
    clampAdd(c.g, random(strength, strength * 2)),
    clampAdd(c.b, random(strength, strength * 2))
  };
}

static RGB ensureMinBrightness(const RGB& c, uint8_t min)
{
    RGB out = c;

    if (out.r < min) out.r = min;
    if (out.g < min) out.g = min;
    if (out.b < min) out.b = min;

    return out;
}

struct AnimColors
{
    RGB background;
    RGB head;
    RGB tail;
};

static AnimColors resolveWalkingPixelColors(
    const RGB& base,
    const AnimationParams& p
)
{
    AnimColors c;

    if (!p.invertEffect)
    {
        c.background = dim(base, 5);
        c.tail       = boost(base, p.intensity * 6);
        c.head       = boost(base, p.intensity * 12);
    }
    else
    {
        c.background = ensureMinBrightness(base, 8);
        c.tail       = dim(c.background, 4);
        c.head       = RGB{0, 0, 0};
    }

    return c;
}

/* =========================================================
   ІНІЦІАЛІЗАЦІЯ АНІМАЦІЙ
   ========================================================= */

/**
 * Ініціалізує стан анімації початковими значеннями.
 * Скидає всі лічильники та прапорці для початку нової анімації.
 *
 * @param s Посилання на стан анімації для ініціалізації
 */
void Animation_Init(AnimationState& s)
{
    s.index = 0;           // Початковий індекс пікселя
    s.phase = 0.0f;        // Початкова фаза (для плавних переходів)
    s.lastStep = 0;        // Час останнього кроку анімації
    s.evenPhase = true;    // Початкова фаза для парних/непарних анімацій

    // Параметри гліч-ефекту
    s.glitchActive = false; // Гліч не активний на старті
    s.glitchPixel = 0;      // Початковий піксель для глічу
    s.glitchCount = 0;      // Кількість пікселів у глічі
    s.glitchUntil = 0;      // Час завершення глічу
}

/* =========================================================
   ОНОВЛЕННЯ СТАНУ АНІМАЦІЇ
   ========================================================= */

/**
 * Оновлює стан анімації на основі поточного часу та параметрів.
 * Обробляє рух пікселів та логіку гліч-ефекту.
 *
 * @param s Посилання на стан анімації для оновлення
 * @param p Параметри анімації (тип, швидкість тощо)
 */
void Animation_Update(AnimationState& s, const AnimationParams& p)
{
    unsigned long now = millis(); // Поточний час у мілісекундах

    // Перевірка, чи минув достатньо часу для наступного кроку
    if (now - s.lastStep < p.speedMs)
        return;

    s.lastStep = now; // Оновлення часу останнього кроку

    // Стандартний рух: зміна індексу пікселя та фази
    s.index = (s.index + 1) % NUMPIXELS; // Циклічний рух по пікселях
    s.phase += 0.1f;                     // Плавне збільшення фази

    /* ---------- ЛОГІКА ПАРНИХ/НЕПАРНИХ ---------- */
    if (p.type == ANIM_EVEN_ODD)
    {
        s.evenPhase = !s.evenPhase; // <-- головне
        return;
    }

    /* ---------- ЛОГІКА ГЛІЧ-ЕФЕКТУ ---------- */
    if (p.type == ANIM_GLITCH)
    {
        // Завершення активного глічу, якщо час минув
        if (s.glitchActive && now > s.glitchUntil)
        {
            s.glitchActive = false;
        }

        // Випадковий старт нового глічу (~12% шанс на кожному кроці)
        if (!s.glitchActive && random(100) < 15)
        {
            s.glitchActive = true;
            s.glitchPixel = random(NUMPIXELS);         // Випадковий піксель для початку глічу
            s.glitchCount = random(1, 2);              // 1-3 пікселі будуть у глічі
            s.glitchUntil = now + random(50, 100);     // Тривалість глічу: 40-120 мс
        }
    }
}

/* =========================================================
   ЗАСТОСУВАННЯ АНІМАЦІЇ ДО КОЛЬОРУ
   ========================================================= */

/**
 * Застосовує ефект анімації до базового кольору для конкретного пікселя.
 * Залежно від типу анімації змінює колір або повертає базовий.
 *
 * @param s Стан анімації
 * @param p Параметри анімації
 * @param base Базовий колір пікселя
 * @param i Індекс пікселя (0 до NUMPIXELS-1)
 * @return RGB Результуючий колір після застосування анімації
 */
RGB Animation_Apply(const AnimationState& s, const AnimationParams& p, const RGB& base, uint8_t i, bool isSecondStrip)
{
    switch (p.type)
    {
        /* ===== ХОДЯЧИЙ ПІКСЕЛЬ ===== */
        // Опис: Один яскравий піксель "ходить" вздовж смуги,
        // інші пікселі приглушені
        case ANIM_WALKING_PIXEL:
        {
            uint8_t pos = s.index;

            // інверсія напрямку для другої стрічки
            if (p.invertSecond && isSecondStrip)
            {
                pos = (NUMPIXELS - 1) - pos;
            }

            uint8_t dist = (i > pos) ? (i - pos) : (pos - i);

            AnimColors colors = resolveWalkingPixelColors(base, p);

            RGB out = colors.background;

            if (dist == 0)
            {
                out = colors.head;
            }
            else if (dist <= p.intensity)
            {
                out = colors.tail;
            }

            return out;
        }
        /* ===== ПАРНІ/НЕПАРНІ ===== */
        // Опис: Парні пікселі світяться базовим кольором,
        // Та перемикаються через заданий час
        // непарні - вимкнені (чорні)
        case ANIM_EVEN_ODD:
        {
            bool isEvenPixel = (i % 2 == 0);
            bool lit = s.evenPhase ? isEvenPixel : !isEvenPixel;

            // інверсія другої стрічки
            if (p.invertSecond && isSecondStrip)
                lit = !lit;

            // інтенсивність як яскравість
            RGB on = boost(base, p.intensity * 10);

            return lit ? on : RGB{0, 0, 0};
        }
        /* ===== ГЛІЧ ===== */
        // Опис: Випадкові пікселі спалахують яскравіше на короткий час,
        // імітуючи цифровий збій
        case ANIM_GLITCH:
        {
            // Якщо гліч активний і поточний піксель у зоні глічу
            if (s.glitchActive && i >= s.glitchPixel && i < s.glitchPixel + s.glitchCount)
            {
                // КОНТРАСТНИЙ КОЛЬОРОВИЙ СПАЛАХ
                return boost(base, p.intensity * 1);
            }

            // чоний фон
            return RGB{0, 0, 0};
        }

        // Якщо тип анімації невідомий, повертаємо базовий колір без змін
        default:
            return base;
    }
}
