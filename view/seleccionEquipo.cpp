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
    // Este ciclo "for" recorre nuestra base de datos (arreglo) desde la posición 0 hasta la 29.
    for (int i = 0; i < 30; i++)
    {
        // Imprimimos el número de opción sumando 1 a la variable 'i' (para que el menú vaya del 1 al 30, no del 0 al 29).
        // Usamos "\t" (tabulación) para dar un espacio uniforme entre los nombres.
        cout << i + 1 << ". " << pokedexDisponible[i].nombre << "\t";
        
        // Un pequeño truco matemático: si el número de la lista es múltiplo de 3, damos un salto de línea.
        // Esto hace que la lista en la consola se imprima de forma ordenada en columnas de 3 en 3.
        if ((i + 1) % 3 == 0)
        {
            cout << endl;
        }
    }
}

//Pasamos el equipo actual que tengamos y el turno en el que van 
void MostrarProgresoEquipo(Equipo equipoTemporal , int turnoActual)
{
  cout << "\n--- Tu equipo actual ---" << endl;

//nuestro limite sera el turno actual que se paso
  for (int x = 0; x<= turnoActual; x++)
  {
 // se imprime el numero de lista y el nombre del pokemon n
   cout << x + 1 << ". " << equipoTemporal.pokemon[x].nombre << endl;
  }
  
cout << "------------------------\n" << endl;

}

void GuardarEquipoPokemon()
{
    // Mensaje de bienvenida indicando la regla del juego (6 max).
    cout << "Bienvenido es el turno de elegir tu equipo pokemon(solo puedes elegir 6 max)" << endl;
    
    // Llamamos a la función anterior para que el jugador vea el catálogo en pantalla.
    MostrarPokemones();
    
    // Creamos nuestra variable 'temp' del tipo Equipo. 
    // Este será nuestro "escritorio" o memoria temporal donde guardaremos las elecciones.
    Equipo temp;
    
    // CICLO PRINCIPAL: Controla los turnos del jugador. Dará exactamente 6 vueltas (de la 0 a la 5).
    for (int i = 0; i < 6; i++)
    {
        int seleccionUser; // Variable para atrapar el número que el jugador teclee en la consola.
        cout << "Elige tu pokemon segun su numero" << i + 1 << endl;
        cin >> seleccionUser; // Leemos la respuesta.

        // EL GUARDIA DE SEGURIDAD (Validación de rango)
        // Si el jugador escribe un número inválido (mayor a 30 o menor/igual a 0), lo atrapamos en este bucle.
        while (seleccionUser > 30 || seleccionUser <= 0)
        {
            cout << "Te has equivocado ingresa de nuevo el numero de pokemon a elegir" << endl;
            cout << "Elige tu pokemon segun su numero" << i + 1 << endl;
            cin >> seleccionUser; // Lo obligamos a escribir de nuevo hasta que ponga un número correcto.
        }
        
        // Traducimos el número que eligió el humano (1-30) al índice real del arreglo (0-29) restándole 1.
        int indiceReal = seleccionUser - 1;

        // EL DETECTOR DE CLONES (Validación de repetidos)
        // Creamos una "bandera" y la iniciamos apagada (false), asumiendo que el Pokémon no está repetido.
        bool pokeRep = false;

        // El ciclo "j" es nuestro inspector. Solo revisa los slots que ya llenamos (j != i) para evitar revisar espacios vacíos.
        for (int j = 0; j != i; j++)
        {
            // Comparamos si el nombre del Pokémon nuevo es exactamente igual a alguno que ya esté en el arreglo 'temp'.
            if (pokedexDisponible[indiceReal].nombre == temp.pokemon[j].nombre)
            {
                cout << "Pokemon repetido" << endl; // Advertencia en pantalla.
                pokeRep = true; // Levantamos la bandera para avisar que se detectó un clon.
            }
        }
        
        // EL VEREDICTO FINAL (Decisión de guardado)
        // Si el ciclo inspector terminó y la bandera sigue en 'false', el Pokémon es único y pasó la prueba.
        if (pokeRep == false)
        {
            // Lo guardamos oficialmente en la posición 'i' y mandamos mensaje de éxito.
            temp.pokemon[i] = pokedexDisponible[indiceReal];
            cout << "¡Has agregado a " << temp.pokemon[i].nombre << " a tu equipo!" << endl;
        }
        else
        {
            // Si la bandera sí se levantó (true), ejecutamos un "rebobinado".
            // Al restarle 1 a la variable 'i', obligamos al ciclo principal a repetir este mismo turno para no perder el espacio.
            i--;
        }
        
       //SE IMPRIME EL PROGRESO DEL EQUIPO
       //sE LLAMA LA FUNCION Y LE DAMOS LAS VARIABLES TEMPORALES

      MostrarProgresoEquipo(temp,i);
        
    } // Llave de cierre del ciclo principal
    
    // Mensaje final (fuera del ciclo principal para que se ejecute solo al terminar los 6 turnos)
    cout << "Felicidades Tu equipo esta completo" << endl;
}