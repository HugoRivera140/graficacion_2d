#include "boton.h"
#include "../global.h"
#include "../draw/draw.h"
#include "../draw/figuras.h"
#include "../memoria/memoria.h"

#include <stdlib.h>
#include <stdio.h>

void draw_boton(Button *button){
    draw_rectangle(button -> x, button -> y,
                  button -> width, button -> height,
                  0xFFFFFFFF);

    draw_figura(&(button -> label));
}

void eventListener(Button *button){    
    if(estadosrender.evento.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        int mx = estadosrender.evento.button.x;
        int my = estadosrender.evento.button.y;

        if(mx >= button->x &&
           mx <= (button->x + button->width) &&
           my >= button->y &&
           my <= (button->y + button->height)) {

            switch(button->label.data.type){
                case CUADRO:
                {
                    printf("Boton1 encontrado...\n");
                    Figuras *prueba = createCuad();
                    pushto_array(estadosrender.figuras_buffer, *prueba);
                    break;
                }
                case CIRC:
                {
                    printf("Boton2 encontrado...\n");
                    Figuras *c = createCirc();
                    pushto_array(estadosrender.figuras_buffer, *c);
                    break;
                }
                case TRIAN:
                {
                    printf("Boton3 encontrado...\n");
                    Figuras *t = createTrian();
                    pushto_array(estadosrender.figuras_buffer, *t);
                    break;
                }
                default:
                    break;
            }
        }
    }
}


float desplazamientoX_total = 0.f; // desplazamiento horizontal acumulado
const float stepX = 120.f;         // separación horizontal entre figuras
const float initOffsetX = -300.f;  // empieza un poco a la izquierda del centro
const float initOffsetY = -100.f;   // altura fija, un poco arriba del centro



Figuras* createCuad(void){
    Figuras* f = malloc(sizeof(Figuras));
    f->cuadro.pos.unpack.x = estadosrender.ven_width / 2.f + initOffsetX + desplazamientoX_total;
    f->cuadro.pos.unpack.y = estadosrender.ven_height / 2.f + initOffsetY;
    f->cuadro.w = 100;
    f->cuadro.h = 100;
    f->cuadro.color.hex = 0xFF00FFFF;
    f->data.type = CUADRO;

    desplazamientoX_total += stepX; // siguiente figura a la derecha
    return f;
}

Figuras* createCirc(void){
    Figuras* f = malloc(sizeof(Figuras));
    f->circulo.pos.unpack.x = estadosrender.ven_width / 2.f + initOffsetX + desplazamientoX_total;
    f->circulo.pos.unpack.y = estadosrender.ven_height / 2.f + initOffsetY;
    f->circulo.r = 50;
    f->circulo.color.hex = 0xFFFF00FF;
    f->data.type = CIRC;

    desplazamientoX_total += stepX;
    return f;
}

Figuras* createTrian(void){
    Figuras* f = malloc(sizeof(Figuras));
    float cx = estadosrender.ven_width / 2.f + initOffsetX + desplazamientoX_total;
    float cy = estadosrender.ven_height / 2.f + initOffsetY;

    f->triangulo.p1.unpack.x = cx;
    f->triangulo.p1.unpack.y = cy - 50;
    f->triangulo.p2.unpack.x = cx - 50;
    f->triangulo.p2.unpack.y = cy + 50;
    f->triangulo.p3.unpack.x = cx + 50;
    f->triangulo.p3.unpack.y = cy + 50;
    f->triangulo.color.hex = 0xFF0000FF;
    f->data.type = TRIAN;

    desplazamientoX_total += stepX;
    return f;
}
