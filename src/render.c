#include "render.h"
#include "color/colores.h"
#include "draw/draw.h"
#include "global.h"
#include "draw/linea.h"
#include "stdlib.h"
#include "math.h"
#include "draw/vectores.h"
#include "draw/lerp.h"
#include "draw/figuras.h"
#include "memoria/memoria.h"
#include <stdio.h>

vec2* punto_seleccionado = NULL;

vec2 *pivote_mas_cerca(vec2 mp, Figuras *figs, float umbral){
	int a = 0;
	int b = array_size(figs)-1;
	
	float low;
	float high;
	float centro;
	for(int i=0; i<array_size(figs);i++){
		int r = (a+b)/2;
		low = distanciav2(mp,figs[a].cuadro.pos);
		high = distanciav2(mp,figs[b].cuadro.pos);
		centro = distanciav2(mp,figs[r].cuadro.pos);

		if(fabs(low) <= umbral)
			return &figs[a].cuadro.pos;
		else if(fabs(high) <= umbral)
			return &figs[b].cuadro.pos;
		else if(fabs(centro) <= umbral)
			return &figs[b].cuadro.pos;

		if(r<b)
			b=r;
		else if(r>a)
			a=r;


	}
	return NULL;
}

void render_input(){
	if(estadosrender.evento.type == SDL_EVENT_QUIT){
		estadosrender.run = 0;
	}
	if (estadosrender.evento.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
	// buscar el pivote mas cerca
	// encontrar referencia mas cercana a el
		if(!punto_seleccionado){
			punto_seleccionado = pivote_mas_cerca((vec2){{estadosrender.evento.motion.x,estadosrender.evento.motion.y}},estadosrender.figuras_buffer,10.f);
			if(punto_seleccionado){
				printf("Punto mas cercano(%3.f, %3.f)\n",punto_seleccionado->unpack.x,punto_seleccionado->unpack.y);
			}
		}
	}
	else if(estadosrender.evento.type == SDL_EVENT_MOUSE_BUTTON_UP){
		if(punto_seleccionado){
		//Modificar la figura
		punto_seleccionado->unpack.x = estadosrender.evento.motion.x;
		punto_seleccionado->unpack.y = estadosrender.evento.motion.y;
		punto_seleccionado = NULL;
		}
	}
}


void clear_color_buffer(){
    for(int y=0; y<estadosrender.ven_height; ++y){
        for(int x=0; x<estadosrender.ven_width; ++x){
            draw_pixel(x, y, estadosrender.clear_color.hex);
        }
    }	
}

void copy_buffer_to_texture(void){
	SDL_UpdateTexture(estadosrender.textura, NULL, estadosrender.color_buffer,(int)(estadosrender.ven_width*sizeof(int)));
	SDL_RenderTexture(estadosrender.renderer, estadosrender.textura, NULL, NULL);
}

//============== Funciones ==============

void update(void){
    
    Color AZUL = {0x0000ffff};
    Color VERDE = {0x00ff00ff};
    float t;
	
	for(int i=-10; i<10; i++){
		int y = (estadosrender.ven_height/2.f)+i;
		for(int x = 0; x<estadosrender.ven_width; ++x){
			t = x/(float)estadosrender.ven_width;
			// color_buffer[y*w+x] = lerp_color(AZUL,VERDE,t).hex;
            draw_pixel(x,y,lerp_color(AZUL,VERDE,t).hex);
        }
	}
}

//================= Practica 0 =================
void pattern1(int zh, int zw){
	int pointY = estadosrender.ven_height/zh;
	int pointX = estadosrender.ven_width/zw;
    Color BLANCO = {0xffffffff};

	for(int y = 0; y<estadosrender.ven_height; y+=pointY){
		for(int x = 0; x<estadosrender.ven_width; x+=pointX){
			// color_buffer[y*w+x] = BLANCO.hex;
            draw_pixel(x,y,BLANCO.hex);
		} 
	}
}
void pattern2(int zh){
	int lineY = estadosrender.ven_height/zh;
    Color BLANCO = {0xffffffff};
	
	for(int y = 0; y<estadosrender.ven_height; y+=lineY){
		for(int x = 0; x<estadosrender.ven_width; x++){
			// color_buffer[y*w+x] = BLANCO.hex;
            draw_pixel(x,y,BLANCO.hex);
		} 
	}	
}
void pattern3(int zh,int zw){
	int lineY = estadosrender.ven_height/zh;
	int wallX = estadosrender.ven_width/zw;
    Color BLANCO = {0xffffffff};

	for(int y = lineY; y<estadosrender.ven_height; y+=lineY){
		for(int x = 0; x<estadosrender.ven_width; x++){
			// color_buffer[y*w+x] = BLANCO.hex;
            draw_pixel(x,y,BLANCO.hex);
		} 
	}		
	for(int y = 0; y<estadosrender.ven_height; y++){
		for(int x = wallX; x<estadosrender.ven_width; x+=wallX){
			// color_buffer[y*w+x] = BLANCO.hex;
			draw_pixel(x,y,BLANCO.hex);
		} 
	}	
}
//==============================================
void updateLinea(void){
    
    Color AZUL = {0x0000ffff};
    // Color VERDE = {0x00ff00ff};
	int y0 = 20;
	
    for(int y=y0; y<estadosrender.ven_height; y+=20) 
	{draw_linea(0,y0,estadosrender.ven_width, y, AZUL.hex);}
	
}

//==============================================
void updateDDA(void){
	Color AZUL = {0x0000ffff};
	int y0 = 20;
    
	for(int y=y0; y<estadosrender.ven_height; y+=20) 
	{draw_linea(0,y0,estadosrender.ven_width, y, AZUL.hex);}
}
//==============================================
void updateBressenham(void){
	Color AZUL = {0x0000ffff};
	int y0 = 20;
    
	for(int y=y0; y<estadosrender.ven_height; y+=20) 
	{draw_linea(0,y0,estadosrender.ven_width, y, AZUL.hex);}

}
void updateTriangle(void){
	Color BLANCO = {0xffffffff};
	Color ROJO = {0xff0000ff};

	//===================Camisa===================
	draw_triangle(180,500,230,500,210,520,BLANCO.hex);
	draw_triangle(270,500,320,500,290,520,BLANCO.hex);
	//===================Corbata===================
	draw_triangle(240,550,260,550,250,560,ROJO.hex);
	//===================Mangas===================
	draw_triangle(70,400,100,380,100,420,BLANCO.hex);
	draw_triangle(430,400,400,380,400,420,BLANCO.hex);
}
void updateRectangle(void){
	Color AMARILLO = {0xf7f707ff};
	int x0 = 100;
	int y0 = 200;

	draw_rectangle(x0,y0,100,100,AMARILLO.hex);

}
void updateCirclePoints(void){
	
	// Color AZUL = {0x0000ffff};
	Color CYAN = {0x5DE2E7ff};
    Color NEGRO = {0x00000000};
	Color AMARILLO = {0xBFD641ff};
	int r = 50;
	int xc = 180;
	int yc = 290;
	
	//Ojos
	draw_circle_points(r, xc, yc, NEGRO.hex);
	draw_circle_points(r, 324, 290, NEGRO.hex);
	//Pupilas
	draw_circle_points(20, 180, 292, CYAN.hex);
	draw_circle_points(20, 324, 292, CYAN.hex);
	//Iris
	draw_circle_points(13, 180, 293, NEGRO.hex);
	draw_circle_points(13, 324, 293, NEGRO.hex);
	//Hoyos
	draw_circle_points(11, 114.23, 233.14, AMARILLO.hex);
	draw_circle_points(13, 242.76, 220.27, AMARILLO.hex);
	draw_circle_points(12, 378.11, 217.41, AMARILLO.hex);
	draw_circle_points(13.5, 363, 352.54, AMARILLO.hex);
	draw_circle_points(17, 323.65, 429.3, AMARILLO.hex);
	draw_circle_points(19, 233.15, 467.2, AMARILLO.hex);
	draw_circle_points(20, 139.34, 442.56, AMARILLO.hex);
}
void updateCircle(void){
	
	Color AZUL = {0x0000ffff};
	// Color VERDE = {0x00ff00ff};
	int numvert = 32;
	int x0 = 400;
	int y0 = 200;
	int radio = 150;

	draw_circle(numvert,x0,y0,radio,AZUL.hex);	
}

void updateCurva(void){
	Color ROJO = {0xff0000ff};

	vec2 p1 = {.unpack = {.x = 100, .y = 100}};
	vec2 p2 = {.unpack = {.x = 300, .y = 100}};
	vec2 p3 = {.unpack = {.x = 200, .y = 30}};

	vec2 punto;
	for(float t=0; t<=1; t+=0.01){
		punto = lerp2v2(p1,p2,p3,t);
		draw_pixel(punto.unpack.x, punto.unpack.y, ROJO.hex);
	}

}


void _init(void){
	//inicializar todas las variables a utilizar
	vec2 pc1 = {{400.f,360.f}};
	vec2 pc2 = {{600.f,100.f}};
	vec2 pc3 = {{800.f,360.f}};

	Linea linea = {
		.p1 = (vec2){{800,100}},
		.p2 = (vec2){{600,250}},
		.offset_mem1 = {0},
		.color = (Color){0xab00abff},
		.type = LINEA
	};

	Curva curva = {
		.p1 = pc1,
		.p2 = pc2,
		.p3 = pc3,
		.color = (Color){0xffff00ff},
		.type = CURVA
	};

	Circulo circ = {
		.pos = {{estadosrender.ven_width/2.f,estadosrender.ven_height/2.f}},
		.r = 20.f,
		.vert = 32,
		.offset_mem1 = {0},
		.color = (Color){0x00ffffff},
		.type = CIRC
	};

	Cuadro cuadro = {
		.pos = {{140.f,140.f}},
		.w = 140,
		.h = 200,
		.offset_mem1 = {0},
		.color = (Color){0x140140ff},
		.type = CUADRO
	};

	Triangulo triangulo = {
		.p1 = {{100.f,500.f}},
		.p2 = {{300.f,680.f}},
		.p3 = {{300.f,440.f}},
		.color = (Color){0xffffffff},
		.type = TRIAN
	};

	Figuras test1 = {.linea   = linea};
    Figuras test2 = {.curva   = curva};
    Figuras test3 = {.circulo = circ};
    Figuras test4 = {.cuadro = cuadro};
    Figuras test5 = {.triangulo = triangulo};

	// Figuras test1 = {*(FigComun*)&linea};
	// Figuras test2 = {.curva = curva};
	// Figuras test3 = {*(FigComun*)&circ};

	draw_figura(&test1);
	draw_figura(&test2);
	draw_figura(&test3);
	draw_figura(&test4);
	draw_figura(&test5);

	pushto_array(estadosrender.figuras_buffer,test1);
	pushto_array(estadosrender.figuras_buffer,test2);
	pushto_array(estadosrender.figuras_buffer,test3);
	pushto_array(estadosrender.figuras_buffer,test4);
	pushto_array(estadosrender.figuras_buffer,test5);

}

void updateFiguras(void){
	for(int i=0; i<array_size(estadosrender.figuras_buffer); i++)
		draw_figura(&estadosrender.figuras_buffer[i]);
}

void render_frame(void){
	SDL_RenderPresent(estadosrender.renderer);
}