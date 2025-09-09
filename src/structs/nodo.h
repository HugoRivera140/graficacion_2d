#pragma once
#include <stdlib.h>

typedef struct nodo{
    void *dato;
    struct nodo *sig;
}Nodo;

Nodo* crearNodo(void*);