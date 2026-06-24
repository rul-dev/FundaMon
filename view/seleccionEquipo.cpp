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
    MostrarPokemones();
    Equipo temp;
    for (int i = 0; i < 6; i++)
    {
        int seleccionUser;
        cout << "Elige tu pokemon segun su numero" << i + 1 << endl;
        cin >> seleccionUser;

        while (seleccionUser > 30 || seleccionUser <= 0)
        {
            cout << "Te has equivocado ingresa de nuevo el numero de pokemon a elegir" << endl;
            cout << "Elige tu pokemon segun su numero" << i + 1 << endl;
            cin >> seleccionUser;
        }
        int indiceReal = seleccionUser - 1;

        bool pokeRep = false;

        for (int j = 0; j != i; j++)
        {
            if (pokedexDisponible[indiceReal].nombre == temp.pokemon[j].nombre)
            {
                cout << "Pokemon repetido" << endl;
                pokeRep = true;
            }
        }
        if (pokeRep == false)
        {
            temp.pokemon[i] = pokedexDisponible[indiceReal];
            cout << "¡Has agregado a " << temp.pokemon[i].nombre << " a tu equipo!" << endl;
    }
    else{
        i--;
    }
        }

        
}