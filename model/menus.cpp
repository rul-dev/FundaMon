#include <iostream>
#include "../model/partida.cpp"

using namespace std;


//El menu principal despues de crear o continuar una partida
void menuPrincipal(){
    int principalOption = 0;

    while (principalOption != 3) //bucle while para validar la opcion
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
            // TODO: llamar funcion para jugar
            cout << "\n[Jugar - por implementar]\n";
            break;
        case 2:
            // TODO: llamar función de puntajes
            cout << "\n[Puntajes - por implementar]\n";
            break;
        case 3: 
            // Guardar sesión y salir
            guardarSesionAlSalir();
            break;
        default:
            cout << "\nOpción invalida. Intenta de nuevo\n" << endl;
            break;
        }
    }
}