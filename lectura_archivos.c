#include <stdio.h>

#include "lectura_archivos.h"
#include "imprenta.h"


bool letras_son_iguales(char letra_recibida, char letra_esperada) {
    if (toupper(letra_recibida) == letra_esperada) 
        return true;

    return false;
}

char chequear_letra(FILE* archivo) {
    int primer_letra = fgetc(archivo);
    char letra = OTRA;

    if (letras_son_iguales((char)primer_letra, INICIAL_POKEMON))
        letra = INICIAL_POKEMON;
    else if (letras_son_iguales((char)primer_letra, INICIAL_ENTRENADOR))
        letra = INICIAL_ENTRENADOR;
    else if (letras_son_iguales((char)primer_letra, INICIAL_GIMNASIO))
        letra = INICIAL_GIMNASIO;
    else if (primer_letra == EOF)
        letra = FIN_ARCHIVO;

    ungetc(primer_letra, archivo);
    return letra;
}

void capturar_datos_pokes(pokemon_t* pokemon_agregado, pokemon_t* pokemon_datos){
    strcpy(pokemon_agregado->nombre_pokemon, pokemon_datos->nombre_pokemon);
    pokemon_agregado->velocidad = pokemon_datos->velocidad;
    pokemon_agregado->ataque = pokemon_datos->ataque;
    pokemon_agregado->defensa = pokemon_datos->defensa;
}

void cargar_pokemones(FILE* archivo, char* primer_char, entrenador_t* entrenador, lista_t* lista_obtenidos) {
   
    pokemon_t poke_aux;
    int campos = fscanf(archivo, FORMATO_POKEMON, primer_char, poke_aux.nombre_pokemon, &poke_aux.velocidad, 
                                                    &poke_aux.ataque, &poke_aux.defensa);

    while ((campos == CAMPOS_POKEMON) && (*primer_char == INICIAL_POKEMON)) {

        pokemon_t* poke_p = crear_pokemon();
        if(!poke_p) return;

        capturar_datos_pokes(poke_p, &poke_aux);

        if (entrenador->lista_de_pokemones->cantidad < MAX_POKES_A_COMBATIR)
            lista_insertar(entrenador->lista_de_pokemones, poke_p);
        else if (!lista_obtenidos) {
            destructor_pokemones(poke_p);
            return;
        }
        if (lista_obtenidos) 
            lista_insertar(lista_obtenidos, poke_p);
        

        *primer_char = chequear_letra(archivo);
        if (*primer_char == INICIAL_POKEMON)
            campos = fscanf(archivo, FORMATO_POKEMON,   primer_char, poke_aux.nombre_pokemon, 
                                                        &poke_aux.velocidad, &poke_aux.ataque, &poke_aux.defensa);

    }
}


personaje_t* cargar_personaje_principal(FILE* archivo) {
    char primer_char;
   
    personaje_t* personaje_p = crear_personaje();
    if(!personaje_p) return false;
    fscanf(archivo, FORMATO_ENTRENADOR, &primer_char, personaje_p->entrenador->nombre_entrenador);
    cargar_pokemones(archivo, &primer_char, personaje_p->entrenador, personaje_p->pokemones_obtenidos);


    if (personaje_p->entrenador->lista_de_pokemones->cantidad > VACIA)
        return personaje_p;
    else destructor_personaje(personaje_p);
    
    return NULL;
}

void cargar_entrenadores(FILE* archivo, char* primer_char, gimnasio_t* gimnasio) {
    
    entrenador_t entrenador_aux;
    int campos = fscanf(archivo, FORMATO_ENTRENADOR, primer_char, entrenador_aux.nombre_entrenador);
   
    while ((campos == CAMPOS_ENTRENADOR) && ((*primer_char == INICIAL_LIDER) || 
                                            (*primer_char == INICIAL_ENTRENADOR))) {
        entrenador_t* entrenador_p = crear_entrenador();
        if(!entrenador_p) return;
        strcpy(entrenador_p->nombre_entrenador, entrenador_aux.nombre_entrenador);

        cargar_pokemones(archivo, primer_char, entrenador_p, NULL);

        if (entrenador_p->lista_de_pokemones->cantidad > VACIA)
            lista_apilar(gimnasio->pila_de_entrenadores, entrenador_p);
        else destructor_entrenadores(entrenador_p);

        if (*primer_char == INICIAL_ENTRENADOR) 
            campos = fscanf(archivo, FORMATO_ENTRENADOR, primer_char, entrenador_aux.nombre_entrenador);    

    }

}

bool verificar_batalla(gimnasio_t* gimnasio) {
 
    switch (gimnasio->id) {
    case 1: 
        gimnasio->id_ptero_funcion = funcion_batalla_1;
        break;
    case 2:
        gimnasio->id_ptero_funcion = funcion_batalla_2;
        break;
    case 3:
        gimnasio->id_ptero_funcion = funcion_batalla_3;
        break;
    case 4:
        gimnasio->id_ptero_funcion = funcion_batalla_4;
        break;
    case 5:
        gimnasio->id_ptero_funcion = funcion_batalla_5;
        break;    
    default:
        return false;
        break;
    }

    return true;
}

void capturar_datos_gimnasio(gimnasio_t* gimnasio_agregado, gimnasio_t* gimnasio_datos){
    strcpy(gimnasio_agregado->nombre_gimnasio, gimnasio_datos->nombre_gimnasio);
    gimnasio_agregado->dificultad = gimnasio_datos->dificultad;
    gimnasio_agregado->id = gimnasio_datos->id;
}

bool cargar_gimnasio(FILE* archivo, heap_t* heap) {
    char primer_char; //de la siguiente linea a cargar
 
    gimnasio_t gimnasio_aux;
    
    int campos = fscanf(archivo, FORMATO_GIMNASIO,  &primer_char, gimnasio_aux.nombre_gimnasio,
                                                    &gimnasio_aux.dificultad, &gimnasio_aux.id);
    if (campos != CAMPOS_GIMNASIO) {
            printf("Formato de Gimnasio erroneo.");
            return false;
    }
    while(campos == CAMPOS_GIMNASIO && primer_char == INICIAL_GIMNASIO) {
        gimnasio_t* gimnasio_p = crear_gimnasio();
        if(!gimnasio_p) return false;
        capturar_datos_gimnasio(gimnasio_p, &gimnasio_aux);

        bool tiene_puntero_abatalla = verificar_batalla(gimnasio_p);
        cargar_entrenadores(archivo, &primer_char, gimnasio_p);

        if (gimnasio_p->pila_de_entrenadores->cantidad > VACIA && tiene_puntero_abatalla)
            heap_insertar(heap, gimnasio_p);
        else destructor_gimnasios(gimnasio_p);

        //mostrar_gimnasios(gimnasio_p);
        
        if (primer_char == INICIAL_GIMNASIO)
            campos = fscanf(archivo, FORMATO_GIMNASIO,  &primer_char, gimnasio_aux.nombre_gimnasio,
                                                        &gimnasio_aux.dificultad, &gimnasio_aux.id);
    }
    return true;
}



bool verificar_archivo(FILE* archivo, const char* nombre_archivo, char inicial_esperada) {
    if (!archivo) printf("ERROR de lectura del archivo \"%s\".\n", nombre_archivo);
    else {
    int primer_char = fgetc(archivo);

    if (primer_char == EOF) 
        printf("\nERROR. El archivo \"%s\" se encuentra vacio.\n", nombre_archivo); 

    else if (primer_char != inicial_esperada) {
        if (inicial_esperada == INICIAL_GIMNASIO)
            printf("El archivo \"%s\" no contiene un gimnasio.", nombre_archivo);
        else if(inicial_esperada == INICIAL_ENTRENADOR)
            printf("El archivo \"%s\" no contiene un personaje principal.", nombre_archivo);
        ungetc(primer_char, archivo);
    } else {
        ungetc(primer_char, archivo);
        return true; 
    }
    }

    return false;
}

bool leer_archivo_personaje(juego_t* juego) {
    char nombre_archivo[100], enter;
    printf("\nPor favor ingrese el nombre del archivo que contiene el personaje principal: \n");
    scanf("%s%c", nombre_archivo, &enter);
    FILE* archivo = fopen(nombre_archivo, LECTURA);

    if (verificar_archivo(archivo, nombre_archivo, INICIAL_ENTRENADOR)) {

        juego->personaje = cargar_personaje_principal(archivo);
        fclose(archivo);
        if (!juego->personaje) {
            printf("\nERROR, no se pudo obtener el personaje principal\n");
            return false;
        } else printf("\nSe pudo cargar el personaje con exito.\n");

        existe_personaje = true;
        return true;
    } 

    if (archivo) fclose(archivo);
    return false;
}


bool leer_archivo_gimnasio(juego_t* juego) {
    char nombre_archivo[100], enter;
    printf("\nPor favor ingrese el nombre del archivo que contiene el gimnasio: \n");
    scanf("%s%c", nombre_archivo, &enter);
    FILE* archivo = fopen(nombre_archivo, LECTURA);

    if (verificar_archivo(archivo, nombre_archivo, INICIAL_GIMNASIO)) {
        cargar_gimnasio(archivo, juego->heap_gimnasios);
        fclose(archivo);
        if (juego->heap_gimnasios->tope == VACIA) {
            printf("\nERROR, no se pudo obtener un gimnasio\n");
            return false;
        } else printf("\nSe pudo cargar el gimnasio con exito.\n");

        return true;
    } 

    if (archivo) fclose(archivo);
    return false;
}