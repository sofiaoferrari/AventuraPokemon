#ifndef __IMPRENTA_H__
#define __IMPRENTA_H__

#include "estructuras.h"

#define FORMATO_IMPRESION_POKE "%li. %-12s %-12d %-12d %-12d\n"


void clear_screen();

void pedir_ingreso();

void letra_erronea();

void continuar();

void imprimir_titulo_batalla(int id_funcion_batalla);

void imprimir_versus_pokemones(pokemon_t* poke_usuario, pokemon_t* poke_rival);

void error_no_hay_archivo(const char* tipo_archivo);

void mostrar_personaje (personaje_t* personaje);

void imprimir_nombre_entrenador(entrenador_t* entrenador);

void mostrar_entrenador(entrenador_t* entrenador);

void mostrar_gimnasios (gimnasio_t* gimnasio);

void imprimir_lista_pokemones(lista_t* lista_pokes);

void imprimir_poke_ganador(pokemon_t* pokemon);

void imprimir_derrota();

void imprimir_menu_derrota();

void imprimir_victoria();

void imprimir_menu_victoria();

void imprimir_menu_batalla();

void imprimir_menu_gimnasio();

void imprimir_inicio();

void imprimir_titulo();

void nos_calmamo();

#endif /*__IMPRENTA_H__*/