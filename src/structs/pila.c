#include "pila.h"
#include "nodo.h"
#include <stdio.h>

void push(Pila *pila, void *dato){
    Nodo *nuevo = crearNodo(dato);
    nuevo->sig = pila->cima;
    pila->cima = nuevo;
}

void* pop(Pila *pila){    
    Nodo *aux = pila->cima;
    pila->cima = aux->sig;
    void *dato = aux->dato;
    free(aux);
    return dato;
}

void freePila(Pila *pila){
    while (pila->cima != NULL) {
        Nodo *aux = pila->cima;
        pila->cima = aux->sig;
        free(aux);
    }
}
