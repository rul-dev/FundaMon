#include <iostream>
#include "../model/partida.cpp"

using namespace std;

//NOTE: Aqui deberian de ir TODOS los menús, es mejor para evitar redundancias de menús, si agregan algun menu, avisenme y lo pongo aquí


//El menu principal despues de crear o continuar una partida
void principalMenu(){
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

//menú de batalla despues de darle a jugar
void fightMenu(){

    int fightOption = 0;

    while (fightOption != 3) //bucle while para validar la opcion
    {
        cout << "\n=============================================\n";
        cout << "1. Luchar\n";
        cout << "2. Cambiar\n";
        cout << "3. Huir\n";
        cout << "\n=============================================\n";
        cout << "¿Que quieres hacer?: ";
        cin >> fightOption;

        switch (fightOption)
        {
        case 1:
            // TODO: llamar funcion para luchar
            cout << "\n[Lucha - por implementar]\n";
            break;
        case 2:
            // TODO: llamar función para cambiar
            cout << "\n[Cambiar - por implementar]\n";
            break;
        case 3: 
            // TODO: llamar función para huir
            cout << "\n[Huir - por implementar]\n";
            break;
        default:
            cout << "\nElige alguna de las 3 opciones! " << endl;
            break;
        }
    }
}