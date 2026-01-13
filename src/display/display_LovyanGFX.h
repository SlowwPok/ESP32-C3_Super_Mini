#pragma once
#include <stdint.h>

// ===== LIFECYCLE =====
void Display_Init();
void Display_Clear(uint32_t color);

// ===== GEOMETRY =====
int  Display_Width();
int  Display_Height();

// ===== PRIMITIVES =====
void Display_DrawLine(int x0, int y0, int x1, int y1, uint32_t color);
void Display_DrawRect(int x, int y, int w, int h, uint32_t color);
void Display_FillRect(int x, int y, int w, int h, uint32_t color);
void Display_DrawText(int x, int y, const char* text, uint32_t color);

// ===== DEBUG / TEST =====
void Display_DrawGrid();
