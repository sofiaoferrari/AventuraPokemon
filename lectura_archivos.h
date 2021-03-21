#ifndef __LECTURA_DE_ARCHIVOS_H__
#define __LECTURA_DE_ARCHIVOS_H__

#include "estructuras.h"
#include "juego.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define LECTURA "r"

//archivos para la simulacion del juego
#define ARCHIVO_GIMNASIO "gimnasio.txt"
#define ARCHIVO_PERSONAJE "personaje.txt" 

#define INICIAL_GIMNASIO 'G'
#define INICIAL_LIDER 'L'
#define INICIAL_ENTRENADOR 'E'
#define INICIAL_POKEMON 'P'

#define FIN_ARCHIVO 'F'
#define OTRA 0

#define FORMATO_GIMNASIO "%c;%100[^;]; %d; %d\n"
#define CAMPOS_GIMNASIO 4

#define FORMATO_ENTRENADOR "%c;%100[^\n]\n"
#define CAMPOS_ENTRENADOR 2

#define FORMATO_POKEMON "%c;%50[^;]; %d; %d; %d\n"
#define CAMPOS_POKEMON 5

void capturar_datos_pokes(pokemon_t* pokemon_agregado, pokemon_t* pokemon_datos);

bool cargar_gimnasio(FILE* archivo, heap_t* heap);

personaje_t* cargar_personaje_principal(FILE* archivo);

bool letras_son_iguales(char letra_recibida, char letra_esperada);

bool verificar_archivo(FILE* archivo, const char* nombre_archivo, char inicial_esperada);

bool leer_archivo_personaje(juego_t* juego); //void

bool leer_archivo_gimnasio(juego_t* juego);

#endif  /* __LECTURA_DE_ARCHIVOS_H__ */