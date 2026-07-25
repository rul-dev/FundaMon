#include <windows.h>
#include <iostream>
#include "../model/menus.cpp"
// ojo con esto a quien sea que lo lea, las dependencias de cada archivo, es como si se "duplicara"
// el codigo, si pones ../model/menus.cpp aqui, y en otro archivo de otra funcion, te tirara un error de duplicados enorme
// basta con importar lo que necesites en el archivo de tu funcion y aqui importar EL ARCHIVO DE ESA FUNCION NUEVA, no dupliques imports

using namespace std;

// Re-definimos la estructura localmente para evitar que MinGW se queje
typedef struct _CONSOLE_FONT_INFOEX
{
    ULONG cbSize;
    DWORD nFont;
    COORD dwFontSize;
    UINT FontFamily;
    UINT FontWeight;
    WCHAR FaceName[LF_FACESIZE];
} CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;

// Definimos el tipo de función
typedef BOOL(WINAPI *SETCURRENTCONSOLEFONTEX)(HANDLE, BOOL, PCONSOLE_FONT_INFOEX);

void configurarPantalla()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // 1. Cambiar la fuente
    HMODULE hKernel = GetModuleHandleA("kernel32.dll");
    if (hKernel)
    {
        SETCURRENTCONSOLEFONTEX SetCurrentConsoleFontExFunc = 
            (SETCURRENTCONSOLEFONTEX)GetProcAddress(hKernel, "SetCurrentConsoleFontEx");

        if (SetCurrentConsoleFontExFunc)
        {
            CONSOLE_FONT_INFOEX cfi = { 0 };
            cfi.cbSize = sizeof(cfi);
            cfi.nFont = 0;
            cfi.dwFontSize.X = 5;   
            cfi.dwFontSize.Y = 8;  
            cfi.FontFamily = FF_DONTCARE;
            cfi.FontWeight = FW_NORMAL;
            lstrcpyW(cfi.FaceName, L"Consolas");

            SetCurrentConsoleFontExFunc(hOut, FALSE, &cfi);
        }
    }

    // 2. Ajustar dimensiones
    SHORT ancho = 170; 
    SHORT alto = 100;   

    SMALL_RECT minWindow = { 0, 0, 1, 1 };
    SetConsoleWindowInfo(hOut, TRUE, &minWindow);

    COORD bufferSize = { ancho, alto };
    SetConsoleScreenBufferSize(hOut, bufferSize);

    SMALL_RECT windowSize = { 0, 0, (SHORT)(ancho - 1), (SHORT)(alto - 1) };
    SetConsoleWindowInfo(hOut, TRUE, &windowSize);

    // 3. Forzar refresco del búfer y de la ventana de la consola
    HWND hwnd = GetConsoleWindow();
    if (hwnd)
    {
        InvalidateRect(hwnd, NULL, TRUE);
        UpdateWindow(hwnd);
    }
}

int main()
{
    configurarPantalla();
    pantallaBienvenida();
    iniciarSesion();
    principalMenu();
    return 0;
}