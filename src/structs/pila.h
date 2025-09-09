#pragma once
#include <stdio.h>

typedef struct _pila{
    int *cima;
    int *inicio;
    int datos;
}Pila;

void push(Pila *pila, void *datos);
void* pop(Pila *pila);
void freePila(Pila *pila);