#include "vectores.h"
#include "draw.h"
#include "../color/colores.h"
#include "figuras.h"

void sortY(vec2 *p1, vec2 *p2, vec2 *p3);
void fill_flat_bottom(vec2 p1, vec2 p2, vec2 c, uint32_t color);
void fill_flat_top(vec2 p1, vec2 p2, vec2 c, uint32_t color);

void fillTriangle(Triangulo triangulo){
    Color ROJO = {0xff0000ff};
    vec2 p1 = triangulo.p1;
    vec2 p2 = triangulo.p2;
    vec2 p3 = triangulo.p3;

    sortY(&p1,&p2,&p3); 

    if(p2.unpack.y == p3.unpack.y)
        fill_flat_bottom(p1,p2,p3,ROJO.hex);
    else if(p1.unpack.y == p2.unpack.y)
        fill_flat_top(p1,p2,p3,ROJO.hex);
    else{
        float cy = p2.unpack.y;
        float cx = (p2.unpack.y-p1.unpack.y)*(p3.unpack.x-p1.unpack.x)/(p3.unpack.y-p1.unpack.y)+p1.unpack.x;

        vec2 pnew = {{cx,cy}};
        fill_flat_bottom(p1,p2,pnew,ROJO.hex);
        fill_flat_top(p2,pnew,p3,ROJO.hex);
    }
}


void fill_flat_bottom(vec2 p1, vec2 p2, vec2 c, uint32_t color){
    //calcular pendiente inversa para x inicial(p1) y x final (c)
    float mi = (p2.unpack.x-p1.unpack.x)/(p2.unpack.y-p1.unpack.y);
    float mf = (c.unpack.x-p1.unpack.x)/(c.unpack.y-p1.unpack.y);
    float xi = p1.unpack.x;
    float xf = p1.unpack.x;

    for(int y=p1.unpack.y; y<=p2.unpack.y; y++){
        draw_linea((int)xi,y,(int)xf,y,color);
        xi += mi;
        xf += mf;
    }
}
void fill_flat_top(vec2 p1, vec2 p2, vec2 c, uint32_t color){
    //calcular pendiente inversa para x inicial(p1) y x final (c)
    float mi = (c.unpack.x-p1.unpack.x)/(c.unpack.y-p1.unpack.y);
    float mf = (c.unpack.x-p2.unpack.x)/(c.unpack.y-p2.unpack.y);
    float xi = c.unpack.x;
    float xf = c.unpack.x;

    for(int y=c.unpack.y; y>p1.unpack.y; y--){
        draw_linea((int)xi,y,(int)xf,y,color);
        xi -= mi;
        xf -= mf;
    }
}

void sortY(vec2 *p1, vec2 *p2, vec2 *p3) {
    vec2 aux;
    if(p1->unpack.y > p2->unpack.y){
        aux = *p1;
        *p1 = *p2;
        *p2 = aux;
    }
    if(p2->unpack.y > p3->unpack.y){
        aux = *p2;
        *p2 = *p3;
        *p3 = aux;
    }
    if(p1->unpack.y > p2->unpack.y){
        aux = *p1;
        *p1 = *p2;
        *p2 = aux;
    }
}
