#pragma once 
#include <stdint.h>
#include "vectores.h"
#include "figuras.h"

void draw_pixel(int x, int y, uint32_t color);
void draw_linea(int x0, int y0, int x1, int y1, uint32_t color);
void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void draw_rectangle(int x0, int y0, int w, int h, uint32_t color);
void draw_circle(int numvert, int x0, int y0, int radio, uint32_t color);
void draw_circle_points(int r, int xc, int yc, uint32_t color);

void fillTriangle(Triangulo triangulo);
