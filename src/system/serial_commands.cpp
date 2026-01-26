#include "serial_commands.h"
#include "system/time/rtc_service.h"
#include "system/system_state.h"

// Налаштування швидкості Serial
#define SERIAL_BAUD_RATE 115200

void SerialCommands_Init()
{
    Serial.begin(SERIAL_BAUD_RATE);
    
    // Чекаємо підключення Serial (для debug)
    delay(3000);
    
    Serial.println("");
    Serial.println("━━━━━━━━━━━━━━━━━━━━━━━━━━━");
    Serial.println("  ESP32-C3 Super Mini");
    Serial.println("  Serial Commands Ready");
    Serial.println("  Type 'HELP' for commands");
    Serial.println("━━━━━━━━━━━━━━━━━━━━━━━━━━━");
}

void SerialCommands_PrintHelp()
{
    Serial.println("");
    Serial.println("━━━━━━━━━━━━━━━━━━━━━━━━━━━");
    Serial.println("AVAILABLE COMMANDS:");
    Serial.println("━━━━━━━━━━━━━━━━━━━━━━━━━━━");
    Serial.println("TIME YYYY MM DD HH MM SS");
    Serial.println("  Set RTC time");
    Serial.println("  Example: TIME 2026 01 26 14 30 00");
    Serial.println("");
    Serial.println("STATUS");
    Serial.println("  Show system status");
    Serial.println("");
    Serial.println("HELP");
    Serial.println("  Show this help");
    Serial.println("━━━━━━━━━━━━━━━━━━━━━━━━━━━");
}

// Команда TIME
static void handleTimeCommand(const String& cmd)
{
    int yr, mo, dy, hr, mn, sc;
    int parsed = sscanf(cmd.c_str(), "TIME %d %d %d %d %d %d",
                       &yr, &mo, &dy, &hr, &mn, &sc);
    
    if (parsed != 6) {
        Serial.println("❌ Invalid format!");
        Serial.println("Format: TIME YYYY MM DD HH MM SS");
        Serial.println("Example: TIME 2026 01 26 13 20 00");
        return;
    }
    
    // ВАЛІДАЦІЯ (перевірка правильності даних)
    if (yr < 2020 || yr > 2100) {
        Serial.println("❌ Invalid year (2020-2100)");
        return;
    }
    if (mo < 1 || mo > 12) {
        Serial.println("❌ Invalid month (1-12)");
        return;
    }
    if (dy < 1 || dy > 31) {
        Serial.println("❌ Invalid day (1-31)");
        return;
    }
    if (hr < 0 || hr > 23) {
        Serial.println("❌ Invalid hour (0-23)");
        return;
    }
    if (mn < 0 || mn > 59) {
        Serial.println("❌ Invalid minute (0-59)");
        return;
    }
    if (sc < 0 || sc > 59) {
        Serial.println("❌ Invalid second (0-59)");
        return;
    }
    
    // Встановлюємо час
    RTC_SetTime(yr, mo, dy, hr, mn, sc);
    Serial.println("✓ Time set successfully");
}

// Команда STATUS
static void handleStatusCommand()
{
    const SystemState& state = System_Get();
    
    Serial.println("");
    Serial.println("━━━━━━━━━━━━━━━━━━━━━━━━━━━");
    Serial.println("SYSTEM STATUS:");
    Serial.println("━━━━━━━━━━━━━━━━━━━━━━━━━━━");
    
    Serial.printf("Power: %s\n", state.powerOn ? "ON" : "OFF");
    Serial.printf("Current Mode: %d\n", state.currentMode);
    Serial.printf("Time: %04d-%02d-%02d %02d:%02d:%02d\n",
                  state.time.year, state.time.month, state.time.day,
                  state.time.hour, state.time.minute, state.time.second);
    
    Serial.println("━━━━━━━━━━━━━━━━━━━━━━━━━━━");
}

void SerialCommands_Process()
{
    // Перевіряємо чи є дані в Serial буфері
    if (!Serial.available()) {
        return;  // Немає команд - виходимо
    }
    
    // Читаємо команду до символу нового рядка '\n'
    String cmd = Serial.readStringUntil('\n');
    
    // Видаляємо пробіли з початку і кінця
    cmd.trim();
    
    // Ігноруємо порожні команди
    if (cmd.length() == 0) {
        return;
    }
    
    // Виводимо що отримали (для debug)
    Serial.print("> ");
    Serial.println(cmd);
    
    // Обробляємо команди
    if (cmd.startsWith("TIME")) {
        handleTimeCommand(cmd);
    }
    else if (cmd == "STATUS") {
        handleStatusCommand();
    }
    else if (cmd == "HELP") {
        SerialCommands_PrintHelp();
    }
    else {
        Serial.println("❌ Unknown command. Type 'HELP'");
    }
}