#include <iostream>
#include "../model/menus.cpp" 
//ojo con esto a quien sea que lo lea, las dependencias de cada archivo, es como si se "duplicara"
//el codigo, si pones ../model/menus.cpp aqui, y en otro archivo de otra funcion, te tirara un error de duplicados enorme
//basta con importar lo que necesites en el archivo de tu funcion y aqui importar EL ARCHIVO DE ESA FUNCION NUEVA, no dupliques imports

using namespace std;

int main()
{
    iniciarSesion();
    principalMenu();
    return 0;
}