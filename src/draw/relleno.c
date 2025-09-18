#include "draw.h"
#include "vectores.h"
#include "../memoria/memoria.h"
#include "figuras.h"
#include "linea.h"
#include "../structs/pila.h"
#include "../render.h"
#include "../global.h"

#include <stdlib.h>
#include <stdio.h>

// ---------------------------
// Triángulo (Scanline)
// ---------------------------
static void sortY(vec2 *p1, vec2 *p2, vec2 *p3);
static void fill_flat_bottom(vec2 p1, vec2 p2, vec2 p3, uint32_t color);
static void fill_flat_top(vec2 p1, vec2 p2, vec2 p3, uint32_t color);

void fillTriangle(Triangulo *triangulo, uint32_t color){
    vec2 p1 = triangulo->p1;
    vec2 p2 = triangulo->p2;
    vec2 p3 = triangulo->p3;

    sortY(&p1, &p2, &p3);

    if(p2.unpack.y == p3.unpack.y){
        fill_flat_bottom(p1,p2,p3,color);
    } else if(p1.unpack.y == p2.unpack.y){
        fill_flat_top(p1,p2,p3,color);
    } else {
        float cy = p2.unpack.y;
        float cx = p1.unpack.x + (cy - p1.unpack.y)*(p3.unpack.x - p1.unpack.x)/(p3.unpack.y - p1.unpack.y);
        vec2 pnew = {{cx, cy}};

        fill_flat_bottom(p1,p2,pnew,color);
        fill_flat_top(p2,pnew,p3,color);
    }
}

static void sortY(vec2 *p1, vec2 *p2, vec2 *p3){
    vec2 aux;
    if(p1->unpack.y > p2->unpack.y){ aux = *p1; *p1 = *p2; *p2 = aux; }
    if(p2->unpack.y > p3->unpack.y){ aux = *p2; *p2 = *p3; *p3 = aux; }
    if(p1->unpack.y > p2->unpack.y){ aux = *p1; *p1 = *p2; *p2 = aux; }
}

static void fill_flat_bottom(vec2 p1, vec2 p2, vec2 p3, uint32_t color){
    float mi = (p2.unpack.x - p1.unpack.x)/(p2.unpack.y - p1.unpack.y);
    float mf = (p3.unpack.x - p1.unpack.x)/(p3.unpack.y - p1.unpack.y);
    float xi = p1.unpack.x;
    float xf = p1.unpack.x;
    for(int y=(int)p1.unpack.y; y<=(int)p2.unpack.y; y++){
        draw_linea((int)xi, y, (int)xf, y, color);
        xi += mi; xf += mf;
    }
}

static void fill_flat_top(vec2 p1, vec2 p2, vec2 p3, uint32_t color){
    float mi = (p3.unpack.x - p1.unpack.x)/(p3.unpack.y - p1.unpack.y);
    float mf = (p3.unpack.x - p2.unpack.x)/(p3.unpack.y - p2.unpack.y);
    float xi = p3.unpack.x;
    float xf = p3.unpack.x;
    for(int y=(int)p3.unpack.y; y>=(int)p1.unpack.y; y--){
        draw_linea((int)xi, y, (int)xf, y, color);
        xi -= mi; xf -= mf;
    }
}

uint32_t getColor(vec2 *pixel){
    return estadosrender.color_buffer[(int)pixel->unpack.y * estadosrender.ven_width + (int)pixel->unpack.x];
}

void fill_flood_iterative(vec2 *pInicial, uint32_t fill_color){
    Pila *pila = calloc(1,sizeof(Pila));
    int total_pixeles = estadosrender.ven_width * estadosrender.ven_height;
    char *verificado = calloc(total_pixeles,sizeof(char));

    uint32_t color_obj = getColor(pInicial);
    if(color_obj == fill_color){ free(verificado); return; }

    vec2 *start = malloc(sizeof(vec2));
    *start = *pInicial;
    push(pila, start);

    while(pila->cima != NULL){
        vec2 *pixel = pop(pila);
        int x = (int)pixel->unpack.x;
        int y = (int)pixel->unpack.y;

        if(x<0 || x>=estadosrender.ven_width || y<0 || y>=estadosrender.ven_height){
            free(pixel); continue;
        }

        int idx = y*estadosrender.ven_width + x;
        uint32_t cur_color = getColor(pixel);
        if(verificado[idx] || cur_color != color_obj){
            free(pixel); continue;
        }

        draw_pixel(x, y, fill_color);
        verificado[idx] = 1;

        vec2 vecinos[4] = {{{x+1,y}},{{x-1,y}},{{x,y+1}},{{x,y-1}}};
        for(int i=0;i<4;i++){
            int nx = (int)vecinos[i].unpack.x;
            int ny = (int)vecinos[i].unpack.y;
            int nIdx = ny*estadosrender.ven_width + nx;
            if(nx>=0 && nx<estadosrender.ven_width && ny>=0 && ny<estadosrender.ven_height && !verificado[nIdx]){
                vec2 *np = malloc(sizeof(vec2));
                *np = vecinos[i];
                push(pila,np);
            }
        }

        free(pixel);
    }

    free(verificado);
    freePila(pila);
    free(pila);
}

void fill_cuadro(Cuadro *cuadro, uint32_t color){
    vec2 centro = {{cuadro->pos.unpack.x + cuadro->w/2.0f,
                    cuadro->pos.unpack.y + cuadro->h/2.0f}};
    fill_flood_iterative(&centro, color);
}

void fill_circulo(Circulo *circulo, uint32_t color){
    vec2 centro = circulo->pos;
    fill_flood_iterative(&centro, color);
}

