#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estructuras.h"
#include "batallas.h"
#include "imprenta.h"

#define ERROR_2 2


void bonificar_pokemon(pokemon_t* poke) {
    if (poke->bonificaciones < 63) {
        poke->bonificaciones ++;
        poke->velocidad++;
        poke->ataque++;
        poke->defensa++;
    }
}

int funcion_batalla_1(void* pkm_1, void* pkm_2) {
    if(!pkm_1 || !pkm_2) return ERROR_2;
    pokemon_t* poke_usuario = (pokemon_t*)pkm_1;
    pokemon_t* poke_rival = (pokemon_t*)pkm_2;

    if (poke_usuario->velocidad >= poke_rival->velocidad) {
        bonificar_pokemon(poke_usuario);
        return GANO_PRIMERO;
    }
    return GANO_SEGUNDO;
}

int funcion_batalla_2(void* pkm_1, void* pkm_2) {
    if(!pkm_1 || !pkm_2) return ERROR_2;
    pokemon_t* poke_usuario = (pokemon_t*)pkm_1;
    pokemon_t* poke_rival = (pokemon_t*)pkm_2;

    if ((poke_usuario->ataque >= poke_rival->ataque) && 
        (poke_usuario->defensa >= poke_rival->defensa)) {
        bonificar_pokemon(poke_usuario);
        return GANO_PRIMERO;
    }
    return GANO_SEGUNDO;
}

int funcion_batalla_3(void* pkm_1, void* pkm_2) {
    if(!pkm_1 || !pkm_2) return ERROR_2;
    pokemon_t* poke_usuario = (pokemon_t*)pkm_1;
    pokemon_t* poke_rival = (pokemon_t*)pkm_2;

    if ((poke_usuario->ataque <= poke_rival->ataque) && 
        (poke_usuario->defensa <= poke_rival->defensa)) {
        bonificar_pokemon(poke_usuario);
        return GANO_PRIMERO;
    }
    return GANO_SEGUNDO;
}

int funcion_batalla_4(void* pkm_1, void* pkm_2) {
    if(!pkm_1 || !pkm_2) return ERROR_2;
    pokemon_t* poke_usuario = (pokemon_t*)pkm_1;
    pokemon_t* poke_rival = (pokemon_t*)pkm_2;

    if (strcmp(poke_usuario->nombre_pokemon, poke_rival->nombre_pokemon) < 0) {
        bonificar_pokemon(poke_usuario);
        return GANO_PRIMERO;
    }
    return GANO_SEGUNDO;
}

int funcion_batalla_5(void* pkm_1, void* pkm_2) {
    if(!pkm_1 || !pkm_2) return ERROR_2;
    pokemon_t* poke_usuario = (pokemon_t*)pkm_1;
    pokemon_t* poke_rival = (pokemon_t*)pkm_2;

    if ((poke_usuario->ataque >= poke_rival->ataque) && 
        (poke_usuario->defensa >= poke_rival->defensa) &&
        (poke_usuario->velocidad >= poke_rival->velocidad)) {
        bonificar_pokemon(poke_usuario);
        return GANO_PRIMERO;
    }
    return GANO_SEGUNDO;
}