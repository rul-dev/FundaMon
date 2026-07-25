#include <iostream>
#include <windows.h> // es para el Sleep
#include "../model/partida.cpp"
#include "../model/seleccionEquipo.cpp"

using namespace std;

// Variables globales para la persistencia de los equipos en la sesión de juego
Equipo equipoAliado;
Equipo equipoEnemigo;

void prepararFaseSeleccion()
{
    // Aquí invocamos la lógica pura del reclutamiento pasándole nuestro struct global
    guardarEquipoPokemon(equipoAliado);
}

void generarEquipoEnemigo()
{
    // Inicializamos la semilla del random usando el tiempo actual
    srand(time(0));

    for (int i = 0; i < 6; i++)
    {
        // Genera un número aleatorio entre 0 y 29
        int indiceAleatorio = rand() % 30;

        // Copiamos el Pokémon aleatorio de la Pokédex al equipo enemigo
        equipoEnemigo.pokemon[i] = pokedexDisponible[indiceAleatorio];
    }
}

// Índices para saber quién está peleando en la arena (empiezan con el primero [0])
int pokemonActivo = 0;
int pokemonEnemigoActivo = 0;

// Banderas de control de juego
bool aliadoVivo = true;
bool enemigoVivo = true;

// 1. Obtiene la vida maxima original buscando al pokemon en la pokedex base
int obtenerHpMaximo(string nombrePokemon)
{
    for (int i = 0; i < 30; i++)
    {
        if (pokedexDisponible[i].nombre == nombrePokemon)
        {
            // Replicamos la misma fórmula que usaste al iniciarBatalla
            return (pokedexDisponible[i].hp * 2.5) + 60;
        }
    }
    return 100; // Valor de seguridad
}

// 2. Genera un string visual de barra de progreso [####----]
string crearBarraVida(int hpActual, int hpMax)
{
    int longitudBarra = 20; // La barra tendrá 20 "cuadritos" de largo
    if (hpActual < 0)
        hpActual = 0;

    // Regla de 3 simple para saber cuántos cuadros pintar
    int bloquesLlenos = (hpActual * longitudBarra) / hpMax;

    string barra = "[";
    for (int i = 0; i < longitudBarra; i++)
    {
        if (i < bloquesLlenos)
            barra += "#"; // Vida que le queda
        else
            barra += "-"; // Vida perdida
    }
    barra += "]";
    return barra;
}

void imprimirSprite(const string& sprite, int margen)
{
    string espacios(margen, ' ');
    cout << espacios;
    for (char c : sprite)
    {
        if (c == '\r') continue;          // por si el archivo tiene CRLF
        if (c == '\n')
            cout << "\n" << espacios;
        else
            cout << c;
    }
    cout << "\n";
}

void infoPokemon()
{
    // Calculamos la vida máxima real de los que están peleando en este momento
    int hpMaxEnemigo = obtenerHpMaximo(equipoEnemigo.pokemon[pokemonEnemigoActivo].nombre);
    int hpMaxAliado = obtenerHpMaximo(equipoAliado.pokemon[pokemonActivo].nombre);

    leerAscii("../model/assets/marcoArriba.txt");

    // ==================== ZONA DEL RIVAL ====================
    cout << string(110, ' ') << "* RIVAL: " << equipoEnemigo.pokemon[pokemonEnemigoActivo].nombre << " - Nv.60\n";

    // Imprimimos la vida junto con la nueva barra de progreso
    cout << string(110, ' ') << "  HP: " << equipoEnemigo.pokemon[pokemonEnemigoActivo].hp << "/" << hpMaxEnemigo
         << " " << crearBarraVida(equipoEnemigo.pokemon[pokemonEnemigoActivo].hp, hpMaxEnemigo) << "\n\n";

    // Imprimimos el sprite del enemigo (Le damos margen de 90 para que se vea a la derecha)
    imprimirSprite(equipoEnemigo.pokemon[pokemonEnemigoActivo].spriteAscii, 90);

    leerAscii("../model/assets/marco2.txt");
    leerAscii("../model/assets/marco2.txt");

    // ==================== ZONA DE TU POKEMON ====================

    // Imprimimos tu sprite (Le damos margen de 30, igual que a tus textos)
    imprimirSprite(equipoAliado.pokemon[pokemonActivo].spriteAscii, 30);

    cout << "\n"
         << string(30, ' ') << "* TU POKEMON: " << equipoAliado.pokemon[pokemonActivo].nombre << " - Nv.60\n";

    // Imprimimos la vida junto con la nueva barra de progreso
    cout << string(30, ' ') << "  HP: " << equipoAliado.pokemon[pokemonActivo].hp << "/" << hpMaxAliado
         << " " << crearBarraVida(equipoAliado.pokemon[pokemonActivo].hp, hpMaxAliado) << "\n\n";
}

// Función para mostrar los 4 ataques y validar la opción
void menuMovimientos()
{
    leerAscii("../model/assets/marco3.txt");

    // string(30, ' ') agrega 30 espacios en blanco para centrar el mensaje
    cout << string(30, ' ') << "  Movimientos de " << equipoAliado.pokemon[pokemonActivo].nombre << "\n";
    leerAscii("../model/assets/marco2.txt");
    cout << "\n";

    for (int i = 0; i < 4; i++)
    {
        // Este for recorre los 4 movimientos del Pokémon activo y los imprime en pantalla
        cout << string(30, ' ') << i + 1 << ". " << equipoAliado.pokemon[pokemonActivo].movimientos[i].nombre
             << " (Tipo: " << equipoAliado.pokemon[pokemonActivo].movimientos[i].tipo
             << " | Danio: " << equipoAliado.pokemon[pokemonActivo].movimientos[i].danio << ")\n";
    }

    cout << string(30, ' ') << "0. Regresar\n\n";
}

// Retorna el índice (0 al 3) del movimiento elegido
int seleccionarAtaque()
{

    int opcionAtaque = 0;
    menuMovimientos(); // Muestra los movimientos del Pokémon activo y elige uno
    leerAscii("../model/assets/marco2.txt");
    cout << string(30, ' ') << "Elige un ataque (1-4 y presione enter) o 0 para regresar\n";
    leerAscii("../model/assets/marcoArriba.txt");
    cin >> opcionAtaque;

    // Validación de rango: Si el jugador escribe un número inválido (mayor a 4 o menor a 0), lo atrapamos en este bucle.
    while (opcionAtaque < 0 || opcionAtaque > 4)
    {
        system("cls");

        // Mostramos la información de los Pokémon y el menú de movimientos nuevamente
        infoPokemon();
        menuMovimientos();
        leerAscii("../model/assets/marco2.txt");
        cout << string(30, ' ') << "Opcion invalida. Intenta de nuevo (0-4)\n";
        leerAscii("../model/assets/marcoArriba.txt");
        cin >> opcionAtaque;
    }

    // Si el jugador elige 0, regresamos al menú de batalla sin ejecutar un ataque
    if (opcionAtaque == 0)
        return -1; // -1 indica que regresó

    return opcionAtaque - 1;
}

void verPokemones()
{

    leerAscii("../model/assets/marco3.txt");

    // string(30, ' ') agrega 30 espacios en blanco para centrar el mensaje
    cout << string(30, ' ') << "Elige un pokemon\n";
    leerAscii("../model/assets/marco2.txt");

    // Este for recorre los 6 Pokémon del equipo aliado y los imprime en pantalla
    for (int f = 0; f < 6; f++)
    {
        if (equipoAliado.pokemon[f].hp > 0 && f != pokemonActivo)
        {
            cout << string(35, ' ') << f + 1 << ". " << equipoAliado.pokemon[f].nombre
                 << " - HP: " << equipoAliado.pokemon[f].hp << "\n";
        }
        else if (f == pokemonActivo)
        {
            cout << string(35, ' ') << f + 1 << ". " << equipoAliado.pokemon[f].nombre << " (EN COMBATE)\n";
        }
        else
        {
            cout << string(35, ' ') << f + 1 << ". " << equipoAliado.pokemon[f].nombre << " (DEBILITADO)\n";
        }
    }

    cout << string(35, ' ') << "0. Regresar\n";
}

// Función para cambiar de Pokémon en medio de la batalla
void cambiarPokemonBatalla()
{
    int opcionElegida = 0;

    verPokemones(); // Muestra los Pokémon del equipo aliado y permite al jugador elegir uno para cambiar

    leerAscii("../model/assets/marco2.txt");
    cout << string(30, ' ') << "Ingresa el numero del Pokemon o 0 para regresar!\n";
    leerAscii("../model/assets/marcoArriba.txt");
    cin >> opcionElegida;

    // Opción 0 regresa al menú de batalla sin cambiar de Pokémon
    if (opcionElegida == 0)
    {
        system("cls");
        return;
    }

    // Convertimos la opción elegida a un índice de 0 a 5 (ya que el jugador ingresa de 1 a 6)
    int index = opcionElegida - 1;

    // Validación de rango y estado del Pokémon: Si el jugador escribe un número inválido (mayor a 6, menor a 1, o el Pokémon está debilitado), lo atrapamos en este bucle.
    while (index < 0 || index > 5 || equipoAliado.pokemon[index].hp <= 0 || index == pokemonActivo)
    {
        system("cls");
        infoPokemon(); // Mostramos la información de los Pokémon antes de mostrar el menú de cambio nuevamente
        verPokemones();
        leerAscii("../model/assets/marco2.txt");
        cout << string(30, ' ') << "Opcion invalida, intenta de nuevo (0 para regresar)\n";
        leerAscii("../model/assets/marcoArriba.txt");
        cin >> opcionElegida;

        // Opción 0 regresa al menú de batalla sin cambiar de Pokémon
        if (opcionElegida == 0)
            system("cls");
        index = opcionElegida - 1;
        return; // Regresa al menú de batalla si elige 0
    }

    pokemonActivo = index;

    system("cls");
    infoPokemon();
    verPokemones();
    leerAscii("../model/assets/marco2.txt");

    // Mensaje de confirmación del cambio de Pokémon
    cout << string(30, ' ') << "-> Regresa! Adelante, " << equipoAliado.pokemon[pokemonActivo].nombre << "!\n";
    leerAscii("../model/assets/marcoArriba.txt");
    Sleep(1500);
}

void iniciarBatalla()
{

    leerAscii("../model/assets/iniciarBatalla.txt");

    puntosBatallaActual = 0;

    // Inicializamos los equipos y variables de control
    prepararFaseSeleccion();
    generarEquipoEnemigo();

    // ESCALADO A NIVEL 60:
    // Multiplicamos la salud base por 2.5 y sumamos un fix plano para simular
    // la vida de un Pokémon a nivel medio-alto sin alterar permanentemente el struct.
    for (int i = 0; i < 6; i++)
    {
        equipoAliado.pokemon[i].hp = (equipoAliado.pokemon[i].hp * 2.5) + 60;
        equipoEnemigo.pokemon[i].hp = (equipoEnemigo.pokemon[i].hp * 2.5) + 60;
    }

    cout << string(60, ' ') << "-> El rival ha preparado su equipo de forma aleatoria!\n";
    cout << string(60, ' ') << "-> Todos los pokemones han sido nivelados al Nivel 60 para el torneo!\n"
         << endl;
    leerAscii("../model/assets/marcoArriba.txt");
    Sleep(3000); // es para que espere 3 segundos
    system("cls");

    pokemonActivo = 0;
    pokemonEnemigoActivo = 0;
    aliadoVivo = true;
    enemigoVivo = true;
}

// Función de apoyo: Convierte el string del tipo a su índice numérico (0 al 17)
int obtenerIndiceTipo(string tipo)
{
    if (tipo == "")
        return -1; // Para los Pokémon que no tienen segundo tipo
    for (int i = 0; i < 18; i++)
    {
        if (TIPOS[i] == tipo)
            return i;
    }
    return -1;
}

// Función 1: Verificar quién ataca primero basado en la velocidad
// Retorna true si el aliado ataca primero, false si el enemigo ataca primero
bool aliadoAtacaPrimero()
{
    int velJugador = equipoAliado.pokemon[pokemonActivo].velocidad;
    int velEnemigo = equipoEnemigo.pokemon[pokemonEnemigoActivo].velocidad;

    // Comparación de velocidades: Si hay empate, se decide al azar (50/50)
    if (velJugador > velEnemigo)
    {
        return true;
    }
    else if (velEnemigo > velJugador)
    {
        return false;
    }
    else
    {
        // Si hay empate de velocidad, se decide al azar (50/50)
        return (rand() % 2 == 0);
    }
}

// Función 2: Calcular el Daño en base a las estadísticas, tipo de ataque y efectividad
int calcularDano(Pokemon atacante, Pokemon defensor, Movimiento mov)
{
    // 1. Revisar si es Físico o Especial para usar las estadísticas correctas
    float poderAtaque = mov.esEspecial ? atacante.ataqueEsp : atacante.ataque;
    float poderDefensa = mov.esEspecial ? defensor.defensaEsp : defensor.defensa;

    // 2. Bonificación por mismo tipo (STAB). Si el ataque es del mismo tipo que el Pokémon, pega 50% más.
    float stab = 1.0;
    if (mov.tipo == atacante.tipos[0] || mov.tipo == atacante.tipos[1])
    {
        stab = 1.5;
    }

    // 3. Multiplicador de Efectividad usando la tabla de tipos
    int indiceMov = obtenerIndiceTipo(mov.tipo);
    int indiceDef1 = obtenerIndiceTipo(defensor.tipos[0]);
    int indiceDef2 = obtenerIndiceTipo(defensor.tipos[1]);

    float efectividad = 1.0;
    if (indiceMov != -1 && indiceDef1 != -1)
    {
        efectividad *= tablaEfectividad[indiceMov][indiceDef1];
    }
    // Si el defensor tiene un segundo tipo, lo multiplicamos también
    if (indiceMov != -1 && indiceDef2 != -1)
    {
        efectividad *= tablaEfectividad[indiceMov][indiceDef2];
    }

    // Imprimir mensaje de efectividad visual
    if (efectividad > 1.0)
        cout << string(30, ' ') << "-> Es super eficaz!\n";
    else if (efectividad < 1.0 && efectividad > 0.0)
        cout << string(30, ' ') << "-> No es muy eficaz...\n";
    else if (efectividad == 0.0)
        cout << string(30, ' ') << "-> No tiene efecto en " << defensor.nombre << "...\n";

    // 4. Fórmula de Daño final simplificada
    float danioBase = (mov.danio * (poderAtaque / poderDefensa)) / 2.0;
    int danioFinal = (danioBase * stab * efectividad);

    // Si el ataque no es inmune pero el cálculo da 0, aseguramos al menos 1 de daño
    if (danioFinal < 1 && efectividad > 0.0)
    {
        danioFinal = 1;
    }

    return danioFinal;
}

// Verifica el estado de salud de los equipos
void verificarYProcesarDebilitados()
{
    // 1. Validar Pokémon Aliado Activo
    if (equipoAliado.pokemon[pokemonActivo].hp <= 0)
    {
        equipoAliado.pokemon[pokemonActivo].hp = 0; // Evitamos HPs negativos visuales
        cout << string(30, ' ') << "Tu " << equipoAliado.pokemon[pokemonActivo].nombre << " se ha debilitado!\n";

        // Verificar si quedan Pokémon vivos en el equipo
        bool quedanVivos = false;
        for (int i = 0; i < 6; i++)
        {
            if (equipoAliado.pokemon[i].hp > 0)
            {
                quedanVivos = true;
                break;
            }
        }

        // Si quedan Pokémon vivos, forzamos al jugador a cambiar
        if (quedanVivos)
        {
            cout << string(30, ' ') << "Debes elegir a otro miembro de tu equipo para continuar.\n\n";
            leerAscii("../model/assets/marcoArriba.txt");
            Sleep(4500);
            system("cls");

            // Forzamos al jugador a cambiar.
            // Guardamos el índice actual; si no cambia con éxito, el bucle insistirá.
            int indexAnterior = pokemonActivo;
            while (pokemonActivo == indexAnterior)
            {
                infoPokemon();
                cambiarPokemonBatalla();
            }
        }
        else
        {

            // Si no quedan Pokémon vivos, el jugador pierde la batalla
            aliadoVivo = false;
        }
    }

    // 2. Validar Pokémon Enemigo Activo
    if (equipoEnemigo.pokemon[pokemonEnemigoActivo].hp <= 0)
    {
        equipoEnemigo.pokemon[pokemonEnemigoActivo].hp = 0;
        cout << string(30, ' ') << "El " << equipoEnemigo.pokemon[pokemonEnemigoActivo].nombre << " rival se ha debilitado!\n";

        // Al ser la maquina, avanzamos al siguiente de forma secuencial (del 0 al 5)
        if (pokemonEnemigoActivo < 5)
        {
            pokemonEnemigoActivo++;
            cout << string(30, ' ') << "El rival envia a " << equipoEnemigo.pokemon[pokemonEnemigoActivo].nombre << " a la arena!\n\n";
        }
        else
        {
            enemigoVivo = false; // Se quedó sin Pokémon, victoria del jugador
        }
    }
}

void ejecutarTurno(int indiceAtaque)
{
    // 1. La máquina elige un movimiento al azar de sus 4 opciones
    int indiceAtaqueEnemigo = rand() % 4;

    // 2. Obtenemos los movimientos elegidos por ambos Pokémon
    Movimiento movAliado = equipoAliado.pokemon[pokemonActivo].movimientos[indiceAtaque];
    Movimiento movEnemigo = equipoEnemigo.pokemon[pokemonEnemigoActivo].movimientos[indiceAtaqueEnemigo];

    // 3. Determinamos quién ataca primero basado en la velocidad
    bool jugadorPrimero = aliadoAtacaPrimero();

    system("cls");

    // Mostramos la información de los Pokémon y el marco superior antes de ejecutar los ataques
    infoPokemon();
    leerAscii("../model/assets/marcoArriba.txt");

    // 4. Ejecutamos los ataques en orden de velocidad
    if (jugadorPrimero)
    {
        // Ataca primero el jugador más rapido
        cout << string(30, ' ') << "* " << equipoAliado.pokemon[pokemonActivo].nombre << " es mas rapido!\n";
        cout << string(30, ' ') << "-> " << equipoAliado.pokemon[pokemonActivo].nombre << " usa " << movAliado.nombre << "!\n";

        // Calculamos el daño con las función de calcularDano y restamos la vida
        int danioAlEnemigo = calcularDano(equipoAliado.pokemon[pokemonActivo], equipoEnemigo.pokemon[pokemonEnemigoActivo], movAliado);

        // Restamos la vida al enemigo y sumamos los puntos de batalla
        equipoEnemigo.pokemon[pokemonEnemigoActivo].hp -= danioAlEnemigo;
        puntosBatallaActual += danioAlEnemigo;
        cout << string(30, ' ') << "-> Causo " << danioAlEnemigo << " puntos de danio.\n\n";

        // Si el enemigo muere aquí, ya no puede contraatacar
        if (equipoEnemigo.pokemon[pokemonEnemigoActivo].hp <= 0)
        {
            verificarYProcesarDebilitados();
            leerAscii("../model/assets/marcoArriba.txt");
            Sleep(4000);
            return;
        }

        // El enemigo ataca sólo si sobrevivió
        cout << "\n"
             << string(30, ' ') << "-> El rival " << equipoEnemigo.pokemon[pokemonEnemigoActivo].nombre << " usa " << movEnemigo.nombre << "!\n";
        int danioAlAliado = calcularDano(equipoEnemigo.pokemon[pokemonEnemigoActivo], equipoAliado.pokemon[pokemonActivo], movEnemigo);

        // Restamos la vida al aliado y mostramos el daño recibido
        equipoAliado.pokemon[pokemonActivo].hp -= danioAlAliado;
        cout << string(30, ' ') << "-> Recibiste " << danioAlAliado << " puntos de danio.\n\n";

        // Si el jugador muere aquí, se procesa su debilitamiento
        if (equipoAliado.pokemon[pokemonActivo].hp <= 0)
        {
            verificarYProcesarDebilitados(); // Procesamos el debilitamiento del aliado
        }
        else
        {
            leerAscii("../model/assets/marcoArriba.txt");
            Sleep(3000); // Espera 3 segundos antes de continuar
        }
    }
    else
    {
        // Ataca primero el enemigo mas rapido
        cout << string(30, ' ') << "El rival " << equipoEnemigo.pokemon[pokemonEnemigoActivo].nombre << " es mas rapido!\n";
        cout << string(30, ' ') << "-> El rival usa " << movEnemigo.nombre << "!\n";

        // Calculamos el daño con las función calcularDano y restamos la vida
        int danioAlAliado = calcularDano(equipoEnemigo.pokemon[pokemonEnemigoActivo], equipoAliado.pokemon[pokemonActivo], movEnemigo);

        // Restamos la vida al aliado y mostramos el daño recibido
        equipoAliado.pokemon[pokemonActivo].hp -= danioAlAliado;
        cout << string(30, ' ') << "-> Recibiste " << danioAlAliado << " puntos de danio.\n\n";

        // Si el jugador muere aquí, se cancela su ataque
        if (equipoAliado.pokemon[pokemonActivo].hp <= 0)
        {
            verificarYProcesarDebilitados();
            return;
        }

        // El jugador ataca sólo si sobrevivió
        cout << "\n"
             << string(30, ' ') << "-> " << equipoAliado.pokemon[pokemonActivo].nombre << " usa " << movAliado.nombre << "!\n";
        int danioAlEnemigo = calcularDano(equipoAliado.pokemon[pokemonActivo], equipoEnemigo.pokemon[pokemonEnemigoActivo], movAliado);

        // Restamos la vida al enemigo y sumamos los puntos de batalla
        equipoEnemigo.pokemon[pokemonEnemigoActivo].hp -= danioAlEnemigo;
        puntosBatallaActual += danioAlEnemigo;
        cout << string(30, ' ') << "-> Causo " << danioAlEnemigo << " puntos de danio.\n\n";

        // Si el enemigo muere aquí, se procesa su debilitamiento
        if (equipoEnemigo.pokemon[pokemonEnemigoActivo].hp <= 0)
        {
            verificarYProcesarDebilitados();
        }
        else
        {
            leerAscii("../model/assets/marcoArriba.txt");
            Sleep(3000); // Espera 3 segundos antes de continuar
        }
    }
}

// Función para procesar el contraataque del enemigo cuando el jugador cambia de Pokémon
void procesarContraataquePorCambio()
{
    system("cls");
    infoPokemon();
    leerAscii("../model/assets/marco3.txt");
    cout << string(30, ' ') << "Le diste una oportunidad al rival por cambiar!\n";
    leerAscii("../model/assets/marco2.txt");

    // La maquina elige un movimiento al azar de sus 4 opciones
    int indiceAtaqueEnemigo = rand() % 4;
    Movimiento movEnemigo = equipoEnemigo.pokemon[pokemonEnemigoActivo].movimientos[indiceAtaqueEnemigo];

    cout << "\n"
         << string(30, ' ') << "-> El rival " << equipoEnemigo.pokemon[pokemonEnemigoActivo].nombre
         << " aprovecha y usa " << movEnemigo.nombre << "!\n";

    // Calculamos el daño con las función calcularDano y restamos la vida
    int danioAlAliado = calcularDano(equipoEnemigo.pokemon[pokemonEnemigoActivo], equipoAliado.pokemon[pokemonActivo], movEnemigo);

    // Restamos la vida al aliado y mostramos el daño recibido
    equipoAliado.pokemon[pokemonActivo].hp -= danioAlAliado;
    cout << string(30, ' ') << "-> Recibiste " << danioAlAliado << " puntos de danio.\n\n";

    leerAscii("../model/assets/marcoArriba.txt");
    Sleep(3000); // Espera 3 segundos antes de continuar

    // Verificamos de inmediato si el Pokémon entrante resistió o se debilitó por el golpe
    verificarYProcesarDebilitados();
}
