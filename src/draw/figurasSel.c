#include "figuras.h"
#include "draw.h"
#include "lerp.h"

void draw_figura(Figuras *fig){
    switch(fig->data.type){
        case LINEA:
        {
            Linea f = fig->linea;
            draw_circle(32,f.p1.unpack.x,f.p1.unpack.y,5.f,0x0000ffff);
            draw_circle(32,f.p2.unpack.x,f.p2.unpack.y,5.f,0x0000ffff);

            draw_linea(f.p1.unpack.x,f.p1.unpack.y,f.p2.unpack.x,f.p2.unpack.y,f.color.hex);
        }
        break;
        
        case CURVA:
        {
            Curva c = fig->curva;
            vec2 punto;
            for(float t=0; t<=1; t+=0.001){
                punto = lerp2v2(c.p1,c.p2,c.p3,t);
                draw_pixel(punto.unpack.x, punto.unpack.y, c.color.hex);
            }
            draw_circle(32,c.p1.unpack.x,c.p1.unpack.y,5.f,0x0000ffff);
            draw_circle(32,c.p2.unpack.x,c.p2.unpack.y,5.f,0x0000ffff);
            draw_circle(32,c.p3.unpack.x,c.p3.unpack.y,5.f,0x0000ffff);
        }
        break;

        case CUADRO:
        {
            Cuadro c = fig->cuadro;
            draw_rectangle(c.pos.unpack.x, c.pos.unpack.y, c.w, c.h, c.color.hex);
            draw_circle(32,c.pos.unpack.x,c.pos.unpack.y,5.f,0x0000ffff);
            draw_circle(32,c.pos.unpack.x+c.w,c.pos.unpack.y,5.f,0x0000ffff);
            draw_circle(32,c.pos.unpack.x+c.w,c.pos.unpack.y+c.h,5.f,0x0000ffff);
            draw_circle(32,c.pos.unpack.x,c.pos.unpack.y+c.h,5.f,0x0000ffff);
        }
        break;


        case TRIAN:
        {
            Triangulo t = fig->triangulo;
            draw_circle(32,t.p1.unpack.x,t.p1.unpack.y,5.f,0x0000ffff);
            draw_circle(32,t.p2.unpack.x,t.p2.unpack.y,5.f,0x0000ffff);
            draw_circle(32,t.p3.unpack.x,t.p3.unpack.y,5.f,0x0000ffff);
            draw_triangle(t.p1.unpack.x, t.p1.unpack.y, t.p2.unpack.x, t.p2.unpack.y,t.p3.unpack.x, t.p3.unpack.y, t.color.hex);

            fillTriangle(t);
        }
        break;

        case CIRC:{
            Circulo c = fig->circulo;
            draw_circle_points(c.r,c.pos.unpack.x,c.pos.unpack.y,c.color.hex);
        }
        break;
    }
}