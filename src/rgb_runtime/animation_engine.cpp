#include "rgb_runtime/animation_engine.h"
#include "rgb_strip/rgb_types.h"
#include "rgb_strip/rgb_config.h"

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
 * Збільшення яскравості кольору з випадковим компонентом.
 * Додає до кожного каналу випадкове значення в діапазоні.
 *
 * @param c Вхідний колір RGB
 * @param strength Сила бусту (базова величина випадкового додавання)
 * @return RGB Бустований колір з забезпеченням від переповнення
 */
static RGB boost(const RGB& c, uint8_t strength)
{
    return RGB{
        clampAdd(c.r, random(strength, strength * 2)), // Додавання випадкового значення до червоного
        clampAdd(c.g, random(strength, strength * 2)), // Додавання випадкового значення до зеленого
        clampAdd(c.b, random(strength, strength * 2))  // Додавання випадкового значення до синього
    };
}

/**
 * Гарантування мінімальної яскравості для кольору.
 * Переконує, що жоден канал не темніший за вказане значення.
 * Корисно для забезпечення видимості в темних ефектах.
 *
 * @param c Вхідний колір RGB
 * @param min Мінімальне значення для кожного каналу
 * @return RGB Колір з гарантованою мінімальною яскравістю
 */
static RGB ensureMinBrightness(const RGB& c, uint8_t min)
{
    RGB out = c;

    if (out.r < min) out.r = min; // Встановлення мінімуму для червоного каналу
    if (out.g < min) out.g = min; // Встановлення мінімуму для зеленого каналу
    if (out.b < min) out.b = min; // Встановлення мінімуму для синього каналу

    return out;
}

/**
 * Структура для зберігання кольорів анімованого пікселя.
 * Містить три компоненти: фон, голова (яскравий піксель) та хвіст (згасання).
 */
struct AnimColors
{
    RGB background; // Колір фону (для пікселів без анімації)
    RGB head;       // Колір "голови" (основний яскравий піксель)
    RGB tail;       // Колір "хвоста" (згасання за яскравим пікселем)
};

/**
 * Визначення інтенсивності ефекту на основі параметрів.
 * Конвертує значення інтенсивності (1-10) у масштабоване значення (4-40).
 * Використовується для контролю яскравості ефектів.
 *
 * @param sp Параметри анімації, що містять поле intensity
 * @return uint8_t Масштабована інтенсивність (1 → ~4, 10 → ~40)
 */
static uint8_t resolveIntensity(const AnimationParams& sp)
{
    // Обмеження безпеки: забезпечення коректного діапазону
    uint8_t i = sp.intensity;
    if (i < 1) i = 1;   // Мінімум: 1
    if (i > 10) i = 10; // Максимум: 10

    // Базова шкала сили ефекту
    // intensity = 1 → результат = 4
    // intensity = 10 → результат = 40
    return i * 4;
}

/**
 * Визначення потужності (яскравості) ефекту.
 * Простий обгортач над resolveIntensity для читабельності коду.
 *
 * @param p Параметри анімації
 * @return uint8_t Потужність ефекту (наскільки яскраво)
 */
static uint8_t resolvePower(const AnimationParams& p)
{
    return resolveIntensity(p); // Обчислення яскравості на основі інтенсивності
}

/**
 * Визначення діапазону (дальність) ефекту.
 * Конвертує інтенсивність у довжину "хвоста" анімації (1-4 пікселі).
 * Використовується для контролю того, наскільки далеко простягається ефект.
 *
 * @param p Параметри анімації
 * @return uint8_t Діапазон ефекту в пікселях (1-4)
 */
static uint8_t resolveRange(const AnimationParams& p)
{
    // Конвертація інтенсивності (1-10) в діапазон (1-4)
    uint8_t i = p.intensity;
    if (i < 1) i = 1;   // Мінімум: 1
    if (i > 10) i = 10; // Максимум: 10

    return (i + 2) / 3; // 1..4 (формула для плавного розподілу)
}

/**
 * Визначення кольорів для анімації "ходячого пікселя".
 * Розраховує фон, голову та хвіст на основі базового кольору та параметрів.
 * Підтримує нормальний та інвертований режими.
 *
 * @param base Базовий колір градієнта
 * @param p Параметри анімації (містять intensity та invertEffect)
 * @return AnimColors Структура з кольорами для різних частин ефекту
 */
static AnimColors resolveWalkingPixelColors(
    const RGB& base,
    const AnimationParams& p
)
{
    AnimColors c;

    if (!p.invertEffect)
    {
        // Нормальний режим: яскравий піксель на темному фоні
        c.background = dim(base, 5);        // Сильно приглушений фон
        
        uint8_t power = resolvePower(p);

        c.tail = boost(base, power);        // Хвіст: помірно бустований колір
        c.head = boost(base, power * 2);    // Голова: сильно бустований колір
    }
    else
    {
        // Інвертований режим: темний піксель на світлому фоні
        c.background = ensureMinBrightness(base, 8);  // Світлий фон
        c.tail       = dim(c.background, 2);          // Хвіст: приглушення фону
        c.head       = RGB{0, 0, 0};                  // Голова: чорний (контраст)
    }

    return c;
}

/**
 * Санітизація параметрів анімації перед використанням.
 * Переконує, що всі параметри мають розумні значення,
 * та коригує конфліктні комбінації параметрів.
 *
 * @param in Оригінальні параметри анімації
 * @return AnimationParams Сантивизовані параметри, готові до використання
 */
static AnimationParams sanitizeParams(const AnimationParams& in)
{
    AnimationParams p = in;

    // Обмеження безпеки: intensity ніколи не повинна бути 0
    if (p.intensity < 1)
        p.intensity = 1;

    // Ходячий піксель: invertEffect без сенсу при intensity = 1
    // Коригуємо для видимого ефекту
    if (p.type == ANIM_WALKING_PIXEL && p.invertEffect && p.intensity == 1)
    {
        // Збільшуємо інтенсивність для мінімального видимого хвоста
        p.intensity = 2;
    }

    // Гліч: syncStrips не має сенсу (завжди окремі стани для кожної смуги)
    if (p.type == ANIM_GLITCH)
    {
        p.syncStrips = false; // Примусово розсинхронізуємо смуги
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
    s.position  = 0;           // Початковий індекс пікселя
    s.phase = 0.0f;        // Початкова фаза (для плавних переходів)

    unsigned long now = millis();
    s.lastFrameTime = now;
    s.lastStepTime  = now;

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

void Animation_Update(AnimationState& s, const AnimationParams& p)
{
    unsigned long now = millis();

    // ---------- FRAME TIME ----------
    float dt = (now - s.lastFrameTime) * 0.001f;
    s.lastFrameTime = now;

    // position ЗАВЖДИ рухається
    float speedPxPerSec = 1.0f + p.intensity * 0.5f;
    s.position += speedPxPerSec * dt;

    while (s.position >= RGB_STRIP_LENGTH)
        s.position -= RGB_STRIP_LENGTH;

    // фаза теж завжди
    s.phase += dt * 2.0f;

    // ---------- STEP TIME (логіка) ----------
    if (now - s.lastStepTime < p.speedMs)
        return;

    if (p.type == ANIM_EVEN_ODD)
        s.evenPhase = !s.evenPhase;

    if (p.type == ANIM_GLITCH)
    {
        if (s.glitchActive && now > s.glitchUntil)
            s.glitchActive = false;

        if (!s.glitchActive && random(100) < 15)
        {
            s.glitchActive = true;
            s.glitchPixel = random(RGB_STRIP_LENGTH);
            s.glitchCount = random(1, 2);
            s.glitchUntil = now + random(50, 100);
        }
    }

    s.lastStepTime = now;
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
            float posf = s.position;
            int pos0 = int(posf);
            int pos1 = (pos0 + 1) % RGB_STRIP_LENGTH;
            float t = posf - pos0; // 0..1

            // інверсія напрямку для другої стрічки
            if (sp.invertSecond && isSecondStrip)
            {
                pos0 = (RGB_STRIP_LENGTH - 1) - pos0;
                pos1 = (RGB_STRIP_LENGTH - 1) - pos1;
            }

            int d0 = abs(i - pos0);
            int d1 = abs(i - pos1);

            int dist0 = d0;
            int dist1 = d1;

            AnimColors colors = resolveWalkingPixelColors(base, sp);
            uint8_t range = resolveRange(sp);

            RGB out = colors.background;

            // ---- ГОЛОВА (плавна) ----
            if (dist0 == 0)
            {
                // pos0 → (1 - t)
                out.r = clampAdd(out.r, uint8_t(colors.head.r * (1.0f - t)));
                out.g = clampAdd(out.g, uint8_t(colors.head.g * (1.0f - t)));
                out.b = clampAdd(out.b, uint8_t(colors.head.b * (1.0f - t)));
            }
            else if (dist1 == 0)
            {
                out.r = clampAdd(out.r, uint8_t(colors.head.r * t));
                out.g = clampAdd(out.g, uint8_t(colors.head.g * t));
                out.b = clampAdd(out.b, uint8_t(colors.head.b * t));
            }
            // ---- ХВІСТ ----
            else if (dist0 <= range)
            {
                float k = 1.0f - (float(dist0) / float(range + 1));
                out.r = clampAdd(out.r, uint8_t(colors.tail.r * k));
                out.g = clampAdd(out.g, uint8_t(colors.tail.g * k));
                out.b = clampAdd(out.b, uint8_t(colors.tail.b * k));
            }

            return out;
        }
        /* ===== ПАРНІ/НЕПАРНІ ===== */
        // Опис: Парні пікселі світяться базовим кольором та перемикаються через час
        // Непарні - вимкнені (чорні), або навпаки залежно від фази
        case ANIM_EVEN_ODD:
        {
            bool isEvenPixel = (i % 2 == 0);
            
            // Визначення, чи світить піксель залежно від поточної фази
            bool lit = s.evenPhase ? isEvenPixel : !isEvenPixel;

            // Інверсія режиму для другої стрічки (чередування парних/непарних)
            if (sp.invertSecond && isSecondStrip)
                lit = !lit;

            // Світлі пікселі мають інтенсивність, темні - чорні
            RGB on = boost(base, resolveIntensity(sp));

            return lit ? on : RGB{0, 0, 0}; // Світло або чорний
        }
        /* ===== ГЛІЧ ===== */
        // Опис: Випадкові пікселі спалахують яскравіше на короткий час
        // Імітує цифровий збій з контрастними спалахами
        case ANIM_GLITCH:
        {
            RGB out = base;

            if (s.glitchActive &&
                i >= s.glitchPixel &&
                i < s.glitchPixel + s.glitchCount)
            {
                if (!sp.invertEffect)
                {
                    // контрастний кольоровий глітч
                    uint8_t ch = random(3);
                    out = base;

                    if (ch == 0) { out.r = 255; out.g /= 4; out.b /= 4; }
                    else if (ch == 1) { out.g = 255; out.r /= 4; out.b /= 4; }
                    else { out.b = 255; out.r /= 4; out.g /= 4; }
                }
                else
                {
                    // інверсний глітч
                    out.r = 255 - base.r;
                    out.g = 255 - base.g;
                    out.b = 255 - base.b;
                }
            }

            return out;
        }

        /* ===== ПУЛЬС ===== */
        // Опис: Плавне збільшення та зменшення яскравості
        // Створює ритмічний пульсуючий ефект
        case ANIM_PULSE:
        {
            float pulse = 0.5f - 0.5f * cos(s.phase);

            RGB out;
            out.r = uint8_t(base.r * pulse);
            out.g = uint8_t(base.g * pulse);
            out.b = uint8_t(base.b * pulse);

            return out;
        }

        /* ===== ХВИЛЯ ===== */
        // Опис: Косинусоїдна хвиля, що рухається по смузі
        // Створює ефект хвилі, що розповсюджується
        case ANIM_WAVE:
        {
            uint8_t center = s.position; // Центр хвилі

            // Дзеркалення центру для другої стрічки (асиметрія)
            if (sp.invertSecond && isSecondStrip)
            {
                center = (RGB_STRIP_LENGTH - 1) - center;
            }

            // Обчислення відстані від центру хвилі
            uint8_t dist = (i > center) ? (i - center) : (center - i);
            uint8_t range = resolveRange(sp);

            // За межами хвилі повертаємо базовий колір
            if (dist > range)
                return base;

            // Нормалізація: dist 0..range → 1..0 (від максимуму до мінімуму)
            float norm = 1.0f - (float(dist) / float(range + 1));
            float wave = cos(norm * (PI / 2.0f)); // М'яка косинусна крива

            uint8_t power = resolvePower(sp);

            // Масштабування кольору за хвилею
            RGB out;
            out.r = clampAdd(0, uint8_t(base.r * wave));
            out.g = clampAdd(0, uint8_t(base.g * wave));
            out.b = clampAdd(0, uint8_t(base.b * wave));

            // Підсилення хвилі інтенсивністю
            if (!sp.invertEffect)
            {
                out = boost(out, power); // Посилення хвилі
            }
            else
            {
                out = dim(out, 2);       // Пом'якшення хвилі
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
                out.r = clampAdd(0, uint8_t(out.r + power * noise));
                out.g = clampAdd(0, uint8_t(out.g + power * noise));
                out.b = clampAdd(0, uint8_t(out.b + power * noise));
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
