#include <iostream>
#include <windows.h>
#include <conio.h> // ¡Importante para Windows!
#include "../model/partida.cpp"
#include "../model/batalla.cpp"

using namespace std;

// NOTE: Aqui deberian de ir TODOS los menús, es mejor para evitar redundancias de menús, si agregan algun menu, avisenme y lo pongo aquí

void fightMenu();

void pantallaBienvenida(){
    system("cls");
    leerAscii("model/assets/pokedevs.txt"); //chambón? si, pero funciona, si se cambia la ruta assets, tambien se tendra que cambiar esto
    _getch();
    system("cls");
}

// El menu principal despues de crear o continuar una partida
void principalMenu()
{

    int principalOption = 0;

    while (principalOption != 3)
    {
        cout << "\nMenu Principal:\n";
        cout << "1. Jugar\n";
        cout << "2. Puntajes\n";
        cout << "3. Salir\n";
        cout << "Selecciona una opcion: ";
        cin >> principalOption;
        system("cls");

        switch (principalOption)
        {
        case 1:
            iniciarBatalla();
            // 4. Entramos al flujo de turnos
            fightMenu();
            break;
        case 2:
            cout << "\n[Puntajes - por implementar]\n";
            break;
        case 3:
            guardarSesionAlSalir();
            break;
        default:
            cout << "\nOpción invalida. Intenta de nuevo\n"
                 << endl;
            break;
        }
    }
}

// menú de batalla despues de darle a jugar
void fightMenu()
{
    int fightOption = 0;

    // El ciclo se ejecuta mientras ambos lados sigan en condiciones de pelear y no se huya
    while (fightOption != 3 && aliadoVivo == true && enemigoVivo == true)
    {
        cout << "\n---------------------------------------------\n";
        cout << " TU POKEMON: " << equipoAliado.pokemon[activePokemon].nombre
             << " Nv.60 (HP: " << equipoAliado.pokemon[activePokemon].hp << ")\n";
        cout << " RIVAL:      " << equipoEnemigo.pokemon[activePokemonEnemy].nombre
             << " Nv.60 (HP: " << equipoEnemigo.pokemon[activePokemonEnemy].hp << ")\n";
        cout << "---------------------------------------------\n";

        cout << "1. Luchar\n";
        cout << "2. Cambiar\n";
        cout << "3. Huir\n";
        cout << "---------------------------------------------\n";
        cout << "Que quieres hacer?: ";
        cin >> fightOption;

        switch (fightOption)
        {
        case 1:
        {
            system("cls");
            int indiceAtaque = seleccionarAtaque();

            if (indiceAtaque == -1)
            {
                system("cls");
                break; // El jugador decidió regresar al menú de combate anterior
            }
            ejecutarTurno(indiceAtaque);
        }
        break;

        case 2:
        {
            system("cls");
            // Guardamos el índice del Pokémon antes de abrir el catálogo de cambios
            int pokemonPrevio = activePokemon;

            cambiarPokemonBatalla();
            system("cls");

            // Si activePokemon cambió, significa que el usuario concretó un cambio válido
            // (No aplica si presionó '0' para arrepentirse y regresar)
            if (activePokemon != pokemonPrevio)
            {
                // Invocamos la nueva función del motor de batalla
                procesarContraataquePorCambio();
            }
        }
        break;

        case 3:
            system("cls");
            cout << "\nHas huido de la batalla de forma segura!" << endl;
            Sleep(500);
            break;

        default:
            system("cls");
            cout << "\nElige alguna de las 3 opciones validas! " << endl;
            Sleep(500);
            break;
        }
    }

    // Al romperse el bucle por derrota de algún bando, evaluamos el fin de juego
    if (fightOption != 3)
    {
        score += puntosBatallaActual;
    }

    if (fightOption == 3)
    {
        cout << "\n=============================================\n";
        cout << "        Has huido de la batalla              " << endl;
        cout << "Puntos ganados en esta batalla: " << puntosBatallaActual << " pts" << endl;
        cout << "Puntos acumulados de la partida: " << score << " pts" << endl;
        cout << "=============================================\n";
    }
    else if (!aliadoVivo)
    {
        cout << "\n=============================================\n";
        cout << "      GAME OVER - Has sido derrotado         " << endl;
        cout << "Puntos ganados en esta batalla: " << puntosBatallaActual << " pts" << endl;
        cout << "Puntos acumulados de la partida: " << score << " pts" << endl;
        cout << "=============================================\n";
    }
    else if (!enemigoVivo)
    {
        cout << "\n=============================================\n";
        cout << "     VICTORIA! Has ganado la batalla!       \n" << endl;
        cout << "Puntos ganados en esta batalla: " << puntosBatallaActual << " pts" << endl;
        cout << "Puntos acumulados de la partida: " << score << " pts" << endl;
        cout << "=============================================\n";
    }

    guardarPartida();
}