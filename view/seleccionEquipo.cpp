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

void GuardarEquipoPokemon()
{
    cout << "Bienvenido es el turno de elegir tu equipo pokemon(solo puedes elegir 6 max)" << endl;
}