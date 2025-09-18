#pragma once
#include <stdio.h>
#include "nodo.h"

typedef struct _pila{
    Nodo *cima;
    int datos;
}Pila;

void push(Pila *pila, void *dato);
void* pop(Pila *pila);
void freePila(Pila *pila);
