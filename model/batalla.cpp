#include <iostream>
#include <windows.h>
#include "../model/partida.cpp"
#include "../view/seleccionEquipo.cpp"

using namespace std;

// Variables globales para la persistencia de los equipos en la sesión de juego
Equipo equipoAliado;
Equipo equipoEnemigo;

void prepararFaseSeleccion()
{
    // Aquí invocamos la lógica pura del reclutamiento pasándole nuestro struct global
    GuardarEquipoPokemon(equipoAliado);
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
int activePokemon = 0;
int activePokemonEnemy = 0;

// Banderas de control de juego
bool aliadoVivo = true;
bool enemigoVivo = true;

void infoPokemon(){
    //Datos del enemigo y nosotros
    leerAscii("model/assets/marcoArriba.txt");
    cout <<string(110, ' ') <<"* RIVAL: " << equipoEnemigo.pokemon[activePokemonEnemy].nombre
         << " - Nv.60 (HP: " << equipoEnemigo.pokemon[activePokemonEnemy].hp << ")\n\n";
    leerAscii("model/assets/marco2.txt");
    leerAscii("model/assets/marco2.txt");
    cout <<"\n"<<string(30, ' ') << "* TU POKEMON: " << equipoAliado.pokemon[activePokemon].nombre
         << " - Nv.60 (HP: " << equipoAliado.pokemon[activePokemon].hp << ")\n\n";
}

// Función para mostrar los 4 ataques y validar la opción
void menuMovimientos(){
    leerAscii("model/assets/marco3.txt");
    cout << string(30,' ')<<"  Movimientos de " << equipoAliado.pokemon[activePokemon].nombre << "\n";
    leerAscii("model/assets/marco2.txt");
    cout<<"\n";

    for (int i = 0; i < 4; i++)
    {
        cout <<string(30,' ')<< i + 1 << ". " << equipoAliado.pokemon[activePokemon].movimientos[i].nombre
             << " (Tipo: " << equipoAliado.pokemon[activePokemon].movimientos[i].tipo
             << " | Danio: " << equipoAliado.pokemon[activePokemon].movimientos[i].danio << ")\n";
    }

    cout <<string(30,' ')<< "0. Regresar\n\n";
}

// Retorna el índice (0 al 3) del movimiento elegido
int seleccionarAtaque()
{

    int opcionAtaque = 0;
    menuMovimientos();
    leerAscii("model/assets/marco2.txt");
    cout <<string(30,' ')<< "Elige un ataque (1-4 y presione enter) o 0 para regresar\n";
    leerAscii("model/assets/marcoArriba.txt");
    cin >> opcionAtaque;

    while (opcionAtaque < 0 || opcionAtaque > 4)
    {
        system("cls");
        infoPokemon();
        menuMovimientos();
        leerAscii("model/assets/marco2.txt");
        cout <<string(30,' ')<< "Opcion invalida. Intenta de nuevo (0-4)\n";
        leerAscii("model/assets/marcoArriba.txt");
        cin >> opcionAtaque;
    }

    if (opcionAtaque == 0)
        return -1; // -1 indica que regresó

    return opcionAtaque - 1;
}

// Función para cambiar de Pokémon en medio de la batalla
void cambiarPokemonBatalla()
{
    int opcionElegida = 0;

    cout << "\nElige un pokemon:\n";
    cout << "---------------------------------------------\n";

    for (int f = 0; f < 6; f++)
    {
        if (equipoAliado.pokemon[f].hp > 0 && f != activePokemon)
        {
            cout << f + 1 << ". " << equipoAliado.pokemon[f].nombre
                 << " - HP: " << equipoAliado.pokemon[f].hp << "\n";
        }
        else if (f == activePokemon)
        {
            cout << f + 1 << ". " << equipoAliado.pokemon[f].nombre << " (EN COMBATE)\n";
        }
        else
        {
            cout << f + 1 << ". " << equipoAliado.pokemon[f].nombre << " (DEBILITADO)\n";
        }
    }

    cout << "0. Regresar\n";
    cout << "---------------------------------------------\n";
    cout << "Ingresa el numero del Pokemon o 0 para regresar: ";
    cin >> opcionElegida;

    if (opcionElegida == 0)
    {
        system("cls");
        return;
    }

    int index = opcionElegida - 1;

    while (index < 0 || index > 5 || equipoAliado.pokemon[index].hp <= 0 || index == activePokemon)
    {
        cout << "Opción inválida, intenta de nuevo (0 para regresar): ";
        cin >> opcionElegida;
        if (opcionElegida == 0)
            system("cls");
        return; // También puede regresar desde aquí
        index = opcionElegida - 1;
    }

    activePokemon = index;
    cout << "\n-> Regresa! Adelante, " << equipoAliado.pokemon[activePokemon].nombre << "!\n";
}

void iniciarBatalla() {
    
    leerAscii("model/assets/iniciarBatalla.txt");

    puntosBatallaActual = 0;
    prepararFaseSeleccion();
    generarEquipoEnemigo();

    // ESCALADO A NIVEL 60:
    // Multiplicamos la salud base por 2.5 y sumamos un fix plano para simular 
    // la vida de un Pokémon a nivel medio-alto sin alterar permanentemente el struct.
    for (int i = 0; i < 6; i++) {
        equipoAliado.pokemon[i].hp = (equipoAliado.pokemon[i].hp * 2.5) + 60;
        equipoEnemigo.pokemon[i].hp = (equipoEnemigo.pokemon[i].hp * 2.5) + 60;
    }

    cout << string(60, ' ')<<"-> El rival ha preparado su equipo de forma aleatoria!\n";
    cout << string(60, ' ')<<"-> Todos los pokemones han sido nivelados al Nivel 60 para el torneo!\n"<<endl;
    leerAscii("model/assets/marcoArriba.txt");
    Sleep(3500); //es para que espere 3 segundos
    system("cls");
    
    activePokemon = 0;
    activePokemonEnemy = 0;
    aliadoVivo = true;
    enemigoVivo = true;
}

// Función de apoyo: Convierte el string del tipo a su índice numérico (0 al 17)
int obtenerIndiceTipo(string tipo) {
    if (tipo == "") return -1; // Para los Pokémon que no tienen segundo tipo
    for (int i = 0; i < 18; i++) {
        if (TIPOS[i] == tipo) return i;
    }
    return -1;
}

// Función 1: Verificar quién ataca primero basado en la velocidad
// Retorna TRUE si el jugador ataca primero, FALSE si el enemigo ataca primero
bool aliadoAtacaPrimero() {
    int velJugador = equipoAliado.pokemon[activePokemon].velocidad;
    int velEnemigo = equipoEnemigo.pokemon[activePokemonEnemy].velocidad;

    if (velJugador > velEnemigo) {
        return true;
    } else if (velEnemigo > velJugador) {
        return false;
    } else {
        // Si hay empate de velocidad, se decide al azar (50/50)
        return (rand() % 2 == 0);
    }
}

// Función 2: Calcular el Daño (Exactamente como tu diagrama)
int calcularDano(Pokemon atacante, Pokemon defensor, Movimiento mov) {
    // 1. Revisar si es Físico o Especial para usar las estadísticas correctas
    float poderAtaque = mov.esEspecial ? atacante.ataqueEsp : atacante.ataque;
    float poderDefensa = mov.esEspecial ? defensor.defensaEsp : defensor.defensa;

    // 2. Bonificación por mismo tipo (STAB). Si el ataque es del mismo tipo que el Pokémon, pega 50% más.
    float stab = 1.0;
    if (mov.tipo == atacante.tipos[0] || mov.tipo == atacante.tipos[1]) {
        stab = 1.5;
    }

    // 3. Multiplicador de Efectividad (Usando tu tabla 18x18)
    int indiceMov = obtenerIndiceTipo(mov.tipo);
    int indiceDef1 = obtenerIndiceTipo(defensor.tipos[0]);
    int indiceDef2 = obtenerIndiceTipo(defensor.tipos[1]);

    float efectividad = 1.0;
    if (indiceMov != -1 && indiceDef1 != -1) {
        efectividad *= tablaEfectividad[indiceMov][indiceDef1];
    }
    // Si el defensor tiene un segundo tipo, lo multiplicamos también
    if (indiceMov != -1 && indiceDef2 != -1) {
        efectividad *= tablaEfectividad[indiceMov][indiceDef2];
    }

    // Imprimir mensaje de efectividad visual
    if (efectividad > 1.0) cout <<string(30,' ')<< "-> Es super eficaz!\n";
    else if (efectividad < 1.0 && efectividad > 0.0) cout <<string(30,' ')<< "-> No es muy eficaz...\n";
    else if (efectividad == 0.0) cout <<string(30,' ')<< "-> No tiene efecto en " << defensor.nombre << "...\n";

    // 4. Fórmula de Daño final simplificada para fundamentos
    float danioBase = (mov.danio * (poderAtaque / poderDefensa)) / 2.0;
    int danioFinal = (danioBase * stab * efectividad);

    // Si el ataque no es inmune pero el cálculo da 0, aseguramos al menos 1 de daño
    if (danioFinal < 1 && efectividad > 0.0) {
        danioFinal = 1;
    }

    return danioFinal;
}

// =============================================================================
// NUEVA FUNCIÓN DE APOYO: Verifica el estado de salud de los equipos
// =============================================================================
void verificarYProcesarDebilitados() {
    // 1. Validar Pokémon Aliado Activo
    if (equipoAliado.pokemon[activePokemon].hp <= 0) {
        equipoAliado.pokemon[activePokemon].hp = 0; // Evitamos HPs negativos visuales
        cout << "\nTu " << equipoAliado.pokemon[activePokemon].nombre << " se ha debilitado!\n";
        Sleep(1500);

        // Verificar si quedan Pokémon vivos en el equipo
        bool quedanVivos = false;
        for (int i = 0; i < 6; i++) {
            if (equipoAliado.pokemon[i].hp > 0) {
                quedanVivos = true;
                break;
            }
        }

        if (quedanVivos) {
            cout << "Debes elegir a otro miembro de tu equipo para continuar.\n";
            Sleep(1000);
            system("cls");
            
            // Forzamos al jugador a cambiar. 
            // Guardamos el índice actual; si no cambia con éxito, el bucle insistirá.
            int indexAnterior = activePokemon;
            while (activePokemon == indexAnterior) {
                cambiarPokemonBatalla();
            }
        } else {
            aliadoVivo = false; // Fin de la partida global
        }
    }

    // 2. Validar Pokémon Enemigo Activo
    if (equipoEnemigo.pokemon[activePokemonEnemy].hp <= 0) {
        equipoEnemigo.pokemon[activePokemonEnemy].hp = 0;
        cout << "\nEl " << equipoEnemigo.pokemon[activePokemonEnemy].nombre << " rival se ha debilitado!\n";
        Sleep(1500);

        // Al ser la IA, avanzamos al siguiente de forma secuencial (del 0 al 5)
        if (activePokemonEnemy < 5) {
            activePokemonEnemy++;
            cout << "El rival envia a " << equipoEnemigo.pokemon[activePokemonEnemy].nombre << " a la arena!\n";
            Sleep(2000);
        } else {
            enemigoVivo = false; // Se quedó sin Pokémon, victoria del jugador
        }
    }
}

void ejecutarTurno(int indiceAtaque) {
    int indiceAtaqueEnemigo = rand() % 4;

    Movimiento movAliado = equipoAliado.pokemon[activePokemon].movimientos[indiceAtaque];
    Movimiento movEnemigo = equipoEnemigo.pokemon[activePokemonEnemy].movimientos[indiceAtaqueEnemigo];

    bool jugadorPrimero = aliadoAtacaPrimero();
    
    system("cls");
    infoPokemon();
    leerAscii("model/assets/marcoArriba.txt");
    
    if (jugadorPrimero) {
        // === JUGADOR ES MÁS RÁPIDO ===
        cout <<string(30,' ')<< "* " << equipoAliado.pokemon[activePokemon].nombre << " es mas rapido!\n";
        cout <<string(30,' ')<< "-> " << equipoAliado.pokemon[activePokemon].nombre << " usa " << movAliado.nombre << "!\n";
        
        int danioAlEnemigo = calcularDano(equipoAliado.pokemon[activePokemon], equipoEnemigo.pokemon[activePokemonEnemy], movAliado);
        equipoEnemigo.pokemon[activePokemonEnemy].hp -= danioAlEnemigo;
        puntosBatallaActual += danioAlEnemigo;
        cout <<string(30,' ')<< "-> Causo " << danioAlEnemigo << " puntos de danio.\n\n";
        
        // CORRECCIÓN: Si el enemigo muere aquí, ya no puede contraatacar
        if (equipoEnemigo.pokemon[activePokemonEnemy].hp <= 0) {
            verificarYProcesarDebilitados();
            leerAscii("model/assets/marcoArriba.txt");
            Sleep(2500);
            return; 
        }

        // El enemigo ataca sólo si sobrevivió
        cout <<"\n"<<string(30,' ')<< "-> El rival " << equipoEnemigo.pokemon[activePokemonEnemy].nombre << " usa " << movEnemigo.nombre << "!\n";
        int danioAlAliado = calcularDano(equipoEnemigo.pokemon[activePokemonEnemy], equipoAliado.pokemon[activePokemon], movEnemigo);
        equipoAliado.pokemon[activePokemon].hp -= danioAlAliado;
        cout <<string(30,' ')<< "-> Recibiste " << danioAlAliado << " puntos de danio.\n\n";
        
        if (equipoAliado.pokemon[activePokemon].hp <= 0) {
            verificarYProcesarDebilitados();
        }
    } 
    else {
        // === ENEMIGO ES MÁS RÁPIDO ===
        cout <<string(30,' ')<< "El rival " << equipoEnemigo.pokemon[activePokemonEnemy].nombre << " es mas rapido!\n";
        cout <<string(30,' ')<< "-> El rival usa " << movEnemigo.nombre << "!\n";
        
        int danioAlAliado = calcularDano(equipoEnemigo.pokemon[activePokemonEnemy], equipoAliado.pokemon[activePokemon], movEnemigo);
        equipoAliado.pokemon[activePokemon].hp -= danioAlAliado;
        cout <<string(30,' ')<< "-> Recibiste " << danioAlAliado << " puntos de danio.\n\n";

        // CORRECCIÓN: Si el jugador muere aquí, se cancela su ataque
        if (equipoAliado.pokemon[activePokemon].hp <= 0) {
            verificarYProcesarDebilitados();
            leerAscii("model/assets/marcoArriba.txt");
            Sleep(2500);
            return;
        }

        // El jugador ataca sólo si sobrevivió
        cout <<"\n"<<string(30,' ')<< "-> " << equipoAliado.pokemon[activePokemon].nombre << " usa " << movAliado.nombre << "!\n";
        int danioAlEnemigo = calcularDano(equipoAliado.pokemon[activePokemon], equipoEnemigo.pokemon[activePokemonEnemy], movAliado);
        equipoEnemigo.pokemon[activePokemonEnemy].hp -= danioAlEnemigo;
        puntosBatallaActual += danioAlEnemigo;
        cout <<string(30,' ')<< "-> Causo " << danioAlEnemigo << " puntos de danio.\n\n";
        
        if (equipoEnemigo.pokemon[activePokemonEnemy].hp <= 0) {
            verificarYProcesarDebilitados();
        }
    }
    leerAscii("model/assets/marcoArriba.txt");
    Sleep(2500);
}

void procesarContraataquePorCambio() {
    cout << "\n=============================================\n";
    cout << "Le diste una oportunidad al rival por cambiar!\n";
    
    // La IA elige un movimiento al azar de sus 4 opciones
    int indiceAtaqueEnemigo = rand() % 4;
    Movimiento movEnemigo = equipoEnemigo.pokemon[activePokemonEnemy].movimientos[indiceAtaqueEnemigo];
    
    cout <<string(30,' ')<< "-> El rival " << equipoEnemigo.pokemon[activePokemonEnemy].nombre 
         << " aprovecha y usa " << movEnemigo.nombre << "!\n";
    
    // Calculamos el daño con las funciones nativas y restamos la vida
    int danioAlAliado = calcularDano(equipoEnemigo.pokemon[activePokemonEnemy], equipoAliado.pokemon[activePokemon], movEnemigo);
    equipoAliado.pokemon[activePokemon].hp -= danioAlAliado;
    
    cout <<string(30,' ')<< "-> Recibiste " << danioAlAliado << " puntos de danio.\n\n";
    leerAscii("model/assets/marcoArriba.txt");
    Sleep(2500);

    // Verificamos de inmediato si el Pokémon entrante resistió o se debilitó por el golpe
    verificarYProcesarDebilitados();
}