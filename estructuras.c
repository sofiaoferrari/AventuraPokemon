#include <stdio.h>

#include "estructuras.h"

int comparador(void* elemento1, void* elemento2) {
    int resultado = 2; //"error"
    if (!elemento1 || !elemento2) return resultado;
    
    gimnasio_t* gym1 = (gimnasio_t*) elemento1;
    gimnasio_t* gym2 = (gimnasio_t*) elemento2;
    
    int ele1 = gym1->dificultad;
    int ele2 = gym2->dificultad;

    if (ele1 == ele2) resultado = IGUALES;
    else if (ele1 > ele2) resultado = ANTERIOR_MAYOR;
    else if (ele1 < ele2) resultado = ANTERIOR_MENOR;

    return resultado;
}

void destructor_pokemones(pokemon_t* pokemon) {
    if(!pokemon) return;
    
    free(pokemon);
}

void destruir_lista_pokemones(lista_t* lista_de_pokemones) {
    if (!lista_de_pokemones) return;

    while (lista_de_pokemones->cantidad > VACIA) {
        pokemon_t* pokemon = (pokemon_t*)lista_ultimo(lista_de_pokemones);

        destructor_pokemones(pokemon);
        lista_borrar(lista_de_pokemones);
    }
    
    
    lista_destruir(lista_de_pokemones);

}

/**/
void destructor_entrenadores(entrenador_t* entrenador) {
    if(!entrenador) return;
       
    
    if (entrenador->lista_de_pokemones) 
        destruir_lista_pokemones(entrenador->lista_de_pokemones);


    free(entrenador);
}

void destructor_personaje(personaje_t* personaje) {
    if(!personaje) return;
    
    if (personaje->entrenador) {
       // destructor_entrenadores(personaje->entrenador);
       lista_destruir(personaje->entrenador->lista_de_pokemones);
       free(personaje->entrenador);
    }
    if (personaje->pokemones_obtenidos)
        destruir_lista_pokemones(personaje->pokemones_obtenidos);

    free(personaje);
}

void destructor_gimnasios(void* gimnasio_a_borrar) {

    if(!gimnasio_a_borrar) return;

    gimnasio_t* gimnasio = (gimnasio_t*) gimnasio_a_borrar;

    if (gimnasio->pila_de_entrenadores) {

    while (gimnasio->pila_de_entrenadores->cantidad > VACIA) {
        entrenador_t* entrenador = (entrenador_t*)lista_tope(gimnasio->pila_de_entrenadores);
        
        destructor_entrenadores(entrenador);
        lista_desapilar(gimnasio->pila_de_entrenadores);
    }
    }

    lista_destruir(gimnasio->pila_de_entrenadores);                     
    free(gimnasio);

}

gimnasio_t* crear_gimnasio(){
    gimnasio_t* gimnasio = (gimnasio_t*)calloc(1,sizeof(gimnasio_t));
    if(!gimnasio) return NULL;

    gimnasio->pila_de_entrenadores = lista_crear();
    
    return gimnasio;
}

entrenador_t* crear_entrenador(){
    entrenador_t* entrenador = (entrenador_t*)calloc(1,sizeof(entrenador_t));
    if(!entrenador) return NULL;

    entrenador->lista_de_pokemones = lista_crear();

    return entrenador;
}

personaje_t* crear_personaje(){
    personaje_t* personaje = (personaje_t*)calloc(1,sizeof(personaje_t));
    if(!personaje) return NULL;

    personaje->entrenador = crear_entrenador();
    personaje->pokemones_obtenidos = lista_crear(); //

    return personaje;
}

pokemon_t* crear_pokemon(){
    pokemon_t* pokemon = (pokemon_t*)calloc(1,sizeof(pokemon_t));
    if(!pokemon) return NULL;

    return pokemon;
}