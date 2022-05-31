#ifndef __ESTRUCTURAS_H__
#define __ESTRUCTURAS_H__

#include "lista.h"
#include "heap.h"

#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define EXITO 0
#define ERROR -1

#define MAX_VALOR_BONIFICACION 63
#define MAX_POKES_A_COMBATIR 6

#define GANO 1
#define PERDIO -1

#define IGUALES 0
#define ANTERIOR_MAYOR 1
#define ANTERIOR_MENOR -1

#define VACIA 0

typedef int (* funcion_batalla)(void*, void *);

typedef struct pokemon {
    char nombre_pokemon[20];
    int velocidad;
    int defensa;
    int ataque;
    int bonificaciones; //cada batalla ganada incrementa en 1 sus caracteristicas 
} pokemon_t;

typedef struct entrenador {
    char nombre_entrenador[20];
    lista_t* lista_de_pokemones; //6 pokemones a combatir
} entrenador_t;

typedef struct gimnasio{
    char nombre_gimnasio[30];
    int dificultad;
    int id; //id_ptero_afuncion
    funcion_batalla id_ptero_funcion;
    lista_t* pila_de_entrenadores;
} gimnasio_t;

typedef struct personaje {
    entrenador_t* entrenador;
    lista_t* pokemones_obtenidos;
    lista_t* entrenadores_derrotados;
    int medallas; //batallas ganadas
} personaje_t;


void destructor_gimnasios(void* gimnasio_a_borrar);

void destructor_entrenadores(entrenador_t* entrenador);

void destructor_personaje(personaje_t* personaje);

void destructor_pokemones(pokemon_t* pokemon);

gimnasio_t* crear_gimnasio();

entrenador_t* crear_entrenador();

personaje_t* crear_personaje();

pokemon_t* crear_pokemon();

int comparador(void* elemento1, void* elemento2) ;

#endif /* __ESTRUCTURAS_H__ */