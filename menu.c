#include <stdio.h>

#include "menu.h"


void menues(juego_t* juego, void (*funcion_impresion)(void), bool (*funcion_menu)(juego_t*)) {
    bool ingreso = false;
    int cantidad_errores = 0;

    funcion_impresion();

    while (!ingreso) {
        cantidad_errores ++;
        if (cantidad_errores > 3) {
            continuar();
            funcion_impresion();
            cantidad_errores = 0;
        }

        ingreso = funcion_menu(juego);
    }
    if (!fin_de_la_partida)
        continuar();
}

void finalizar_juego() {
    fin_de_la_partida = true;

    nos_calmamo();
}

bool verificar_ingreso_derrota(juego_t* juego) {
    char ingreso, enter;
    scanf("%c", &ingreso);
    scanf("%c", &enter); //para capturar el enter

    if (letras_son_iguales(ingreso, MODIFICAR_PARTY))
        cambiar_party(juego->personaje);

    else if (letras_son_iguales(ingreso, REINTENTAR))
        batallar(juego);

    else if (letras_son_iguales(ingreso, FINALIZAR_PARTIDA))
        finalizar_juego();

    else {
        letra_erronea();
        return false;
    }
    return true;
}

bool verificar_ingreso_victoria(juego_t* juego) {
    char ingreso, enter;
    scanf("%c", &ingreso);
    scanf("%c", &enter); //para capturar el enter

    if (!se_realizo_prestamo && letras_son_iguales(ingreso, TOMAR_PRESTADO)) 
        tomar_prestado_pokemon((gimnasio_t*)heap_raiz(juego->heap_gimnasios), juego->personaje);

     else if (letras_son_iguales(ingreso, MODIFICAR_PARTY))
        cambiar_party(juego->personaje);

    else if (letras_son_iguales(ingreso, PROXIMO_GIMNASIO))
        siguiente_gimnasio(juego);

    else {
        letra_erronea();
        return false;
    }
    return true;
}

bool verificar_ingreso_batalla(juego_t* juego) {
    char ingreso, enter;
    scanf("%c", &ingreso);
    scanf("%c", &enter); //para capturar el enter

    if (!letras_son_iguales(ingreso, PROXIMO_COMBATE)) {
        letra_erronea();
        return false;
    }
    return true;
}

bool verificar_ingreso_gimnasio(juego_t* juego) {
    char ingreso, enter;
    scanf("%c", &ingreso);
    scanf("%c", &enter); //para capturar el enter

    if (letras_son_iguales(ingreso, MOSTRAR_ENTRENADOR))
        mostrar_personaje(juego->personaje);

    else if (letras_son_iguales(ingreso, MOSTRAR_GIMNASIO))
        mostrar_gimnasios((gimnasio_t*)heap_raiz(juego->heap_gimnasios));

    else if (letras_son_iguales(ingreso, MODIFICAR_PARTY))
        cambiar_party(juego->personaje);

    else if (letras_son_iguales(ingreso, PROXIMA_BATALLA))
        comenzar = true;
    else {
        letra_erronea();
        return false;
    }
    return true;
}

bool verificar_ingreso_inicio(juego_t* juego) {
    char ingreso, enter;
    scanf("%c", &ingreso);
    scanf("%c", &enter); //para capturar el enter

    if (letras_son_iguales(ingreso, INGRESAR_ENTRENADOR))
        leer_archivo_personaje(juego);

    else if (letras_son_iguales(ingreso, AGREGAR_GIMNASIO))
        leer_archivo_gimnasio(juego);

    else if (letras_son_iguales(ingreso, INICIAR_PARTIDA))
        comenzar_partida(juego);

    else if (letras_son_iguales(ingreso, SIMULAR_PARTIDA))
        simular_partida(juego);

    else if (letras_son_iguales(ingreso, FINALIZAR_PARTIDA))
        finalizar_juego();

    else {
        letra_erronea();
        return false;
    }
    return true;
}