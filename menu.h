#ifndef __MENU_H__
#define __MENU_H__

#include "estructuras.h"
#include "lectura_archivos.h"
#include "imprenta.h"
#include "juego.h"

#define AGREGAR_GIMNASIO 'A'
#define PROXIMA_BATALLA 'B'
#define MODIFICAR_PARTY 'C'
#define INGRESAR_ENTRENADOR 'E'
#define MOSTRAR_ENTRENADOR 'E'
#define FINALIZAR_PARTIDA 'F'
#define MOSTRAR_GIMNASIO 'G'
#define INICIAR_PARTIDA 'I'
#define PROXIMO_COMBATE 'N'
#define PROXIMO_GIMNASIO 'N'
#define REINTENTAR 'R'
#define SIMULAR_PARTIDA 'S'
#define TOMAR_PRESTADO 'T'


void menu_inicio();

//falta la batalla
void menu_gimnasio(personaje_t* personaje_principal, gimnasio_t* gimnasio_actual);

void menu_batalla(heap_t* gimnasios, pokemon_t* pokemon_usuario, pokemon_t* pokemon_rival, int resultado);

void menu_victoria(heap_t* gimnasios, entrenador_t* lider, personaje_t* usuario);

void menu_derrota(heap_t* gimnasios, personaje_t* usuario);


bool verificar_ingreso_inicio(juego_t* juego);

bool verificar_ingreso_gimnasio(juego_t* juego);

bool verificar_ingreso_batalla(juego_t* juego);

bool verificar_ingreso_victoria(juego_t* juego);

bool verificar_ingreso_derrota(juego_t* juego);

void menues(juego_t* juego, void (*funcion_impresion)(void), bool (*funcion_menu)(juego_t*));


#endif /*__MENU_H__*/