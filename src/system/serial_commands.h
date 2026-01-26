#pragma once
#include <Arduino.h>

/**
 * Модуль для обробки Serial команд
 * 
 * НАВІЩО: Відділити логіку команд від main.cpp
 * ЯК ПРАЦЮЄ: Перевіряє Serial буфер і виконує команди
 */

// Ініціалізація Serial (викликати в setup())
void SerialCommands_Init();

// Обробка команд (викликати в loop())
void SerialCommands_Process();

// Вивести список доступних команд
void SerialCommands_PrintHelp();