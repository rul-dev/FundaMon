/*
Comienzo para plantear las bases de la selleccion de equipo
*/
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "../model/pokedex.cpp"
using namespace std;

void MostrarPokemones()
{
    for (int i = 0; i < 30; i++)
    {
         cout << i + 1 << ". " << pokedexDisponible[i].nombre << "\t";
        if ((i + 1) % 3 == 0)
        {
            cout << endl;
        }
       
    }
}

// Lógica pura de selección, recibe el equipo a llenar
void GuardarEquipoPokemon(Equipo &miEquipo)
{
    MostrarPokemones();
    cout << "\n-------------------------------------------------------------------------\n";

    for (int i = 0; i < 6; i++)
    {
        int opcion;
        cout << "\nElige a tu Pokemon #" << (i + 1) << " (Ingresa el numero 1-30): ";
        cin >> opcion;

        while (opcion < 1 || opcion > 30)
        {
            cout << "Opcion invalida. Intenta de nuevo: ";
            cin >> opcion;
        }

        miEquipo.pokemon[i] = pokedexDisponible[opcion - 1];
        cout << "-> ¡" << miEquipo.pokemon[i].nombre << " se ha unido a tu equipo!" << endl;
    }

    system("cls");
    
    cout << "\n¡Equipo guardado con exito!\n";
}

