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

static uint8_t resolveIntensity(const AnimationParams& sp)
{
    // обмеження безпеки
    uint8_t i = sp.intensity;
    if (i < 1) i = 1;
    if (i > 10) i = 10;

    // базова шкала сили ефекту
    // 1 → ~4
    // 10 → ~40
    return i * 4;
}

// Наскільки ЯСКРАВО
static uint8_t resolvePower(const AnimationParams& p)
{
    return resolveIntensity(p);
}

// Наскільки ДАЛЕКО (довжина хвоста)
static uint8_t resolveRange(const AnimationParams& p)
{
    // intensity 1–10 → range 1–4
    uint8_t i = p.intensity;
    if (i < 1) i = 1;
    if (i > 10) i = 10;

    return (i + 2) / 3; // 1..4
}

static AnimColors resolveWalkingPixelColors(
    const RGB& base,
    const AnimationParams& p
)
{
    AnimColors c;

    if (!p.invertEffect)
    {
        c.background = dim(base, 5);
        
        uint8_t power = resolvePower(p);

        c.tail = boost(base, power);
        c.head = boost(base, power * 2);
    }
    else
    {
        c.background = ensureMinBrightness(base, 8);
        c.tail       = dim(c.background, 2);
        c.head       = RGB{0, 0, 0};
    }

    return c;
}

static AnimationParams sanitizeParams(const AnimationParams& in)
{
    AnimationParams p = in;

    // intensity ніколи не 0
    if (p.intensity < 1)
        p.intensity = 1;

    // walking pixel: invertEffect без сенсу при intensity = 1
    if (p.type == ANIM_WALKING_PIXEL && p.invertEffect && p.intensity == 1)
    {
        // мінімальний хвіст, щоб ефект був видимий
        p.intensity = 2;
    }

    // glitch: syncStrips не має сенсу
    if (p.type == ANIM_GLITCH)
    {
        p.syncStrips = false;
    }

    return p;
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
    AnimationParams sp = sanitizeParams(p);
    switch (sp.type)
    {
        /* ===== ХОДЯЧИЙ ПІКСЕЛЬ ===== */
        // Опис: Один яскравий піксель "ходить" вздовж смуги,
        // інші пікселі приглушені
        case ANIM_WALKING_PIXEL:
        {
            uint8_t pos = s.index;

            // інверсія напрямку для другої стрічки
            if (sp.invertSecond && isSecondStrip)
            {
                pos = (NUMPIXELS - 1) - pos;
            }

            uint8_t dist = (i > pos) ? (i - pos) : (pos - i);

            AnimColors colors = resolveWalkingPixelColors(base, sp);

            RGB out = colors.background;

            uint8_t range = resolveRange(sp);

            if (dist == 0)
            {
                out = colors.head;
            }
            else if (dist <= range)
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
            if (sp.invertSecond && isSecondStrip)
                lit = !lit;

            // інтенсивність як яскравість
            RGB on = boost(base, resolveIntensity(sp));

            return lit ? on : RGB{0, 0, 0};
        }
        /* ===== ГЛІЧ ===== */
        // Опис: Випадкові пікселі спалахують яскравіше на короткий час,
        // імітуючи цифровий збій
        case ANIM_GLITCH:
        {
            // базовий колір завжди присутній
            RGB out = base;

            if (s.glitchActive &&
                i >= s.glitchPixel &&
                i < s.glitchPixel + s.glitchCount)
            {
                if (!sp.invertEffect)
                {
                    // підсвітити
                    out = boost(base, resolveIntensity(sp));
                }
                else
                {
                    // приглушити (інверсний гліч)
                    out = dim(base, 4);
                }
            }

            return out;
        }

        case ANIM_PULSE:
        {
            // базовий колір завжди присутній
            RGB out = base;

            // фаза → плавна хвиля 0..1
            float pulse = (sin(s.phase) + 1.0f) * 0.5f;

            uint8_t power = resolvePower(sp);

            // масштабуємо яскравість
            out.r = clampAdd(0, uint8_t(base.r * pulse));
            out.g = clampAdd(0, uint8_t(base.g * pulse));
            out.b = clampAdd(0, uint8_t(base.b * pulse));

            // додатковий контраст через power
            if (!sp.invertEffect)
            {
                out = boost(out, power / 2);
            }
            else
            {
                out = dim(out, 2);
            }

            return out;
        }

        case ANIM_WAVE:
        {
            uint8_t center = s.index;

            // дзеркалимо для другої стрічки
            if (sp.invertSecond && isSecondStrip)
            {
                center = (NUMPIXELS - 1) - center;
            }

            uint8_t dist = (i > center) ? (i - center) : (center - i);
            uint8_t range = resolveRange(sp);

            // за межами хвилі — просто база
            if (dist > range)
                return base;

            // dist 0..range → 1..0
            float norm = 1.0f - (float(dist) / float(range + 1));
            float wave = cos(norm * (PI / 2.0f)); // мʼякий спад

            uint8_t power = resolvePower(sp);

            RGB out;
            out.r = clampAdd(0, uint8_t(base.r * wave));
            out.g = clampAdd(0, uint8_t(base.g * wave));
            out.b = clampAdd(0, uint8_t(base.b * wave));

            // підсилюємо хвилю
            if (!sp.invertEffect)
            {
                out = boost(out, power);
            }
            else
            {
                out = dim(out, 2);
            }

            return out;
        }
        case ANIM_NOISE:
        {
            // базовий колір завжди є
            RGB out = base;

            uint8_t power = resolvePower(sp);

            // унікальна фаза для кожного пікселя
            float n =
                sin(s.phase * 1.7f + i * 1.31f) * 0.5f +
                sin(s.phase * 0.9f + i * 0.77f) * 0.5f;

            // нормалізація → 0..1
            float noise = (n + 1.0f) * 0.5f;

            // масштабуємо базу
            out.r = uint8_t(base.r * noise);
            out.g = uint8_t(base.g * noise);
            out.b = uint8_t(base.b * noise);

            if (!sp.invertEffect)
            {
                out = boost(out, power);
            }
            else
            {
                // “нічний” органічний режим
                out = dim(out, 2);
            }

            return out;
        }

        // Якщо тип анімації невідомий, повертаємо базовий колір без змін
        default:
            return base;
    }
}
