#pragma once
#include <stdint.h>

// базове
void Display_Init();
void Display_Clear(uint32_t color);

// helpers для debug / UI
int  Display_Width();
int  Display_Height();
void Display_DrawLine(int x0, int y0, int x1, int y1, uint32_t color);
void Display_DrawRect(int x, int y, int w, int h, uint32_t color);
void Display_FillRect(int x, int y, int w, int h, uint32_t color);
void Display_DrawText(int x, int y, const char* text, uint32_t color);

void Display_DrawGrid();
