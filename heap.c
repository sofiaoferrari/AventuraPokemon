#include "heap.h"
#include <stdio.h>

#define EXITO 0
#define ERROR -1
#define VACIO 0

#define IGUAL 0     //derecha
#define MAYOR 1    //derecha
#define MENOR -1  //izquierda

#define POSICION_RAIZ 0

bool heap_vacio(heap_t* heap) {
    if (!heap || (heap->tope == VACIO)) 
        return true;
  
    return false;
}

void* heap_raiz(heap_t* heap) {
    if (!heap || (heap->tope == VACIO))
        return NULL;

    return heap->vector[POSICION_RAIZ];
}

void swap(void** vector, size_t i, size_t j) {
    void* aux = vector[i];
    vector[i] = vector[j];
    vector[j] = aux;
}

size_t posicion_del_padre(size_t n) {
    return (n-1)/2;
}

size_t posicion_hijo_derecho(size_t n) {
    return 2*n+2;
}

size_t posicion_hijo_izquierdo(size_t n) {
    return 2*n+1;
}

void sift_up(heap_t* heap, size_t posicion_actual) {
    if (posicion_actual == POSICION_RAIZ) return;

    size_t posicion_padre = posicion_del_padre(posicion_actual);
    int comparacion = heap->comparador(heap->vector[posicion_actual], heap->vector[posicion_padre]);

    if (comparacion == MENOR) {
        swap(heap->vector, posicion_actual, posicion_padre);
        sift_up(heap, posicion_padre);
    }
}

void sift_down(heap_t* heap, size_t posicion_actual) {
    heap_comparador comparador = heap->comparador;
    size_t posicion_derecha = posicion_hijo_derecho(posicion_actual);
    size_t posicion_izquierda = posicion_hijo_izquierdo(posicion_actual);
    size_t posicion_menor = posicion_izquierda;
    
    if (posicion_izquierda >= heap->tope) return;
    else if (posicion_derecha < heap->tope) {
        int comparacion_hijos = comparador(heap->vector[posicion_derecha], heap->vector[posicion_izquierda]);
        if (comparacion_hijos == MENOR)
            posicion_menor = posicion_derecha;
    }

    int comparacion = comparador(heap->vector[posicion_actual], heap->vector[posicion_menor]);
    if (comparacion == MAYOR) {
        swap(heap->vector, posicion_actual, posicion_menor);
        sift_down(heap, posicion_menor);
    }
}

int heap_extraer_raiz(heap_t* heap) {
    if (!heap || heap_vacio(heap)) return ERROR;

    size_t ultima_posicion = heap->tope -1;
    void* elemento = heap->vector[POSICION_RAIZ];

    swap(heap->vector, POSICION_RAIZ, ultima_posicion);
    if(heap->destructor)
        heap->destructor(elemento);

    heap->tope --;

    if (!heap_vacio(heap))
        sift_down(heap, POSICION_RAIZ);
    
    return EXITO;
}

void destruir_elemento(heap_t* heap) {
    if (heap->tope != VACIO) {
        heap_extraer_raiz(heap);
        destruir_elemento(heap);
    }
}

void heap_destruir(heap_t* heap) {

    if (heap) {
      destruir_elemento(heap);
      free(heap->vector);
    }
        
    free(heap);
}

int heap_insertar(heap_t* heap, void* elemento) {
    if (!heap) return ERROR;

    size_t tamanio = heap->tope +1;

    void** array_aux = realloc(heap->vector, sizeof(void*)*tamanio);
    if (!array_aux) return ERROR;
    
    heap->vector = array_aux;
    heap->vector[heap->tope] = elemento;

    heap->tope ++;

    sift_up(heap, heap->tope -1);

    return EXITO;
}

heap_t* heap_crear(heap_comparador comparador, heap_liberar_elemento destructor) {
    if (!comparador) return NULL;

    heap_t* heap = (heap_t*)calloc(1, sizeof(heap_t));
    if (!heap) return NULL;
    
    heap->comparador = comparador;
    heap->destructor = destructor;

    return heap;
}