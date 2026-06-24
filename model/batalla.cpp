#include <iostream>
#include "../view/seleccionEquipo.cpp"

using namespace std;

// Variables globales para la persistencia de los equipos en la sesión de juego
Equipo equipoAliado;
Equipo equipoEnemigo;

void prepararFaseSeleccion() {
    // Aquí invocamos la lógica pura del reclutamiento pasándole nuestro struct global
    GuardarEquipoPokemon(equipoAliado);
}

void generarEquipoEnemigo() {
    // Inicializamos la semilla del random usando el tiempo actual
    srand(time(0)); 

    for (int i = 0; i < 6; i++) {
        // Genera un número aleatorio entre 0 y 29
        int indiceAleatorio = rand() % 30; 
        
        // Copiamos el Pokémon aleatorio de la Pokédex al equipo enemigo
        equipoEnemigo.pokemon[i] = pokedexDisponible[indiceAleatorio];
    }
}

// Índices para saber quién está peleando en la arena (empiezan con el primero [0])
int activePokemon = 0;
int activePokemonEnemy = 0;

// Banderas de control de juego
bool aliadoVivo = true;
bool enemigoVivo = true;

// Función para mostrar los 4 ataques y validar la opción
// Retorna el índice (0 al 3) del movimiento elegido
int seleccionarAtaque() {
    int opcionAtaque = 0;
    
    cout << "\n=============================================\n";
    cout << "  MOVIMIENTOS DE " << equipoAliado.pokemon[activePokemon].nombre << "\n";
    cout << "=============================================\n";
    
    // Ciclo FOR del diagrama para mostrar ataques
    for(int i = 0; i < 4; i++) {
        cout << i + 1 << ". " << equipoAliado.pokemon[activePokemon].movimientos[i].nombre 
             << " (Tipo: " << equipoAliado.pokemon[activePokemon].movimientos[i].tipo 
             << " | Danio: " << equipoAliado.pokemon[activePokemon].movimientos[i].danio << ")\n";
    }
    
    cout << "---------------------------------------------\n";
    cout << "Elige un ataque (1-4): ";
    cin >> opcionAtaque;

    // Validación: Si elige algo fuera de 1 y 4, se repite
    while(opcionAtaque < 1 || opcionAtaque > 4) {
        cout << "Opcion invalida. Intenta de nuevo (1-4): ";
        cin >> opcionAtaque;
    }

    // Retornamos el índice real del arreglo (0 a 3)
    return opcionAtaque - 1; 
}

// Función para cambiar de Pokémon en medio de la batalla
void cambiarPokemonBatalla() {
    int opcionElegida = 0;
    
    cout << "\nElige un pokemon:\n";
    cout << "---------------------------------------------\n";
    
    // Ciclo FOR del diagrama (f < 6)
    for(int f = 0; f < 6; f++) {
        // Rombo Azul: Verifica que tenga vida y que NO sea el que ya está peleando
        if(equipoAliado.pokemon[f].hp > 0 && f != activePokemon) {
            cout << f + 1 << ". " << equipoAliado.pokemon[f].nombre 
                 << " - HP: " << equipoAliado.pokemon[f].hp << "\n";
        }
        else if (f == activePokemon) {
            cout << f + 1 << ". " << equipoAliado.pokemon[f].nombre << " (EN COMBATE)\n";
        }
        else {
            cout << f + 1 << ". " << equipoAliado.pokemon[f].nombre << " (DEBILITADO)\n";
        }
    }
    
    cout << "---------------------------------------------\n";
    cout << "Ingresa el numero del Pokemon: ";
    cin >> opcionElegida;
    
    // Convertimos la entrada al índice del arreglo
    int index = opcionElegida - 1;

    // Rombo Verde de validación (WHILE gigante)
    while(index < 0 || index > 5 || equipoAliado.pokemon[index].hp <= 0 || index == activePokemon) {
        cout << "Opción inválida, intenta de nuevo: ";
        cin >> opcionElegida;
        index = opcionElegida - 1;
    }

    // Asignamos el nuevo Pokémon activo
    activePokemon = index;
    cout << "\n-> ¡Regresa! ¡Adelante, " << equipoAliado.pokemon[activePokemon].nombre << "!\n";
}

void iniciarBatalla() {
    // 1. Fase de Selección del Jugador
    prepararFaseSeleccion();

    // 2. Fase de Selección del Enemigo (Llamamos a la nueva función)
    generarEquipoEnemigo();
    cout << "\n-> ¡El rival ha preparado su equipo de forma aleatoria!" << endl;

    // 3. Inicializar el estado de la batalla antes de entrar al bucle
    activePokemon = 0;
    activePokemonEnemy = 0;
    aliadoVivo = true;
    enemigoVivo = true;

    cout << "\n=============================================\n";
    cout << "         ¡COMIENZA EL COMBATE POKÉMON!        \n";
    cout << "=============================================\n";
}