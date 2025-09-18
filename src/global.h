#pragma once
#include <stdint.h>
#include <SDL3/SDL.h>
#include "color/colores.h"
#include "draw/figuras.h"
#include "GUI/boton.h"

typedef struct _estado
{
    SDL_Renderer *renderer;
    SDL_Texture *textura;
    SDL_Event evento;
    uint32_t *color_buffer;
    Color clear_color;
    int ven_width;
    int ven_height;
    int run;
    Figuras *figuras_buffer;
    Button *botones_buffer;
}EstadosRender;

extern EstadosRender estadosrender;
