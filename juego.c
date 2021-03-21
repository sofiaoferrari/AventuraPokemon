#include <stdio.h>

#include "juego.h"
#include "lectura_archivos.h"
#include "imprenta.h"
#include "menu.h"

void juego_destruir(juego_t* juego) {
    if (!juego) return;

    heap_destruir(juego->heap_gimnasios);
    destructor_personaje(juego->personaje);

    free(juego);
}

juego_t* crear_juego() {
    juego_t* juego = (juego_t*)calloc(1, sizeof(juego_t));
    if(!juego) return NULL;

    juego->heap_gimnasios = heap_crear(&comparador, &destructor_gimnasios);//

    return juego;
}

bool cargar_datos(juego_t* juego) {
    if(juego->heap_gimnasios->tope == VACIA) {
        error_no_hay_archivo("gimnasio");
        FILE* archivo_de_gimnasio = fopen(ARCHIVO_GIMNASIO, LECTURA);
        cargar_gimnasio(archivo_de_gimnasio, juego->heap_gimnasios);
        if (archivo_de_gimnasio) fclose(archivo_de_gimnasio);
    }
    if (!juego->personaje) {
        error_no_hay_archivo("personaje");
        FILE* archivo_de_personaje = fopen(ARCHIVO_PERSONAJE, LECTURA);
        juego->personaje = cargar_personaje_principal(archivo_de_personaje);
        if (archivo_de_personaje) fclose(archivo_de_personaje);
        if (!juego->personaje) return false;
    }
    return true;
}

bool verificar_poke_repetido(lista_t* lista_batalla, pokemon_t* poke_agregar) {
    for (size_t i = 0; i < lista_batalla->cantidad; i++) {
        pokemon_t* pokemon = (pokemon_t*)lista_elemento_en_posicion(lista_batalla, i);
        if (poke_agregar == pokemon) {
        printf("\nError, no se puede ingresar 2 veces el mismo pokemon.");
        return true;
        }
    }
    return false;
}

void intercambiar_pokemones(lista_t* lista_batalla, lista_t* lista_obtenidos, size_t i, size_t j) {
    pokemon_t* poke_eliminar = (pokemon_t*)lista_elemento_en_posicion(lista_batalla, i);
    pokemon_t* poke_agregar = (pokemon_t*)lista_elemento_en_posicion(lista_obtenidos, j);
    
    if(verificar_poke_repetido(lista_batalla, poke_agregar)) return;

    lista_borrar_de_posicion(lista_batalla, i);
    lista_insertar_en_posicion(lista_batalla, poke_agregar, i);
  
}
/*
void intercambiar_pokemones(lista_t* lista_batalla, lista_t* lista_obtenidos, size_t i, size_t j) {
    pokemon_t* poke_eliminar = crear_pokemon();
    capturar_datos_pokes(poke_eliminar, (pokemon_t*)lista_elemento_en_posicion(lista_batalla, i));
    pokemon_t* poke_agregar = crear_pokemon();
    capturar_datos_pokes(poke_agregar, (pokemon_t*)lista_elemento_en_posicion(lista_obtenidos, j));

    lista_insertar(lista_batalla, poke_agregar);
    lista_insertar(lista_obtenidos, poke_eliminar);//

    destructor_pokemones(poke_eliminar);
    lista_borrar_de_posicion(lista_batalla, i);
    destructor_pokemones(poke_agregar);
    lista_borrar_de_posicion(lista_obtenidos, j);
}*/

size_t consultar_intercambio(size_t cantidad_pokes) {
    size_t ingreso; 
    char enter;
    scanf("%lu%c", &ingreso, &enter);
   
    while(ingreso <= 0 || ingreso > cantidad_pokes) {
        printf("\nError, numero fuera de rango. Cuentas con %lu pokemones.\nVolver a ingresar: ", cantidad_pokes);
        scanf("%lu%c", &ingreso, &enter);
    }
    return ingreso;
}

void tomar_prestado_pokemon(gimnasio_t* gimnasio, personaje_t* personaje) {

    if (gimnasio->pila_de_entrenadores->cantidad == 1) { //entrenador restante es el Lider
        entrenador_t* lider = (entrenador_t*)lista_tope(gimnasio->pila_de_entrenadores);
        mostrar_entrenador(lider);

        printf("\n\nIngresa el numero del pokemon que deseas tomar prestado del Lider: ");
        size_t posicion_elegido = consultar_intercambio(lider->lista_de_pokemones->cantidad) -1;

        pokemon_t* poke_elegido = crear_pokemon();
        capturar_datos_pokes(poke_elegido, (pokemon_t*)lista_elemento_en_posicion(lider->lista_de_pokemones, posicion_elegido));
        
        lista_insertar(personaje->pokemones_obtenidos, poke_elegido);
    }

}

void cambiar_party(personaje_t* personaje) {
    mostrar_personaje(personaje);

    if (personaje->pokemones_obtenidos->cantidad == VACIA) {
        printf("\n No tienes pokemones obtenidos.\n");
        return;
    }
    
    printf("\n\nIngresa el numero del pokemon que deseas sacar de las batallas: ");
    size_t posicion_eliminar = consultar_intercambio(personaje->entrenador->lista_de_pokemones->cantidad);

    printf("\n\nIngresa el numero del pokemon que deseas agregar a las batallas: ");
    size_t posicion_agregar = consultar_intercambio(personaje->pokemones_obtenidos->cantidad);

    intercambiar_pokemones(personaje->entrenador->lista_de_pokemones, personaje->pokemones_obtenidos,
                                posicion_eliminar -1, posicion_agregar -1);
}

int combatir_pokemon(juego_t* juego, pokemon_t* poke_usuario, pokemon_t* poke_rival, gimnasio_t* gimnasio) {
    imprimir_titulo_batalla(gimnasio->id);
    int resultado = gimnasio->id_ptero_funcion(poke_usuario, poke_rival);
   
    imprimir_versus_pokemones(poke_usuario, poke_rival);
    if (resultado == GANO) 
        imprimir_poke_ganador(poke_usuario);
       
    else imprimir_poke_ganador(poke_rival);

    return resultado;
}


bool combatir_entrenador(juego_t* juego, entrenador_t* entrenador, gimnasio_t* gimnasio) {
    size_t cantidad_pokes_rival = entrenador->lista_de_pokemones->cantidad;
    size_t cantidad_pokes_usuario = juego->personaje->entrenador->lista_de_pokemones->cantidad;
    size_t  i = 0, //posicion poke personaje
            j = 0; //posicion poke rival

    while (j < cantidad_pokes_rival && i < cantidad_pokes_usuario) {
    
        pokemon_t* poke_usuario = (pokemon_t*)lista_elemento_en_posicion(juego->personaje->entrenador->lista_de_pokemones, i);
        pokemon_t* poke_rival = (pokemon_t*)lista_elemento_en_posicion(entrenador->lista_de_pokemones, j);
        int resultado = combatir_pokemon(juego, poke_usuario, poke_rival, gimnasio);

        if (resultado == GANO) j++; //gano el poke del personaje
        else if (resultado == PERDIO) i++;

      //  menues(juego, imprimir_menu_batalla, verificar_ingreso_batalla);
        imprimir_menu_batalla();
    }
    if (j == cantidad_pokes_rival) return true;

    return false;
}

bool combatir_gimnasio(juego_t* juego, gimnasio_t* gimnasio) {

    printf("\nGIMNASIO: %s\n", gimnasio->nombre_gimnasio); //ver

    while (gimnasio->pila_de_entrenadores->cantidad > VACIA){
        entrenador_t* entrenador = (entrenador_t*)lista_tope(gimnasio->pila_de_entrenadores);
        if (!combatir_entrenador(juego, entrenador, gimnasio)) 
            return false;
        if (gimnasio->pila_de_entrenadores->cantidad != 1) { //si no queda solo el lider
            destructor_entrenadores(entrenador);
            lista_desapilar(gimnasio->pila_de_entrenadores);
        }
    }
    if (gimnasio->pila_de_entrenadores->cantidad == VACIA +1) return true; //queda el lider pero se lo derroto

    return false;
}

/**/
void batallar(juego_t* juego) {
    if (!juego || !juego->heap_gimnasios || juego->heap_gimnasios->tope == VACIA) 
        return; //imprimir error

    se_realizo_prestamo = false;
    bool victoria = combatir_gimnasio(juego, (gimnasio_t*)heap_raiz(juego->heap_gimnasios));
    if (victoria) {
        juego->personaje->medallas++;
        menues(juego, imprimir_menu_victoria, verificar_ingreso_victoria);
    } else menues(juego, imprimir_menu_derrota, verificar_ingreso_derrota);
}

void siguiente_gimnasio(juego_t* juego) {
    heap_extraer_raiz(juego->heap_gimnasios);

    if (juego->heap_gimnasios->tope == VACIA)
        printf("No hay mas gimnasios, sos Maestro Pokemon"); // crear funcion (mostrar party y medallas(?))
    else batallar(juego);
}

void comenzar_partida(juego_t* juego) {
        printf("\nENTRO ACAaaa.\n");

    if (!juego || juego->heap_gimnasios->tope == VACIA || !juego->personaje) {
        printf("\nAun no se han ingresado los archivos.\n");
        return;
    }
    while(!comenzar) {
        printf("\nENTRO ACA.\n");

        menues(juego, imprimir_menu_gimnasio, verificar_ingreso_gimnasio);
    }
    batallar(juego);

}

void simular_partida(juego_t* juego) {
    cargar_datos(juego);
    
}

int main() {
    fin_de_la_partida = false;
    existe_personaje = false;
    comenzar = false;

    juego_t* juego = crear_juego(); //crea heap y personaje

    while (!fin_de_la_partida) {

        menues(juego, imprimir_inicio, verificar_ingreso_inicio);  
        
    }
    
    juego_destruir(juego);

    return EXITO;
}