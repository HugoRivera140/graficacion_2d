#pragma once

#include <stdint.h>
#include "draw/figuras.h"

void clear_color_buffer();
void copy_buffer_to_texture(void);

void update(void);

void updateFiguras(void);
void _init(void);
void render_frame(void);
void render_input(void);

void render_GUI_frame(void);
void render_GUI_input(void);

vec2* pivote_mas_cerca(vec2 mp, Figuras *figs, float umbral);