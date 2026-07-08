#ifndef PARTIDA_CPP
#define PARTIDA_CPP

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cctype>
#include <ctime> // Librería para recolectar la fecha

using namespace std;

bool savedLeaderboardThisBattle = false;
// Variables globales de sesión (partidas)

string username = "";
int score = 0;
 int puntosBatallaActual = 0;
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
    return false;
}

//leera el archivo txt para las "interfaces"
void leerAscii(string nombreArchivo){ //va a esperar el nombre del archivo que le demos
    ifstream archivo(nombreArchivo); //abre el archivo que hayamos llamado
    string linea;
    if(archivo.is_open()){
        while(getline(archivo, linea)){
            cout << linea << endl; //imprime la linea que haya leido
        }
        archivo.close(); // Siempre cierra el archivo al terminar
    } else {
        cout << "Error: No se pudo cargar el arte ASCII de " << nombreArchivo << endl;
    }
      
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
        cout << "Partida guardada correctamente" << endl;
    }else{
        cout << "No se pudo guardar la partida" << endl;
    }
}

// Iniciar sesión (cargar o crear una partida)

void iniciarSesion(){
    int loadingUserOption = 0;
    leerAscii("../model/assets/inicioSesion.txt");
    // Validamos que la opción sea 1 o 2, si no el bucle sigue
    while (!(loadingUserOption >= 1 && loadingUserOption <= 2)){
        cin >> loadingUserOption;
        // Le deja saber al usuario que su opción es inválida
        if(!(loadingUserOption >= 1 && loadingUserOption <= 2)){
            system("cls");
            leerAscii("../model/assets/inicioSesionInvalido.txt");
        }
    }
    system("cls");

    if(loadingUserOption == 1){
        // Continuar partida
        if(!cargarPartida()){
            // El .txt no existe entonces no hay partida guardada
            leerAscii("../model/assets/crearGuardado2.txt");
            loadingUserOption = 2; // cae al bloque de nueva partida
        }
    }

    if(loadingUserOption == 2){
        // Nueva partida
        // Reiniciar variables
        score = 0;
        puntosBatallaActual = 0;
        ultimaFecha = obtenerFechaHoy();

        leerAscii("../model/assets/crearGuardado.txt");
        cout << string(90, ' '); //añade 90 espacios vacios, durisimo no?
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
    system("cls");
    leerAscii("../model/assets/menuPrincipalSalir.txt");
    cin >> opcion;
    system("cls");
    
    if(opcion == 's' || opcion == 'S'){
        leerAscii("../model/assets/marcoArriba.txt");
        cout <<string(85, ' ') <<"Hasta luego, " << username << "!\n\n";
        leerAscii("../model/assets/marcoArriba.txt");
        guardarPartida();
    }else{
        // Los datos guardados se quedan igual, solo despedimos
        leerAscii("../model/assets/marcoArriba.txt");
        cout <<string(70, ' ') << "Adios, " << username << ". Los datos no fueron actualizados.\n\n";
        leerAscii("../model/assets/marcoArriba.txt");
    }

    existePartida = true; // la partida sigue existiendo en disco
}


void mostrarPuntuaje(int score)
{
    cout << "Tu puntuaje es de: "<<score <<" pts"<< endl;
}

void guardarPuntosEnLeaderboard(int scoreActual, string nombreJugador)
{
    ofstream archivoEscritura("leaderboard.txt", ios::app);
    if (archivoEscritura.is_open())
    {
        
        archivoEscritura << nombreJugador << " " << scoreActual << "\n";
        archivoEscritura.close();
    }
    else
    {
        cout << "No se pudo guardar el puntaje en leaderboard.txt" << endl;
    }
}

void mostrarLeaderboard()
{    //se declara una estrcuturcon campos de nombre , puntuaje 
    struct Records { string nombre; int puntuaje; };
    //creo un array con 200 espacios y quemamos el puntuaje
    Records listaTop[200];
    int cantidad = 0;

    //abrimos leaderboard y declaramos la variable linea
    ifstream archivoLectura("leaderboard.txt");
    string linea;
    //se va a rrepetir hasta que se lean 200 validos y lineas que si sean disponilbes
    while (cantidad < 200 && getline(archivoLectura, linea))
    {

        //si la linea esta vacia pasa
        if (linea.empty()) continue;
        
        //encuentra el ultimo espacio d ela linea y
        // si no lo encuentra asume que no tiene el formato y continua a la otra linea 
        size_t pos = linea.find_last_of(' ');
        if (pos == string::npos) continue;
        // 0= toma lo ultimo de la linea antes del espacio como name
        string name = linea.substr(0, pos);
        // +1= toma lo ultimo de la linea antes del espacio como el puntuaja
        string scoreStr = linea.substr(pos + 1);
      
        //limpia espacios
        while (!name.empty() && isspace((unsigned char)name.back())) name.pop_back();
        while (!name.empty() && isspace((unsigned char)name.front())) name.erase(0,1);
       

        //comprueba que se pueda convertir el puntuaje a int y si no descarta la linea y coninua 
        //Si funciona sguarda el puntuaje en el arary listatop
        try {
            int s = stoi(scoreStr);
            if (s == 0) continue; // skip zeros
            listaTop[cantidad].nombre = name;
            listaTop[cantidad].puntuaje = s;
            cantidad++;
        } catch(...) { continue; }
    }
    archivoLectura.close();

    // este es un ordenamiento burubuja y detecta y compara 
    //revisa cada pasada y compara del mayor a menor y sigue haciendo eso hasta que se ordene 
    for (int i = 0; i < cantidad - 1; ++i)
    {
        for (int j = 0; j < cantidad - 1 - i; ++j)
        {
            if (listaTop[j+1].puntuaje > listaTop[j].puntuaje)
            {
                Records tmp = listaTop[j]; 
                listaTop[j] = listaTop[j+1];
                 listaTop[j+1] = tmp;
            }
        }
    }

    leerAscii("../model/assets/puntaje.txt");
    if (cantidad == 0) cout << "Aun no hay puntajes registrados.\n";
    else {
        int limite = cantidad < 10 ? cantidad : 10;
        cout <<"\n"<<string(77, ' ')<<"+------------- Top Puntajes --------------+\n";
        for (int i = 0; i < limite; ++i) 
        cout <<"\n"<<string(85, ' ')<<i+1 << ". " << listaTop[i].nombre << " - " << listaTop[i].puntuaje << " pts";
    }
    cout <<"\n\n"<<string(77, ' ') << "+-----------------------------------------+\n\n";
    leerAscii("../model/assets/marco3.txt");
}

#endif