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