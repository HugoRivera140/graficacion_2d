#pragma once
#include <stdint.h>

void fuerza_bruta(int x0, int y0, int x1, int y1, uint32_t color);
void DDA(int x0, int y0, int x1, int y1, uint32_t color);
void Bressenham(int x0, int y0, int x1, int y1, uint32_t color);

void draw_linea(int x0, int y0, int x1, int y1, uint32_t color);

