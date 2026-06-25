#include <iostream>
#include <windows.h>
#include "../model/partida.cpp"
#include "../model/batalla.cpp"

using namespace std;

// NOTE: Aqui deberian de ir TODOS los menús, es mejor para evitar redundancias de menús, si agregan algun menu, avisenme y lo pongo aquí

void fightMenu();

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
    //PlaySound(TEXT("Battle_Theme.wav"), NULL, SND_FILENAME | SND_ASYNC);
    //Sleep(30000);
    int fightOption = 0;

    // WHILE GIGANTE DEL DIAGRAMA: Controla que nadie haya perdido y que no se haya huido
    while (fightOption != 3 && aliadoVivo == true && enemigoVivo == true)
    {
        // Bloques del diagrama: "Mostrar Pokémon del jugador" y "Mostrar Pokémon del enemigo"
        cout << "\n---------------------------------------------\n";
        cout << " TU POKEMON: " << equipoAliado.pokemon[activePokemon].nombre
             << " (HP: " << equipoAliado.pokemon[activePokemon].hp << ")\n";
        cout << " RIVAL:      " << equipoEnemigo.pokemon[activePokemonEnemy].nombre
             << " (HP: " << equipoEnemigo.pokemon[activePokemonEnemy].hp << ")\n";
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
            // TODO: Validar que se pueda regresar
            system("cls");
            // Llamamos a la función y guardamos qué ataque eligió
            int indiceAtaque = seleccionarAtaque();

            if (indiceAtaque == -1)
            { // Eligió regresar
                system("cls");
                break;
            }

            cout << "\n-> " << equipoAliado.pokemon[activePokemon].nombre
                 << " se prepara para usar "
                 << equipoAliado.pokemon[activePokemon].movimientos[indiceAtaque].nombre << "!\n";

            // TODO: Aquí irá el bloque gigante de tu diagrama donde se calcula la velocidad,
            // la efectividad y se resta la vida.
        }
        break;
        case 2:
        {
            // TODO: Validar que se pueda regresar
            // Llamamos a la función de cambio
            system("cls");
            cambiarPokemonBatalla();
            system("cls");

            // TODO: Como cambiaste de Pokémon, pierdes tu turno de atacar.
            // Aquí el enemigo te atacará directamente.
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

    // Al salir del bucle, verificamos si terminó por derrota o por huida
    if (!aliadoVivo)
    {
        cout << "\n=============================================\n";
        cout << "      GAME OVER - Has sido derrotado         \n";
        cout << "=============================================\n";
    }
    else if (!enemigoVivo)
    {
        cout << "\n=============================================\n";
        cout << "     VICTORIA! Has ganado la batalla!       \n";
        cout << "=============================================\n";
    }
}