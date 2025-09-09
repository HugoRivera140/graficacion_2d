#include "draw.h"
#include "linea.h"
#include <math.h>


void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color){
    draw_linea(x0, y0, x1, y1, color);
    draw_linea(x1, y1, x2, y2, color);
    draw_linea(x2, y2, x0, y0, color);
}
void draw_rectangle(int x0, int y0, int w, int h, uint32_t color){
    draw_linea(x0, y0, x0+w, y0, color);
    draw_linea(x0+w, y0, x0+w, y0+h, color);
    draw_linea(x0+w, y0+h, x0, y0+h, color);
    draw_linea(x0, y0+h, x0, y0, color);
}

void draw_circle(int numvert, int x0, int y0, int radio, uint32_t color){

    float PI = 3.1416;
    for(int i=0; i<numvert;++i){
        float angulo = (i*(2*PI)) /numvert;
        float angulo_s = (((i+1)%numvert)*2*PI)/numvert;
        int xa = x0+cos(angulo)*radio;
        int ya = y0+sin(angulo)*radio;
        int xs = x0+cos(angulo_s)*radio;
        int ys = y0+sin(angulo_s)*radio;
        draw_linea(round(xa),round(ya),round(xs),round(ys),color);
    }
}
void draw_circle_points(int r, int xc, int yc, uint32_t color){
    int x = 0;
    int y = r;
    int p = 1- r;
    while (x <= y) {
        draw_pixel(xc- x, yc + y, color);
        draw_pixel(xc + x, yc- y, color);
        draw_pixel(xc + x, yc + y, color);
        draw_pixel(xc- x, yc- y, color);
        draw_pixel(xc + y, yc + x, color);
        draw_pixel(xc- y, yc + x, color);
        draw_pixel(xc + y, yc- x, color);
        draw_pixel(xc- y, yc- x, color);
        x++;
        if (p < 0) p += 2*x + 1;
        else {
            y--;
            p += 2*(x- y) + 1;
        }
    }
}
