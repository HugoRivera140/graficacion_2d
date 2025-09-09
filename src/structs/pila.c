#include <pila.h>
#include <nodo.h>
#include <stdio.h>

void push(Pila *pila, void *dato){
    Nodo *nuevo = crearNodo(dato);
    nuevo->sig = pila->cima;
    pila->cima = nuevo;
}

void* pop(Pila *pila){    
    //Desencadenar el nodo
    Nodo *aux = pila->cima;
    pila->cima = aux->sig;
    aux->sig = NULL;
    //Estraer el dato
    void *dato = aux->dato;
    //Liberar nodo
    free(aux);
    return dato;
}

void freePila(Pila *pila){
    while (pila->cima != NULL) {
        Nodo *aux = pila->cima;   // Guardar el nodo actual
        pila->cima = aux->sig;    // Avanzar al siguiente nodo
        free(aux);                // Liberar el nodo actual
    }
}