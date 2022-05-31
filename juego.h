#ifndef __JUEGO_H__
#define __JUEGO_H__

#include "batallas.h"
#include "estructuras.h"


bool fin_de_la_partida;
bool existe_personaje;
bool comenzar;
bool se_realizo_prestamo;


typedef struct juego {
    heap_t* heap_gimnasios;
    personaje_t* personaje;
    int partidas;
} juego_t;

void juego_destruir(juego_t* juego);

juego_t* crear_juego();

void cambiar_party(personaje_t* personaje);

void tomar_prestado_pokemon(gimnasio_t* gimnasio, personaje_t* personaje);

void batallar(juego_t* juego);

void siguiente_gimnasio(juego_t* juego);

void comenzar_partida(juego_t* juego);

void simular_partida(juego_t* juego);


#endif /*__JUEGO_H__*/