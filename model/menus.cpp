#include <iostream>
#include <windows.h>
#include <conio.h> // es para el _getch
#include "../model/batalla.cpp"
#pragma comment(lib, "winmm.lib")

using namespace std;

// NOTE: Aqui deberian de ir TODOS los menús, es mejor para evitar redundancias de menús, si agregan algun menu, avisenme y lo pongo aquí

void menuCombate();

void pantallaBienvenida()
{
    PlaySound(TEXT("../model/assets/Title_Screen.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    system("cls");
    leerAscii("../model/assets/pokedevs.txt"); // chambón? si, pero funciona, si se cambia la ruta assets, tambien se tendra que cambiar esto
    _getch();
    system("cls");
}

// El menu principal despues de crear o continuar una partida
void principalMenu()
{

    int principalOption = 0;

    while (principalOption != 3)
    {
        system("cls");
        leerAscii("../model/assets/menuPrincipal.txt");

        // esto es una validacion por si el usuario mete algo que no sea 1,2 o 3
        do
        {
            cin >> principalOption;

            // Si la opción no es válida, limpia y cambia el menú al de error
            if (!(principalOption >= 1 && principalOption <= 3))
            {
                system("cls");
                leerAscii("../model/assets/menuPrincipalInvalido.txt");
            }
        } while (!(principalOption >= 1 && principalOption <= 3)); // Se repite si es inválido :D

        switch (principalOption)
        {
        case 1:
            system("cls");
            iniciarBatalla();
            // 4. Entramos al flujo de turnos
            menuCombate();
            break;
        case 2:
            system("cls");
            mostrarTablaClasificacion();
            cout << string(75, ' ') << "Presiona cualquier tecla para volver al menu principal..." << endl;
            leerAscii("../model/assets/marco3.txt");
            _getch();
            break;
        case 3:
            PlaySound(NULL, 0, 0);
            guardarSesionAlSalir();
            Sleep(3000);
            break;
        default:
            leerAscii("../model/assets/menuPrincipalInvalido.txt");
            cin >> principalOption;
            system("cls");
        }
    }
}

// menú de batalla despues de darle a jugar
void menuCombate()
{
    // Inicia música de batalla en bucle, de forma asíncrona para que no bloquee la ejecución del programa:
    PlaySound(TEXT("../model/assets/Battle_Theme.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    int fightOption = 0;

    // El ciclo se ejecuta mientras ambos lados sigan en condiciones de pelear y no se huya
    while (fightOption != 3 && aliadoVivo == true && enemigoVivo == true)
    {
        infoPokemon();

        // menú de pelea en si
        leerAscii("../model/assets/menuPelea.txt");
        cin >> fightOption;

        switch (fightOption)
        {
        case 1:
        {
            system("cls");
            infoPokemon();
            int indiceAtaque = seleccionarAtaque();

            if (indiceAtaque == -1)
            {
                system("cls");
                break; // El jugador decidió regresar al menú de combate anterior
            }
            ejecutarTurno(indiceAtaque);
            system("cls");
        }
        break;

        case 2:
        {
            system("cls");
            // Guardamos el índice del Pokémon antes de abrir el catálogo de cambios
            int pokemonPrevio = pokemonActivo;

            infoPokemon();
            cambiarPokemonBatalla();
            system("cls");

            // Si pokemonActivo cambió, significa que el usuario concretó un cambio válido
            // (No aplica si presionó '0' para arrepentirse y regresar)
            if (pokemonActivo != pokemonPrevio)
            {
                // Invocamos la nueva función del motor de batalla
                procesarContraataquePorCambio();
                system("cls");
            }
        }
        break;

        case 3:
            system("cls");
            infoPokemon();
            leerAscii("../model/assets/marco3.txt");
            system("cls");
            infoPokemon();
            break;

        default:
            system("cls");
            infoPokemon();
            leerAscii("../model/assets/menuPeleaInvalido.txt");
            Sleep(1000);
            system("cls");
            break;
        }
    }

    // Al romperse el bucle por derrota de algún bando, evaluamos el fin de juego
    if (fightOption != 3)
    {
        puntaje += puntosBatallaActual;
    }

    if (fightOption == 3)
    {
        leerAscii("../model/assets/marco3.txt");
        cout << string(35, ' ') << "Has huido de la batalla..." << endl;
        leerAscii("../model/assets/marco2.txt");
        cout << "\n" << string(40, ' ') << "Puntos ganados en esta batalla: " << puntosBatallaActual << " pts" << endl;
        cout << string(40, ' ') << "Puntos acumulados de la partida: " << puntaje << " pts\n" << endl;
        leerAscii("../model/assets/marco2.txt");
        cout << string(35, ' ') << "Presione cualquier tecla para continuar!" << endl;
        leerAscii("../model/assets/marcoArriba.txt");
        _getch();
    }
    else if (!aliadoVivo)
    {
        leerAscii("../model/assets/marco3.txt");
        cout << string(35, ' ') << "GAME OVER - Has sido derrotado" << endl;
        leerAscii("../model/assets/marco2.txt");
        cout << "\n" << string(40, ' ') << "Puntos ganados en esta batalla: " << puntosBatallaActual << " pts" << endl;
        cout << string(40, ' ') << "Puntos acumulados de la partida: " << puntaje << " pts\n" << endl;
        leerAscii("../model/assets/marco2.txt");
        cout << string(35, ' ') << "Presione cualquier tecla para continuar!" << endl;
        leerAscii("../model/assets/marcoArriba.txt");
        _getch();
    }
    else if (!enemigoVivo)
    {
        leerAscii("../model/assets/marco3.txt");
        cout << string(35, ' ') << "VICTORIA! Has ganado la batalla!" << endl;
        leerAscii("../model/assets/marco2.txt");
        cout << "\n" << string(40, ' ') << "Puntos ganados en esta batalla: " << puntosBatallaActual << " pts" << endl;
        cout << string(40, ' ') << "Puntos acumulados de la partida: " << puntaje << " pts\n" << endl;
        leerAscii("../model/assets/marco2.txt");
        cout << string(35, ' ') << "Presione cualquier tecla para continuar!" << endl;
        leerAscii("../model/assets/marcoArriba.txt");
        _getch();
    }

    guardarPartida();

    if (puntosBatallaActual > 0 && !tablaGuardadaEstaBatalla)
    {
        guardarPuntosEnClasificacion(puntosBatallaActual, nombreUsuario);
        tablaGuardadaEstaBatalla = true;
    }

    // Detener la música de batalla al salir del menú de pelea
    PlaySound(NULL, 0, 0);
}