#include <iostream>
#include <windows.h>
#include "../view/seleccionEquipo.cpp"

using namespace std;

// Variables globales para la persistencia de los equipos en la sesión de juego
Equipo equipoAliado;
Equipo equipoEnemigo;

void prepararFaseSeleccion()
{
    // Aquí invocamos la lógica pura del reclutamiento pasándole nuestro struct global
    GuardarEquipoPokemon(equipoAliado);
}

void generarEquipoEnemigo()
{
    // Inicializamos la semilla del random usando el tiempo actual
    srand(time(0));

    for (int i = 0; i < 6; i++)
    {
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
int seleccionarAtaque()
{
    int opcionAtaque = 0;

    cout << "\n=============================================\n";
    cout << "  MOVIMIENTOS DE " << equipoAliado.pokemon[activePokemon].nombre << "\n";
    cout << "=============================================\n";

    for (int i = 0; i < 4; i++)
    {
        cout << i + 1 << ". " << equipoAliado.pokemon[activePokemon].movimientos[i].nombre
             << " (Tipo: " << equipoAliado.pokemon[activePokemon].movimientos[i].tipo
             << " | Danio: " << equipoAliado.pokemon[activePokemon].movimientos[i].danio << ")\n";
    }

    cout << "0. Regresar\n";
    cout << "---------------------------------------------\n";
    cout << "Elige un ataque (1-4) o 0 para regresar: ";
    cin >> opcionAtaque;

    while (opcionAtaque < 0 || opcionAtaque > 4)
    {
        cout << "Opcion invalida. Intenta de nuevo (0-4): ";
        cin >> opcionAtaque;
    }

    if (opcionAtaque == 0)
        return -1; // -1 indica que regresó

    return opcionAtaque - 1;
}

// Función para cambiar de Pokémon en medio de la batalla
void cambiarPokemonBatalla()
{
    int opcionElegida = 0;

    cout << "\nElige un pokemon:\n";
    cout << "---------------------------------------------\n";

    for (int f = 0; f < 6; f++)
    {
        if (equipoAliado.pokemon[f].hp > 0 && f != activePokemon)
        {
            cout << f + 1 << ". " << equipoAliado.pokemon[f].nombre
                 << " - HP: " << equipoAliado.pokemon[f].hp << "\n";
        }
        else if (f == activePokemon)
        {
            cout << f + 1 << ". " << equipoAliado.pokemon[f].nombre << " (EN COMBATE)\n";
        }
        else
        {
            cout << f + 1 << ". " << equipoAliado.pokemon[f].nombre << " (DEBILITADO)\n";
        }
    }

    cout << "0. Regresar\n";
    cout << "---------------------------------------------\n";
    cout << "Ingresa el numero del Pokemon o 0 para regresar: ";
    cin >> opcionElegida;

    if (opcionElegida == 0)
    {
        system("cls");
        return;
    }

    int index = opcionElegida - 1;

    while (index < 0 || index > 5 || equipoAliado.pokemon[index].hp <= 0 || index == activePokemon)
    {
        cout << "Opción inválida, intenta de nuevo (0 para regresar): ";
        cin >> opcionElegida;
        if (opcionElegida == 0)
            system("cls");
        return; // También puede regresar desde aquí
        index = opcionElegida - 1;
    }

    activePokemon = index;
    cout << "\n-> Regresa! Adelante, " << equipoAliado.pokemon[activePokemon].nombre << "!\n";
}

void iniciarBatalla()
{
    // Toda la narrativa de inicio de aventura ocurre aquí de forma exclusiva
    cout << "\n=============================================\n";
    cout << "            INICIANDO LA AVENTURA!            \n";
    cout << "=============================================\n";
    cout << "Bienvenido. Es el turno de elegir tu equipo pokemon (solo puedes elegir 6 max)\n";
    cout << "-------------------------------------------------------------------------\n";

    // 1. Armas tu equipo aliado
    prepararFaseSeleccion();

    // 2. Armas el equipo enemigo al azar (Asegúrate de haber puesto esta función en batalla.cpp)
    generarEquipoEnemigo();
    cout << "\n-> El rival ha preparado su equipo de forma aleatoria!\n";
    Sleep(500);
    cout << "\n-> El oponente te desafia! Preparate...\n";
    Sleep(500);
    // 3. ¡PASO CRÍTICO! Reiniciamos las variables de control de la arena
    // Esto asegura que ambos equipos empiecen sanos y con su primer Pokémon [0]
    activePokemon = 0;
    activePokemonEnemy = 0;
    aliadoVivo = true;
    enemigoVivo = true;
}