#pragma once
#include <stdint.h>

void fuerza_bruta(int x0, int y0, int x1, int y1, uint32_t color);
void DDA(int x0, int y0, int x1, int y1, uint32_t color);
void Bressenham(int x0, int y0, int x1, int y1, uint32_t color);

void draw_linea(int x0, int y0, int x1, int y1, uint32_t color);

float fpart(float x);
float rfpart(float x);
void l_swap(int *a, int *b);
uint32_t cambiar_brillo(uint32_t *color, float brillo);
void Xiaolinline(int x0, int y0, int x1, int y1, uint32_t color);