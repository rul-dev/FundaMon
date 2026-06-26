#include <string>
#include "structs.cpp" // Asegúrate de que este archivo tenga tus structs definidos

using namespace std;

// Declaramos el arreglo con los primeros 10 Pokémon
Pokemon pokedexDisponible[30] = {
{
        "Venusaur", 
        "Pokemon Semilla. La flor de su lomo atrapa los rayos del sol y los transforma en energia.", 
        {"Planta", "Veneno"}, 
        80, 80, 82, 100, 83, 100, // hp, velocidad, ataque, ataqueEsp, defensa, defensaEsp
        {
            {"Hoja Afilada", "Planta", 55, false},
            {"Bomba Lodo", "Veneno", 90, true},
            {"Gigadrenado", "Planta", 75, true},
            {"Derribo", "Normal", 90, false}
        }
    },
    {
        "Charizard", 
        "Pokemon Llama. Escupe un fuego tan caliente que funde las rocas. Causa incendios sin querer.", 
        {"Fuego", "Volador"}, 
        78, 100, 84, 109, 78, 85,
        {
            {"Garra Dragon", "Dragon", 80, false},
            {"Tajo Aereo", "Volador", 75, true},
            {"Lanzallamas", "Fuego", 90, true},
            {"Envite Igneo", "Fuego", 120, false}
        }
    },
    {
        "Blastoise", 
        "Pokemon Armazon. Los cohetes de su caparazon disparan chorros de agua con gran precision.", 
        {"Agua", ""}, 
        79, 78, 83, 85, 100, 105,
        {
            {"Acua Cola", "Agua", 90, false},
            {"Mordisco", "Siniestro", 60, false},
            {"Surf", "Agua", 90, true},
            {"Rayo Hielo", "Hielo", 90, true}
        }
    },
    {
        "Pikachu", 
        "Pokemon Raton. Cuando se enfada, libera al instante la energia que almacena en las mejillas.", 
        {"Electrico", ""}, 
        35, 90, 55, 50, 40, 50,
        {
            {"Impactrueno", "Electrico", 40, true},
            {"Ataque Rapido", "Normal", 40, false},
            {"Rayo", "Electrico", 90, true},
            {"Cola Ferrea", "Acero", 100, false}
        }
    },
    {
        "Gengar", 
        "Pokemon Sombra. Para quitarle la vida a su presa, se desliza en su sombra y espera su oportunidad.", 
        {"Fantasma", "Veneno"}, 
        60, 110, 65, 130, 60, 75,
        {
            {"Golpe Bajo", "Siniestro", 70, false},
            {"Bola Sombra", "Fantasma", 80, true},
            {"Carga Toxica", "Veneno", 65, true},
            {"Punio Sombra", "Fantasma", 60, false}
        }
    },
    {
        "Snorlax", 
        "Pokemon Dormilon. No se encuentra satisfecho hasta haber ingerido 400 kg de comida cada dia.", 
        {"Normal", ""}, 
        160, 30, 110, 65, 65, 110,
        {
            {"Placaje", "Normal", 40, false},
            {"Golpe Cuerpo", "Normal", 85, false},
            {"Fuerza Equina", "Tierra", 95, false},
            {"Triturar", "Siniestro", 80, false}
        }
    },
    {
        "Dragonite", 
        "Pokemon Dragon. Es capaz de dar la vuelta al mundo en tan solo 16 horas.", 
        {"Dragon", "Volador"}, 
        91, 80, 134, 100, 95, 100,
        {
            {"Ciclon", "Dragon", 40, true},
            {"Vuelo", "Volador", 90, false},
            {"Garra Dragon", "Dragon", 80, false},
            {"Carga Dragon", "Dragon", 100, false}
        }
    },
    {
        "Mewtwo", 
        "Pokemon Genetico. Fue creado por un cientifico tras años de horribles experimentos.", 
        {"Psiquico", ""}, 
        106, 130, 110, 154, 90, 90,
        {
            {"Confusion", "Psiquico", 50, true},
            {"Psiquico", "Psiquico", 90, true},
            {"Esfera Aural", "Lucha", 80, true},
            {"Golpe", "Normal", 90, false}
        }
    },
    {
        "Lapras", 
        "Pokemon Transporte. Posee un corazon docil y le encanta llevar a la gente por el mar.", 
        {"Agua", "Hielo"}, 
        130, 60, 85, 85, 80, 95,
        {
            {"Canto Helado", "Hielo", 40, false},
            {"Rayo Aurora", "Hielo", 65, true},
            {"Surf", "Agua", 90, true},
            {"Rayo Hielo", "Hielo", 90, true}
        }
    },
    {
        "Empoleon", 
        "Pokemon Emperador. Evita las disputas innecesarias, pero diezmara a quien amenace su orgullo.", 
        {"Agua", "Acero"}, 
        84, 60, 86, 111, 88, 101,
        {
            {"Acua Jet", "Agua", 40, false},
            {"Pico Taladro", "Volador", 80, false},
            {"Foco Resplandor", "Acero", 80, true},
            {"Hidrobomba", "Agua", 110, true}
        }
    },
    {
        "Sylveon", 
        "Pokemon Vínculo. Sus apendices sensitivos emiten un aura que calma los animos.", 
        {"Hada", ""}, 
        95, 60, 65, 110, 65, 130,
        {
            {"Ataque Rapido", "Normal", 40, false},
            {"Fuerza Lunar", "Hada", 95, true},
            {"Brillo Magico", "Hada", 80, true},
            {"Mordisco", "Siniestro", 60, false}
        }
    },
    {
        "Greninja", 
        "Pokemon Ninja. Aparece y desaparece de improvisto, cual ninja. Marea al oponente con su agilidad.", 
        {"Agua", "Siniestro"}, 
        72, 122, 95, 103, 67, 71,
        {
            {"Shuriken de Agua", "Agua", 60, true},
            {"Tajo Umbrio", "Siniestro", 70, false},
            {"Pulso Umbrio", "Siniestro", 80, true},
            {"Rayo Hielo", "Hielo", 90, true}
        }
    },
    {
        "Sceptile", 
        "Pokemon Bosque. Las hojas que le crecen en los brazos pueden cortar gruesos arboles.", 
        {"Planta", ""}, 
        70, 120, 85, 105, 65, 85,
        {
            {"Ataque Rapido", "Normal", 40, false},
            {"Tijera X", "Bicho", 80, false},
            {"Hoja Aguda", "Planta", 90, false},
            {"Lluevehojas", "Planta", 130, true}
        }
    },
    {
        "Alakazam", 
        "Pokemon Psi. Su cerebro no deja de crecer, por lo que su cabeza pesa demasiado para sostenerla.", 
        {"Psiquico", ""}, 
        55, 120, 50, 135, 45, 95,
        {
            {"Psicorrayo", "Psiquico", 65, true},
            {"Psiquico", "Psiquico", 90, true},
            {"Bola Sombra", "Fantasma", 80, true},
            {"Brillo Magico", "Hada", 80, true}
        }
    },
    {
        "Gardevoir", 
        "Pokemon Envolvente. Tiene el poder de predecir el futuro. Protege a su Entrenador con su vida.", 
        {"Psiquico", "Hada"}, 
        68, 80, 65, 125, 65, 115,
        {
            {"Hoja Magica", "Planta", 60, true},
            {"Rayo", "Electrico", 90, true},
            {"Psiquico", "Psiquico", 90, true},
            {"Fuerza Lunar", "Hada", 95, true}
        }
    },
    {
        "Garchomp", 
        "Pokemon Mach. Vuela a la velocidad del sonido. Sus alas crean remolinos que destrozan arboles.", 
        {"Dragon", "Tierra"}, 
        108, 102, 130, 80, 95, 85,
        {
            {"Triturar", "Siniestro", 80, false},
            {"Garra Dragon", "Dragon", 80, false},
            {"Terremoto", "Tierra", 100, false},
            {"Carga Dragon", "Dragon", 100, false}
        }
    },
    {
        "Houndoom", 
        "Pokemon Siniestro. Los aullidos que emite resultan tan lugubres que antaño se creia que era el enviado de la muerte.", 
        {"Siniestro", "Fuego"}, 
        75, 95, 90, 110, 50, 80, // hp, velocidad, ataque, ataqueEsp, defensa, defensaEsp
        {
            {"Lanzallamas", "Fuego", 90, true},
            {"Triturar", "Siniestro", 80, false},
            {"Bomba Lodo", "Veneno", 90, true},
            {"Colmillo Igneo", "Fuego", 65, false}
        }
    },
    {
        "Metagross", 
        "Pokemon Pata Hierro. Con sus cuatro cerebros, posee una inteligencia comparable a la de un superordenador.", 
        {"Acero", "Psiquico"}, 
        80, 70, 135, 95, 130, 90,
        {
            {"Punio Meteoro", "Acero", 90, false},
            {"Cabezazo Zen", "Psiquico", 80, false},
            {"Terremoto", "Tierra", 100, false},
            {"Punio Bala", "Acero", 40, false}
        }
    },
    {
        "Lucario", 
        "Pokemon Aura. Puede leer los pensamientos y los movimientos de su adversario a traves de su aura.", 
        {"Lucha", "Acero"}, 
        70, 90, 110, 115, 70, 70,
        {
            {"Esfera Aural", "Lucha", 80, true},
            {"Foco Resplandor", "Acero", 80, true},
            {"A Bocajarro", "Lucha", 120, false},
            {"Velocidad Extrema", "Normal", 80, false}
        }
    },
    {
        "Volcarona", 
        "Pokemon Sol. Sus escamas en llamas pueden reemplazar al sol y calentar lugares sumidos en el frio.", 
        {"Bicho", "Fuego"}, 
        85, 100, 60, 135, 65, 105,
        {
            {"Zumbido", "Bicho", 90, true},
            {"Danza Llama", "Fuego", 80, true},
            {"Vendaval", "Volador", 110, true},
            {"Llamarada", "Fuego", 110, true}
        }
    },
    {
        "Annihilape", 
        "Pokemon Mono Furia. Al alcanzar el limite de su furia, se desprendio de su cuerpo fisico y alcanzo un poder sin igual.", 
        {"Lucha", "Fantasma"}, 
        110, 90, 115, 50, 80, 90,
        {
            {"Punio Furia", "Fantasma", 50, false},
            {"A Bocajarro", "Lucha", 120, false},
            {"Garra Umbria", "Fantasma", 70, false},
            {"Enfado", "Dragon", 120, false}
        }
    },
    {
        "Articuno", 
        "Pokemon Congelar. Es un pajaro legendario. Puede controlar el hielo a voluntad.", 
        {"Hielo", "Volador"}, 
        90, 85, 85, 95, 100, 125,
        {
            {"Rayo Hielo", "Hielo", 90, true},
            {"Vendaval", "Volador", 110, true},
            {"Liofilizacion", "Hielo", 70, true},
            {"Poder Pasado", "Roca", 60, true}
        }
    },
    {
        "Zapdos", 
        "Pokemon Electrico. Pajaro legendario que controla la electricidad. Dicen que vive en nubarrones oscuros.", 
        {"Electrico", "Volador"}, 
        90, 100, 90, 125, 85, 90,
        {
            {"Rayo", "Electrico", 90, true},
            {"Pico Taladro", "Volador", 80, false},
            {"Onda Ignea", "Fuego", 95, true},
            {"Chispazo", "Electrico", 80, true}
        }
    },
    {
        "Excadrill", 
        "Pokemon Perforadora. Puede perforar placas de acero con sus garras.", 
        {"Tierra", "Acero"}, 
        110, 88, 135, 60, 60, 65, // hp, velocidad, ataque, ataqueEsp, defensa, defensaEsp
        {
            {"Terremoto", "Tierra", 100, false},
            {"Punio Meteoro", "Acero", 90, false},
            {"Roca Afilada", "Roca", 100, false},
            {"Tijera X", "Bicho", 80, false}
        }
    },
    {
        "Darkrai", 
        "Pokemon Oscuridad. Para protegerse, infunde pesadillas, pero no lo hace de manera malintencionada.", 
        {"Siniestro", ""}, 
        70, 125, 90, 135, 90, 90,
        {
            {"Pulso Umbrio", "Siniestro", 80, true},
            {"Bomba Lodo", "Veneno", 90, true},
            {"Rayo Hielo", "Hielo", 90, true},
            {"Juego Sucio", "Siniestro", 95, false}
        }
    },
    {
        "Lopunny", 
        "Pokemon Conejo. Es muy cauteloso. Si detecta el menor peligro, huye dando saltos a gran velocidad.", 
        {"Normal", ""}, 
        65, 105, 76, 54, 84, 96, // hp, velocidad, ataque, ataqueEsp, defensa, defensaEsp
        {
            {"Retribucion", "Normal", 102, false},
            {"Patada Salto Alta", "Lucha", 130, false},
            {"Puño Hielo", "Hielo", 75, false},
            {"Cabezazo Zen", "Psiquico", 80, false}
        }
    },
    {
        "Tyranitar", 
        "Pokemon Coraza. Su cuerpo no puede ser dañado por casi ningun ataque. Es extremadamente agresivo.", 
        {"Roca", "Siniestro"}, 
        100, 61, 134, 95, 110, 100,
        {
            {"Roca Afilada", "Roca", 100, false},
            {"Triturar", "Siniestro", 80, false},
            {"Terremoto", "Tierra", 100, false},
            {"Puño Fuego", "Fuego", 75, false}
        }
    },
    {
        "Toxtricity", 
        "Pokemon Punk. Genera electricidad en su estomago. Cuando ruge, suena como un instrumento de cuerda.", 
        {"Electrico", "Veneno"}, 
        75, 75, 98, 114, 70, 70,
        {
            {"Amplificador", "Electrico", 80, true},
            {"Bomba Lodo", "Veneno", 90, true},
            {"Estruendo", "Normal", 140, true},
            {"Alarido", "Siniestro", 55, true}
        }
    },
    {
        "Heracross", 
        "Pokemon Unicornio. Posee una fuerza increible, capaz de lanzar por los aires a sus rivales con su poderoso cuerno.", 
        {"Bicho", "Lucha"}, 
        80, 85, 125, 40, 75, 95,
        {
            {"Megacuerno", "Bicho", 120, false},
            {"A Bocajarro", "Lucha", 120, false},
            {"Roca Afilada", "Roca", 100, false},
            {"Tajo Umbrio", "Siniestro", 70, false}
        }
    },
    {
        "Lycanroc", 
        "Pokemon Lobo. Acorrala a su presa con movimientos rapidos y asesta el golpe de gracia con sus afilados colmillos.", 
        {"Roca", ""}, 
        75, 112, 117, 55, 65, 65,
        {
            {"Roca Afilada", "Roca", 100, false},
            {"Acelerroca", "Roca", 40, false},
            {"Triturar", "Siniestro", 80, false},
            {"A Bocajarro", "Lucha", 120, false}
        }
    }
};