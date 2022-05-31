#include <stdio.h>
#include <stdlib.h>

#include "imprenta.h"
#include "juego.h"

void clear_screen() {
    system("clear");
}

void pedir_ingreso() {
    printf("\nIngrese la letra de la opcion con la que desee continuar: ");
}

void letra_erronea() {
    printf("Error, la letra no se encuentra en las opciones.\n");
    pedir_ingreso();
}

void continuar() {
    char enter;
    printf("\nIngrese enter para continuar: ");
    scanf("%c", &enter);
    clear_screen();
}

void error_no_hay_archivo(const char* tipo_archivo) {
    printf("\nNo hay ningun %s cargado.", tipo_archivo);
    printf("\nLa simulacion se realizara con archivos predeterminados");

    continuar();
}


void imprimir_titulo_batalla(int id_funcion_batalla) {
    switch (id_funcion_batalla) {
    case 1:
        printf("\n1. Gana el mas veloz\n\n");
        break;
    case 2:
        printf("\n2. Gana el que mejor ataque y defienda\n\n");
        break;
    case 3:
        printf("\n3. Gana el que peor ataque y defienda\n\n");
        break;
    case 4:
        printf("\n4. Gana el que tenga nombre mas corto\n\n");
        break;
    case 5:
        printf("\n5. Que gane el mejor\n\n");
        break;        
    default:
        break;
    }
}

void imprimir_versus_pokemones(pokemon_t* poke_usuario, pokemon_t* poke_rival) {
    
    printf("\n\t\t\t\t\t _    _______\t\t\t ");
    printf("\nPokemon:\t\t%-12s\t| |  / / ___/\t\t%-12s ",poke_usuario->nombre_pokemon, poke_rival->nombre_pokemon);
    printf("\nVelocidad:\t\t  %-12d\t| | / /\\__ \\ \t\t  %-12d ",poke_usuario->velocidad, poke_rival->velocidad);
    printf("\nAtaque:\t\t\t  %-12d\t| |/ /___/ / \t\t  %-12d ",poke_usuario->ataque, poke_rival->ataque);
    printf("\nDefensa:\t\t  %-12d\t|___//____/  \t\t  %-12d ",poke_usuario->defensa, poke_rival->defensa);                

}


void imprimir_lista_pokemones(lista_t* lista_pokes) {
    size_t cantidad = lista_pokes->cantidad;

    printf("\n   %-10s %-12s %-12s %-12s\n\n", "Nombre", "Velocidad", "Ataque", "Defensa");

    for(size_t i = 0; i < cantidad; i++) {
        pokemon_t* poke = (pokemon_t*)lista_elemento_en_posicion(lista_pokes, i);
        printf(FORMATO_IMPRESION_POKE, i+1, poke->nombre_pokemon, poke->velocidad,
                                            poke->ataque, poke->defensa);
    }

}

void mostrar_entrenador(entrenador_t* entrenador) {

    imprimir_nombre_entrenador(entrenador);

    printf("\n\nPOKEMONES A COMBATIR: \n");
    imprimir_lista_pokemones(entrenador->lista_de_pokemones);
}

void imprimir_lista_entrenadores(lista_t* lista_entrenadores) {
    size_t cantidad = lista_entrenadores->cantidad;

    for(size_t i = 0; i < cantidad; i++) {
        entrenador_t* entrenador = (entrenador_t*)lista_elemento_en_posicion(lista_entrenadores, i);
        mostrar_entrenador(entrenador);
    }

}

void mostrar_personaje (personaje_t* personaje) {
    if (!personaje) {
        printf("\nAun no se ha ingresado un personaje principal\n"); //
        return;
    }
    clear_screen();

    printf("\nPERSONAJE PRINCIPAL: ");
    printf(" %s", personaje->entrenador->nombre_entrenador);

    printf("\n\nPOKEMONES A COMBATIR: \n");
    imprimir_lista_pokemones(personaje->entrenador->lista_de_pokemones);

    printf("\n\nPOKEMONES OBTENIDOS: \n");
    imprimir_lista_pokemones(personaje->pokemones_obtenidos);
}

void mostrar_gimnasios (gimnasio_t* gimnasio) {
    if (!gimnasio) {
        printf("\nAun no se ha ingresado un gimnasio\n"); //
        return;
    }
    clear_screen();

    printf("\n\nGIMNASIO: ");
    printf(" %s", gimnasio->nombre_gimnasio);

    printf("\n\nENTRENADORES:\n");
    imprimir_lista_entrenadores(gimnasio->pila_de_entrenadores);

}

void imprimir_menu_derrota() {
    clear_screen();
    imprimir_derrota();

    printf("C: Cambiar los Pokémon de batalla.\n");
    printf("R: Reintentar el gimnasio.\n");
    printf("F: Finalizar la partida.\n");

    pedir_ingreso();
}

void imprimir_menu_victoria() {
    clear_screen();
    imprimir_victoria();

    if (!se_realizo_prestamo)
        printf("T: Tomar un Pokémon del líder.\n");
    // Una vez realizada dicha operación, esta opción desaparece del menú.
    printf("C: Cambiar los Pokémon de batalla.\n");
    printf("N: Próximo gimnasio.\n");
    // Si no hay próximo gimnasio, se deberá notificar al usuario que se convirtió en Maestro Pokémon.
    
    pedir_ingreso();
}


void imprimir_menu_batalla() {

    printf("\n\nIngrese enter para el próximo combate.");
    continuar();
}

void imprimir_menu_gimnasio() {
    clear_screen();
    imprimir_titulo();

    printf("\n\n------------------- M E N U   G I M N A S I O -------------------\n\n");

    printf("E: Mostrar al entrenador principal junto a sus Pokémon.\n");
    printf("G: Mostrar información del gimnasio actual.\n");
    printf("C: Cambiar los Pokémon de batalla.\n");
    printf("B: Realizar la próxima batalla planificada.\n");

    pedir_ingreso();
}

void imprimir_inicio() {
    clear_screen();
    imprimir_titulo();

    printf("\n\n--------------------- M E N U   I N I C I O ---------------------\n\n");

    if (!existe_personaje)
        printf("E: Ingresar el archivo del entrenador principal.\n");
    printf("A: Agregar un gimnasio al árbol de gimnasios.\n");
    printf("I: Comienza la partida.\n");
    printf("S: Simula la partida.\n");
    printf("F: Finalizar juego.\n");

    pedir_ingreso();
}

void formato_linea_3(int cantidad){ //
	for (int i = 0; i < cantidad; i++){
		printf("%s", "-");
	}
}

void imprimir_poke_ganador(pokemon_t* pokemon) {

    printf("\n\n\t\t\t\t\t   _____________________________");
    printf("\n\t\t\t\t\t / \\                            \\.");
    printf("\n\t\t\t\t\t|   |       G A N A D O R        |.");
    printf("\n\t\t\t\t\t \\_ |                            |.");
    printf("\n\t\t\t\t\t    |   Epecie: %-12s     |.",pokemon->nombre_pokemon);
    printf("\n\t\t\t\t\t    |                            |.");
    printf("\n\t\t\t\t\t    |   Velocidad: %-12i  |.", pokemon->velocidad);
    printf("\n\t\t\t\t\t    |                            |.");
    printf("\n\t\t\t\t\t    |   Ataque: %-12i     |.", pokemon->ataque);
    printf("\n\t\t\t\t\t    |                            |.");
    printf("\n\t\t\t\t\t    |   Defensa: %-12i    |.", pokemon->defensa);
    printf("\n\t\t\t\t\t    |   _________________________|___");
    printf("\n\t\t\t\t\t    \\_/____________________________/.");
}

void imprimir_nombre_entrenador(entrenador_t* entrenador) {

    printf("\n");
    printf("\n __   ______________________________   __");
    printf("\n(__   ______________________________   __)");
    printf("\n   | |                              | |");
    printf("\n   | |\t%-20s        | |", entrenador->nombre_entrenador);
    printf("\n __| |______________________________| |__");
    printf("\n(__   ______________________________   __)");
    printf("\n ");

}

void imprimir_victoria() {
    clear_screen();

    printf("\n\n");
    printf("\n __| |____________________________________________| |__");
    printf("\n(__   ____________________________________________   __)");
    printf("\n   | |   __     ___      _                        | |");
    printf("\n   | |   \\ \\   / (_) ___| |_ ___  _ __(_) __ _    | |");
    printf("\n   | |    \\ \\ / /| |/ __| __/ _ \\|| '__| |/ _` |   | |");
    printf("\n   | |     \\ V / | | (__| || (_) | |  | | (_| |   | |");
    printf("\n   | |      \\_/  |_|\\___|\\__\\___/|_|  |_|\\__,_|   | |");
    printf("\n   | |                                            | |");
    printf("\n __| |____________________________________________| |__");
    printf("\n(__   ____________________________________________   __)");
    printf("\n   | |                                            | |");     
    printf("\n\n");

}

void imprimir_derrota() {
    clear_screen();

    printf("\n\n");
    printf("\n __| |____________________________________________| |__");
    printf("\n(__   ____________________________________________   __)");
    printf("\n   | |    ____                      _             | |");
    printf("\n   | |   |  _ \\  ___ _ __ _ __ ___ | |_ __ _      | |");
    printf("\n   | |   | | | |/ _ \\ '__| '__/ _ \\| __/ _` |     | |");
    printf("\n   | |   | |_| |  __/ |  | | | (_) |  | (_| |     | |");
    printf("\n   | |   |____/ \\___|_|  |_|  \\___/ \\__\\__,_|     | |");
    printf("\n   | |                                            | |");
    printf("\n __| |____________________________________________| |__");
    printf("\n(__   ____________________________________________   __)");
    printf("\n   | |                                            | |");  
    printf("\n\n");

}

void imprimir_titulo(){

    printf("\n                                  ,'\\");
    printf("\n    _.----.        ____         ,'  _\\   ___    ___     ____      ");
    printf("\n_,-'       `.     |    |  /`.   \\,-'    |   \\  /   |   |    \\  |`.");
    printf("\n\\      __    \\    '-.  | /   `.  ___    |    \\/    |   '-.   \\ |  |");
    printf("\n \\.    \\ \\   |  __  |  |/    ,','_  `.  |          | __  |    \\|  |");
    printf("\n   \\    \\/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |");
    printf("\n    \\     ,-'/  /   \\    ,'   | \\/ / ,`.|         /  /   \\  |     |");
    printf("\n     \\    \\ |   \\_/  |   `-.  \\    `'  /|  |    ||   \\_/  | |\\    |");
    printf("\n      \\    \\ \\      /       `-.`.___,-' |  |\\  /| \\      /  | |   |");
    printf("\n       \\    \\ `.__,'|  |`-._    `|      |__| \\/ |  `.__,'|  | |   |");
    printf("\n        \\_.-'       |__|    `-._ |              '-.|     '-.| |   |");
    printf("\n                                `'                            '-._|");
    printf("\n");
}

void nos_calmamo(){
    clear_screen();

    
    printf("\n\t\t\t\t\t               _,........__");
    printf("\n\t\t\t\t\t            ,-'            `-.");
    printf("\n\t\t\t\t\t          ,'                   `-.");
    printf("\n\t\t\t\t\t        ,'                        \\");
    printf("\n\t\t\t\t\t      ,'                           .");
    printf("\n\t\t\tME CALMO CHAU\t      .'\\               ,"".       `");
    printf("\n\t\t\t\t\t     ._.'|             / |  `       \\");
    printf("\n\t\t\t\t\t     |   |            `-.'  ||       `.");
    printf("\n\t\t\t\t\t     |   |            '-._,'||       | \\");
    printf("\n\t\t\t\t\t     .`.,'             `..,'.'       , |`-.");
    printf("\n\t\t\t\t\t     l                       .'`.  _/  |   `.");
    printf("\n\t\t\t\t\t     `-.._'-   ,          _ _'   -' \\  .     `");
    printf("\n\t\t\t\t\t`.''''''-.`-...,---------','         `. `....__.");
    printf("\n\t\t\t\t\t.'        `'-..___      __,\\          \\  \\     \\");
    printf("\n\t\t\t\t\t\\_ .          |   `''''    `.           . \\     \\");
    printf("\n\t\t\t\t\t  `.          |              `.          |  .     L");
    printf("\n\t\t\t\t\t    `.        |`--...________.'.        j   |     |");
    printf("\n\t\t\t\t\t      `._    .'      |          `.     .|   ,     |");
    printf("\n\t\t\t\t\t         `--,\\       .            `7""' |  ,      |");
    printf("\n\t\t\t\t\t            ` `      `            /     |  |      |    _,-''''`-.");
    printf("\n\t\t\t\t\t             \\ `.     .          /      |  '      |  ,'          `.");
    printf("\n\t\t\t\t\t              \\  v.__  .        '       .   \\    /| /              \\");
    printf("\n\t\t\t\t\t                 \\/    `''\''''''`.       \\   \\  /.''                |");
    printf("\n\t\t\t\t\t                 `        .        `._ ___,j.  `/ .-       ,---.     |");
    printf("\n\t\t\t\t\t                 ,`-.      \\         .'     `.  |/        j     `    |");
    printf("\n\t\t\t\t\t               /    `.      \\       /         \\ /         |     /    j");
    printf("\n\t\t\t\t\t               |       `-.   7-.._ .          |'          '         /");
    printf("\n\t\t\t\t\t               |          `./_    `|          |            .     _,'");
    printf("\n\t\t\t\t\t               `.           / `----|          |-............`---'");
    printf("\n\t\t\t\t\t                \\          \\      |          |");
    printf("\n\t\t\t\t\t               ,'           )     `.         |");
    printf("\n\t\t\t\t\t                7____,,..--'      /          |");
    printf("\n\t\t\t\t\t                                  `---.__,--.'");
    printf("\n");
}