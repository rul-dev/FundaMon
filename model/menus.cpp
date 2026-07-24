#include <iostream>
#include <windows.h> // es para el Sleep y para el PlaySound
#include <conio.h>   // es para el _getch
#include "../model/batalla.cpp"
#pragma comment(lib, "winmm.lib") // es para el PlaySound

using namespace std;

// NOTE: Aqui deberian de ir TODOS los menús, es mejor para evitar redundancias de menús, si agregan algun menu, avisenme y lo pongo aquí

void menuCombate();

void pantallaBienvenida()
{
    // Suena la musica de bienvenida en bucle, de forma asíncrona para que no bloquee la ejecución del programa:
    PlaySound(TEXT("../model/assets/Title_Screen.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    system("cls");
    leerAscii("../model/assets/pokedevs.txt"); // chambón? si, pero funciona, si se cambia la ruta assets, tambien se tendra que cambiar esto
    _getch();                                  // lee un carácter del teclado de forma inmediata y sin mostrarlo en pantalla
    system("cls");
}

// El menu principal despues de crear o continuar una partida
void principalMenu()
{
    // Inicializamos con la opción 0 para entrar al bucle
    int principalOption = 0;

    while (principalOption != 3)
    {
        system("cls");
        leerAscii("../model/assets/menuPrincipal.txt");

        // esto es una validacion por si el usuario mete algo que no sea 1,2 o 3
        do
        {
            cin >> principalOption;

            if(cin.fail()) cin.clear(), cin.ignore(1000, '\n'), principalOption = 0;

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
            // Entramos al flujo de turnos
            menuCombate();
            break;
        case 2:
            system("cls");
            mostrarTablaClasificacion();
            cout << string(75, ' ') << "Presiona cualquier tecla para volver al menu principal..." << endl;
            leerAscii("../model/assets/marco3.txt");
            _getch(); // lee un carácter del teclado de forma inmediata y sin mostrarlo en pantalla
            break;
        case 3:
            PlaySound(NULL, 0, 0); // Detenemos la música de fondo
            guardarSesionAlSalir();
            Sleep(3000); // Esperamos 3 segundos
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

        if(cin.fail()) cin.clear(), cin.ignore(1000, '\n'), fightOption = 0;

        switch (fightOption)
        {
        case 1:
        {
            system("cls");

            // Cargamos la información de los Pokémon y el menú de ataques
            infoPokemon();
            int indiceAtaque = seleccionarAtaque();

            if (indiceAtaque == -1)
            {
                system("cls");
                break; // El jugador decidió regresar al menú de combate anterior
            }

            // Ejecutamos el turno con el ataque elegido
            ejecutarTurno(indiceAtaque);
            system("cls");
        }
        break;

        case 2:
        {
            system("cls");
            // Guardamos el índice del Pokémon antes de abrir el catálogo de cambios
            int pokemonPrevio = pokemonActivo;

            // Cargamos la información de los Pokémon y el menú de cambio
            infoPokemon();

            // Invocamos la función de cambio de Pokémon
            cambiarPokemonBatalla();
            system("cls");

            // Si pokemonActivo cambió, significa que el usuario concretó un cambio válido
            // (No aplica si presionó '0' para arrepentirse y regresar)
            if (pokemonActivo != pokemonPrevio)
            {
                // Si el jugador cambió de Pokémon, el enemigo tiene la oportunidad de contraatacar
                procesarContraataquePorCambio();
                system("cls");
            }
        }
        break;

        case 3:
            // El jugador decidió huir, se rompe el bucle y se sale del menú de combate
            system("cls");

            // Mostramos la información de los Pokémon antes de salir
            infoPokemon();
            leerAscii("../model/assets/marco3.txt");
            system("cls");
            infoPokemon();
            break;

        default:
            system("cls");

            // Si el jugador ingresa una opción inválida, mostramos un mensaje de error y regresamos al menú
            infoPokemon();
            leerAscii("../model/assets/menuPeleaInvalido.txt");
            Sleep(1000); // Esperamos 1 segundo antes de regresar al menú
            system("cls");
            break;
        }
    }

    // Al romperse el bucle por derrota de algún bando, evaluamos el fin de juego
    if (fightOption != 3)
    {
        // Si el jugador gana o pierde, sumamos los puntos obtenidos en la batalla al puntaje total de la partida
        puntaje += puntosBatallaActual;
    }

    if (fightOption == 3)
    {
        leerAscii("../model/assets/marco3.txt");
        // string(35, ' ') agrega 35 espacios en blanco para centrar el mensaje
        cout << string(35, ' ') << "Has huido de la batalla..." << endl;
        leerAscii("../model/assets/marco2.txt");
        // string(40, ' ') agrega 40 espacios en blanco para centrar el mensaje
        cout << "\n"
             << string(40, ' ') << "Puntos ganados en esta batalla: " << puntosBatallaActual << " pts" << endl;
        cout << string(40, ' ') << "Puntos acumulados de la partida: " << puntaje << " pts\n"
             << endl;
        leerAscii("../model/assets/marco2.txt");
        cout << string(35, ' ') << "Presione cualquier tecla para continuar!" << endl;
        leerAscii("../model/assets/marcoArriba.txt");
        _getch(); // lee un carácter del teclado de forma inmediata y sin mostrarlo en pantalla
    }
    else if (!aliadoVivo)
    {
        leerAscii("../model/assets/marco3.txt");
        // string(35, ' ') agrega 35 espacios en blanco para centrar el mensaje
        cout << string(35, ' ') << "GAME OVER - Has sido derrotado" << endl;
        leerAscii("../model/assets/marco2.txt");
        // string(40, ' ') agrega 40 espacios en blanco para centrar el mensaje
        cout << "\n"
             << string(40, ' ') << "Puntos ganados en esta batalla: " << puntosBatallaActual << " pts" << endl;
        cout << string(40, ' ') << "Puntos acumulados de la partida: " << puntaje << " pts\n"
             << endl;
        leerAscii("../model/assets/marco2.txt");
        cout << string(35, ' ') << "Presione cualquier tecla para continuar!" << endl;
        leerAscii("../model/assets/marcoArriba.txt");
        _getch(); // lee un carácter del teclado de forma inmediata y sin mostrarlo en pantalla
    }
    else if (!enemigoVivo)
    {
        leerAscii("../model/assets/marco3.txt");
        // string(35, ' ') agrega 35 espacios en blanco para centrar el mensaje
        cout << string(35, ' ') << "VICTORIA! Has ganado la batalla!" << endl;
        leerAscii("../model/assets/marco2.txt");
        // string(40, ' ') agrega 40 espacios en blanco para centrar el mensaje
        cout << "\n"
             << string(40, ' ') << "Puntos ganados en esta batalla: " << puntosBatallaActual << " pts" << endl;
        cout << string(40, ' ') << "Puntos acumulados de la partida: " << puntaje << " pts\n"
             << endl;
        leerAscii("../model/assets/marco2.txt");
        cout << string(35, ' ') << "Presione cualquier tecla para continuar!" << endl;
        leerAscii("../model/assets/marcoArriba.txt");
        _getch(); // lee un carácter del teclado de forma inmediata y sin mostrarlo en pantalla
    }

    // Guardamos la partida al salir del menú de combate, sin importar si se ganó, perdió o huyó
    guardarPartida();

    if (puntosBatallaActual > 0 && !tablaGuardadaEstaBatalla)
    {
        // Guardamos los puntos obtenidos en la batalla en el archivo de clasificación
        guardarPuntosEnClasificacion(puntosBatallaActual, nombreUsuario);
        tablaGuardadaEstaBatalla = true;
    }

    // Detener la música de batalla al salir del menú de pelea
    PlaySound(NULL, 0, 0);
}