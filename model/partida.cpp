#include <iostream>
#include <fstream>
#include <string>
#include <ctime> // Librería para recolectar la fecha

using namespace std;

// Variables globales de sesión (partidas)

string username = "";
int score = 0;
string ultimaFecha = "";
bool existePartida = false;

// Obtener fecha actual como string

string obtenerFechaHoy(){
    // Creando variable llamada ahora de tipo time_t para almacenar marcas de tiempo y los representa a través de números enteros
    time_t ahora = time(0); // Función de la librería ctime que obtiene el tiempo actual del sistema
    // Variable para almacenar el resultado en un puntero
    tm* ltm = localtime(&ahora); // Toma el número gigante de segundos y lo convierte a hora local de computadora
    // Declaramos el espacio de memoria para una cadena de texto con capacidad para 11 elementos
    char buf[11]; // Para almacenar la fecha formateada de forma visual (DD/MM/AAAA). Ocupa espacio 11 porque se reserva para el caracter nulo donde indicar donde termina el texto
    // Formato DD/MM/AAAA
    snprintf(buf, sizeof(buf), "%02d/%02d/%04d", // Obliga a definir cuanto espacio se tiene disponible y la plantilla que tiene que seguir (d es donde va el numero entero, que debe ocupar al menos 2 digitos y si tiene solo uno poner un cero a la izquierda, el 4 es por el año)
            ltm->tm_mday, // Llena el primer 02d con el día del mes
            ltm->tm_mon + 1, // Llena el segundo 02d con el mes (+ 1 porque en c++ solo cuenta desde 0 hasta 11, al sumarle 1 enero pasa a ser 01 y diciembre a 12)
            ltm->tm_year + 1900); // Llena el 04d con el año, se le suma 1900 porque se cuentan los años transcurridos desde 1900
    return string(buf); // Retorna la fecha en el formato string deseado
}

// Cargar y leer las partidas desde partida.txt
// Retornará true si el archivo existe

bool cargarPartida(){
    // Lee el archivo
    ifstream archivo("partida.txt");
    if(archivo.is_open()){
        // Lee la primer línea completa del archivo y la guarda en la variable username, se usa getline por si el nombre del usuario tiene espacios
        getline(archivo, username);
        // Lee el dato del archivo y lo guarda en score, deja el salto de línea atascado en el proceso de lectura
        archivo >> score;
        // Limpia el salto de línea que dejó la lectura de score, sino se leería una línea vacía y se guardaría en la siguiente variable
        archivo.ignore();
        // Lee la fecha y la guarda en la variable
        getline(archivo, ultimaFecha);
        archivo.close();
        existePartida = true;
        system("cls");
        cout << "Partida cargada correctamente" << endl;
        return true;
    }
    cout << "No hay partida guardada" << endl;
    return false;
}

// Guardar partida en partida.txt

void guardarPartida(){
    ofstream archivo("partida.txt");
    if(archivo.is_open()){
        archivo << username << "\n";
        archivo << score << "\n";
        archivo << obtenerFechaHoy() << "\n";
        archivo.close();
        existePartida = true;
        system("cls");
        cout << "Partida guardada correctamente" << endl;
    }else{
        cout << "No se pudo guardar la partida" << endl;
    }
}

// Iniciar sesión (cargar o crear una partida)

void iniciarSesion(){
    int loadingUserOption = 0;

    cout << "\nBienvenido a Poke Devs:\n";
    cout << "1. Continuar Partida\n";
    cout << "2. Crear una nueva partida\n";
    cout << "Seleccion una opcion: ";

    // Validamos que la opción sea 1 o 2, si no el bucle sigue
    while (!(loadingUserOption >= 1 && loadingUserOption <= 2)){
        cin >> loadingUserOption;
        // Le deja saber al usuario que su opción es inválida
        if(!(loadingUserOption >= 1 && loadingUserOption <= 2)){
            cout << "Opción invalida. Intenta de nuevo: ";
        }
    }

    if(loadingUserOption == 1){
        // Continuar partida
        if(!cargarPartida()){
            // El .txt no existe entonces no hay partida guardada
            cout << "Redirigiendo a creacion de nueva partida..." << endl;
            loadingUserOption = 2; // cae al bloque de nueva partida
        }
    }

    if(loadingUserOption == 2){
        // Nueva partida
        // Reiniciar variables
        score = 0;
        ultimaFecha = obtenerFechaHoy();

        cout << "Ingrese el nombre de usuario: ";
        // Limpia el salto de linea que queda al leer lo que el usuario escribió en la consola
        cin.ignore();
        getline(cin, username);

        // Guarda el .txt con los datos iniciales
        guardarPartida();
    }
}

// Guardar sesión al salir (opción 3 del menú)

void guardarSesionAlSalir(){
    char opcion;
    cout << "\nDeseas guardar la partida antes de salir? (s/n): ";
    cin >> opcion;
    
    if(opcion == 's' || opcion == 'S'){
        guardarPartida();
        cout << "Hasta luego, " << username << "!\n";
    }else{
        // Los datos guardados se quedan igual, solo despedimos
        cout << "Adios, " << username << ". Los datos no fueron actualizados.\n";
    }

    existePartida = true; // la partida sigue existiendo en disco
}