#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

#define EXITO 0
#define ERROR -1

#define VACIA 0
#define PRIMERO 0
#define UNITARIA 1

/*
 * Procedimiento recursivo que dado un nodo inicio de una lista,
 * se ocupa de recorrerla llamandose asi mismo hasta llegar al nodo
 * fin de la misma. Una vez que llega al final de la lista, comienza
 * a liberar cada uno de los nodos, desde el ultimo hasta el primero. 
*/
void destruir_nodo(nodo_t* nodo) {

    if (nodo->siguiente)
        destruir_nodo(nodo->siguiente);
    free(nodo);
}

void lista_destruir(lista_t* lista) {
    if (lista && (lista->cantidad != VACIA)) {
        destruir_nodo(lista->nodo_inicio);
        lista->cantidad = VACIA;
    }
    if (lista) {
        free(lista);
    }
}

size_t lista_elementos(lista_t* lista) {
    if (!lista) return VACIA;
    return lista->cantidad;
}

bool lista_vacia(lista_t* lista) {

    return (!lista) || (lista->cantidad == VACIA);
}

void* lista_primero(lista_t* lista) {
    if ((!lista) || lista_vacia(lista))
        return NULL;
    
    return lista->nodo_inicio->elemento;
}

void* lista_ultimo(lista_t* lista) {
    if ((!lista) || lista_vacia(lista)) 
        return NULL;
    return lista->nodo_fin->elemento;
}

void* lista_tope(lista_t* lista) {
    return lista_ultimo(lista);
}

size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto) {
    if ((!lista) || lista_vacia(lista) || (!funcion))
        return VACIA;
    size_t cantidad = VACIA;
    bool corte = true;
    nodo_t* nodo_siguiente = lista->nodo_inicio;

    while ((corte == true) && nodo_siguiente) {
        corte = funcion(nodo_siguiente->elemento, contexto);
        nodo_siguiente = nodo_siguiente->siguiente;
        cantidad++;
    }
    return cantidad;
}

void lista_iterador_destruir(lista_iterador_t* iterador) {
    if(iterador)
        free(iterador);
}

void* lista_iterador_elemento_actual(lista_iterador_t* iterador) {
    if ((!iterador) || (!iterador->corriente)) 
        return NULL;
    return iterador->corriente->elemento;
}

bool lista_iterador_avanzar(lista_iterador_t* iterador) {
    if ((!iterador) || (iterador->lista->cantidad == VACIA)) 
        return false;
    iterador->corriente = iterador->corriente->siguiente;
    if (!iterador->corriente) return false;

    return true;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador) {
    return iterador->corriente;
}

lista_iterador_t* lista_iterador_crear(lista_t* lista) {
    if (!lista) return NULL;

    lista_iterador_t* iterador = calloc(1,sizeof(lista_iterador_t));
    if(!iterador) return NULL;

    iterador->lista = lista;
    iterador->corriente = lista->nodo_inicio;

    return iterador;
}

/*
 * Funcion que dada una lista y una posicion, recorre la lista de 
 * forma iterativa hasta llegar al nodo que se encuentra en dicha posicion.
 * Devulve el nodo obtenido.
*/
nodo_t* recorrer_lista(lista_t* lista, size_t posicion) {
    if ((lista->cantidad == UNITARIA) || (posicion == PRIMERO))
        return lista->nodo_inicio;
    nodo_t* nodo = lista->nodo_inicio->siguiente;
    for (int i = 1; i < posicion; i++) {
        nodo = nodo->siguiente;
    }
    return nodo;
}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion) {
    if ((!lista) || (posicion >= lista_elementos(lista))) 
        return NULL;
    nodo_t* nodo_obtenido = recorrer_lista(lista, posicion);

    return nodo_obtenido->elemento;
}

int lista_borrar(lista_t* lista) {
    if ((!lista) || lista_vacia(lista))
        return ERROR;
    if (lista->cantidad == UNITARIA) {
        free(lista->nodo_fin);
        lista->cantidad --;
        return EXITO;
    }
    nodo_t* nodo_anteultimo = recorrer_lista(lista, (lista->cantidad -2));
    lista->nodo_fin = nodo_anteultimo;
    free(nodo_anteultimo->siguiente);
    nodo_anteultimo->siguiente = NULL;
    lista->cantidad --;
    return EXITO;
}

int lista_desapilar(lista_t* lista) {
    return lista_borrar(lista);
}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion) {
    if ((!lista) || lista_vacia(lista))
        return ERROR;
    if (posicion >= (lista_elementos(lista) -1))
        return lista_borrar(lista);

    if (posicion == PRIMERO) {
        nodo_t* primer_nodo = lista->nodo_inicio;
        lista->nodo_inicio = primer_nodo->siguiente;
        free(primer_nodo);
        lista->cantidad --;
        return EXITO;
    }
    nodo_t* nodo_anterior = recorrer_lista(lista, posicion-1);
    nodo_t* nodo_siguiente = recorrer_lista(lista, posicion+1);
    free(nodo_anterior->siguiente);
    nodo_anterior->siguiente = nodo_siguiente;
    lista->cantidad --;
    return EXITO;
}

int lista_desencolar(lista_t* lista) {
    return lista_borrar_de_posicion(lista, PRIMERO);
}

int lista_insertar(lista_t* lista, void* elemento) {
    if (!lista) return ERROR;
    nodo_t* nodo_anterior = NULL;

    if (!lista_vacia(lista))
        nodo_anterior = lista->nodo_fin;

    nodo_t* nodo_aux = calloc(1, sizeof(nodo_t));
    if (!nodo_aux) return ERROR;

    lista->nodo_fin = nodo_aux; 
    lista->nodo_fin->elemento = elemento;
    if (!lista_vacia(lista)) nodo_anterior->siguiente = lista->nodo_fin;
    else if (lista_vacia(lista)) lista->nodo_inicio = lista->nodo_fin;
    lista->cantidad ++;

    return EXITO;
}

int lista_encolar(lista_t* lista, void* elemento) {
    return lista_insertar(lista, elemento);
}

int lista_apilar(lista_t* lista, void* elemento) {
    return lista_insertar(lista, elemento);
}

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion) {
    if (!lista) return ERROR;
    if (posicion >= lista_elementos(lista)) {
        int agregar = lista_insertar(lista, elemento);
        return agregar;
    }
    nodo_t* nodo_aux = calloc(1, sizeof(nodo_t));
    if (!nodo_aux) return ERROR;
    nodo_aux->elemento = elemento;

    nodo_t* nodo_actual = recorrer_lista(lista, posicion);
    nodo_aux->siguiente = nodo_actual;
    lista->cantidad ++;
    if (posicion == PRIMERO) {
        lista->nodo_inicio = nodo_aux;
        return EXITO;   
    }
    nodo_t* nodo_anterior = recorrer_lista(lista, posicion-1);
    nodo_anterior->siguiente = nodo_aux;
    return EXITO;
}

lista_t* lista_crear() {
    lista_t* nueva_lista = calloc(1,sizeof(lista_t));
    if (!nueva_lista) return NULL;
    
    return nueva_lista;
}