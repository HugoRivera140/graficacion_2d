#include "render.h"
#include "color/colores.h"
#include "draw/draw.h"
#include "global.h"
#include "draw/linea.h"
#include "draw/vectores.h"
#include "draw/lerp.h"
#include "draw/figuras.h"
#include "memoria/memoria.h"
#include "GUI/boton.h"  

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// ==================== Estado local ====================
vec2* punto_seleccionado = NULL;   // Vértice seleccionado para mover
Figuras* figura_activa = NULL;     // Figura seleccionada

// ==================== Utilidades ======================
vec2 *pivote_mas_cerca(vec2 mp, Figuras *figs, float umbral) {
    for(int i=0; i<array_size(figs); i++) {
        Figuras *f = &figs[i];
        switch(f->data.type) {
            case CUADRO:
                if(fabs(mp.unpack.x - f->cuadro.pos.unpack.x) <= umbral &&
                   fabs(mp.unpack.y - f->cuadro.pos.unpack.y) <= umbral)
                    return &f->cuadro.pos;
                break;
            case CIRC:
                if(fabs(mp.unpack.x - f->circulo.pos.unpack.x) <= umbral &&
                   fabs(mp.unpack.y - f->circulo.pos.unpack.y) <= umbral)
                    return &f->circulo.pos;
                break;
            case TRIAN:
                if(distanciav2(mp,f->triangulo.p1) <= umbral) return &f->triangulo.p1;
                if(distanciav2(mp,f->triangulo.p2) <= umbral) return &f->triangulo.p2;
                if(distanciav2(mp,f->triangulo.p3) <= umbral) return &f->triangulo.p3;
                break;
            default: break;
        }
    }
    return NULL;
}

Figuras* figura_mas_cerca(vec2 mp, Figuras *figs, float umbral) {
    for(int i=0; i<array_size(figs); i++) {
        Figuras *f = &figs[i];
        switch(f->data.type) {
            case CUADRO:
                if(mp.unpack.x >= f->cuadro.pos.unpack.x &&
                   mp.unpack.x <= f->cuadro.pos.unpack.x + f->cuadro.w &&
                   mp.unpack.y >= f->cuadro.pos.unpack.y &&
                   mp.unpack.y <= f->cuadro.pos.unpack.y + f->cuadro.h)
                    return f;
                break;
            case CIRC: {
                float dx = mp.unpack.x - f->circulo.pos.unpack.x;
                float dy = mp.unpack.y - f->circulo.pos.unpack.y;
                if(sqrtf(dx*dx + dy*dy) <= f->circulo.r) return f;
                break;
            }
            case TRIAN:
                if(distanciav2(mp,f->triangulo.p1) <= umbral ||
                   distanciav2(mp,f->triangulo.p2) <= umbral ||
                   distanciav2(mp,f->triangulo.p3) <= umbral)
                    return f;
                break;
            default: break;
        }
    }
    return NULL;
}

// ==================== Input ==========================
void render_input() {
    int mx, my;
    switch(estadosrender.evento.type) {
        case SDL_EVENT_QUIT:
            estadosrender.run = 0;
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            mx = estadosrender.evento.button.x;
            my = estadosrender.evento.button.y;

            // Primero, clic en botones
            for(int i=0; i<array_size(estadosrender.botones_buffer); i++)
                eventListener(&estadosrender.botones_buffer[i]);

            // Segundo, clic en figura
            figura_activa = figura_mas_cerca((vec2){{mx,my}}, estadosrender.figuras_buffer, 10.f);
            if(figura_activa)
                printf("Figura seleccionada tipo=%d\n", figura_activa->data.type);

            // Tercero, pivote cercano para mover
            if(!punto_seleccionado)
                punto_seleccionado = pivote_mas_cerca((vec2){{mx,my}}, estadosrender.figuras_buffer, 10.f);
            if(punto_seleccionado)
                printf("Punto mas cercano(%3.f,%3.f)\n", punto_seleccionado->unpack.x, punto_seleccionado->unpack.y);

            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            mx = estadosrender.evento.button.x;
            my = estadosrender.evento.button.y;
            if(punto_seleccionado) {
                punto_seleccionado->unpack.x = mx;
                punto_seleccionado->unpack.y = my;
                punto_seleccionado = NULL;
            }
            break;

        case SDL_EVENT_MOUSE_MOTION:
            mx = estadosrender.evento.motion.x;
            my = estadosrender.evento.motion.y;
            if(punto_seleccionado) {
                punto_seleccionado->unpack.x = mx;
                punto_seleccionado->unpack.y = my;
            }
            break;

        default: break;
    }
}

// ==================== Limpieza =======================
void clear_color_buffer() {
    for(int y=0; y<estadosrender.ven_height; y++)
        for(int x=0; x<estadosrender.ven_width; x++)
            draw_pixel(x, y, estadosrender.clear_color.hex);
}

void copy_buffer_to_texture(void) {
    SDL_UpdateTexture(estadosrender.textura, NULL, estadosrender.color_buffer,
                      (int)(estadosrender.ven_width*sizeof(int)));
    SDL_RenderTexture(estadosrender.renderer, estadosrender.textura, NULL, NULL);
}

// ==================== Inicialización =================
void _init(void) {
    int bttnHeight = 40;
    int bttnWidth = bttnHeight + (bttnHeight / 3);
    int xPosInit[] = {400, 500, 600};
    int yPosInit[] = {400, 400, 400};

    Cuadro bttn1_labelRaw = {.pos = {.unpack = {.x = xPosInit[0]+(bttnWidth/3.f),
                                                 .y = yPosInit[0]+(bttnHeight/5.f)}},
                             .w=(bttnHeight/5.f)*3,.h=(bttnHeight/5.f)*3,
                             .color=(Color){0xFFFFFFFF},.type=CUADRO};
    Circulo bttn2_labelRaw = {.pos = {.unpack = {.x = xPosInit[1]+bttnWidth/2.f,
                                                 .y = yPosInit[1]+bttnHeight/2.f}},
                              .r=(bttnHeight/10.f)*3,.color=(Color){0xFFFFFFFF},.type=CIRC};
    Triangulo bttn3_labelRaw = {.p1={{xPosInit[2]+(bttnWidth/3.f), yPosInit[2]+(bttnHeight/3.f)*2}},
                                .p2={{xPosInit[2]+(bttnWidth/2.f), yPosInit[2]+(bttnHeight/3.f)}},
                                .p3={{xPosInit[2]+(bttnWidth/3.f)*2, yPosInit[2]+(bttnHeight/3.f)*2}},
                                .color=(Color){0xFFFFFFFF},.type=TRIAN};

    Figuras labels[] = {
        {.cuadro=bttn1_labelRaw},
        {.circulo=bttn2_labelRaw},
        {.triangulo=bttn3_labelRaw}
    };

    for(int i=0;i<3;i++){
        Button b = {.x=xPosInit[i],.y=yPosInit[i],.width=bttnWidth,.height=bttnHeight,.label=labels[i]};
        pushto_array(estadosrender.botones_buffer, b);
    }
}

// ==================== Render loop ====================
void updateFiguras(void) {
    // Botones
    for(int i=0; i<array_size(estadosrender.botones_buffer); i++){
        draw_boton(&estadosrender.botones_buffer[i]);
    }
    // Figuras
    for(int i=0; i<array_size(estadosrender.figuras_buffer); i++){
        draw_figura(&estadosrender.figuras_buffer[i]);
    }
}

void render_frame(void) {
    SDL_RenderPresent(estadosrender.renderer);
}
