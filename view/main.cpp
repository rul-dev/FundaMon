#include <iostream>
#include "../model/partida.cpp";

using namespace std;

int main()
{
    iniciarSesion();

    int principalOption = 0;

    while (principalOption != 3)
    {
        cout << "\nMenu Principal:\n";
        cout << "1. Jugar\n";
        cout << "2. Puntajes\n";
        cout << "3. Salir\n";
        cout << "Selecciona una opcion: ";
        cin >> principalOption;

        switch (principalOption)
        {
        case 1:
            // TODO: llamar función de juego desde pokedex.cpp
            cout << "[Jugar - por implementar]";
            break;
        case 2:
            // TODO: llamar función de puntajes
            cout << "[Jugar - por implementar]";
            break;
        case 3: 
            // Guardar sesión y salir
            guardarSesionAlSalir();
            break;
        default:
            cout << "Opción invalida. Intenta de nuevo" << endl;
            break;
        }
    }
    
    return 0;
}