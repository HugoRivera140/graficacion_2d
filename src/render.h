#pragma once

#include <stdint.h>
#include "draw/figuras.h"

void clear_color_buffer();
void copy_buffer_to_texture(void);

void update(void);

void updateLinea(void);
void updateDDA(void);
void updateBressenham(void);

void updateTriangle(void);
void updateRectangle(void);
void updateCircle(void);
void updateCirclePoints(void);

void pattern1(int, int);
void pattern2(int);
void pattern3(int, int);

void updateCurva(void);
void updateFiguras(void);
void _init(void);

void render_frame(void);
void render_input(void);

vec2* pivote_mas_cerca(vec2 mp, Figuras *figs, float umbral);