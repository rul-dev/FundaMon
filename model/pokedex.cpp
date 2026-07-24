#include <string>
#include "structs.cpp"

using namespace std;

// Declaramos el arreglo con los primeros 30 Pokémon
Pokemon pokedexDisponible[30] = {
{
        "Venusaur", 
        "Pokemon Semilla. La flor de su lomo atrapa los rayos del sol y los transforma en energia.", 
        {"Planta", "Veneno"}, 
        80, 80, 82, 100, 83, 100,
        {
            {"Hoja Afilada", "Planta", 55, false},
            {"Bomba Lodo", "Veneno", 90, true},
            {"Gigadrenado", "Planta", 75, true},
            {"Derribo", "Normal", 90, false}
        },
        R"(
                            _._      _,._
                         _.'   `. ' .'   _`.
                 ,"""/`""-.-.,/. ` V'\-,`.,--/"""."-..
               ,'    `...,' . ,\-----._|      `.   /   \
              `.             .`  -'`"" .._   :> `-'   `.
            ,'  ,-.  _,.-'| `..___ ,'   |'-..__   .._ L
           .    \_ -'   `-'     ..      `.-' `.`-.'_ .|
           |   ,',-,--..  ,--../  `.  .-.    , `-.  ``.
           `.,' ,  |   |  `.  /'/,,.\/  |    \|   |
                `  `---'    `j   .   \  .     '   j
               ,__`"         ,'|`'\_/`.'\'        |\-'-, _,.
       .--...`-. `-`. /    '- ..      _,    /\ ,' .--"'  ,'".
     _'-""-    --  _`'-.../ __ '.'`-^,_`-""""---....__  ' _,-`
   _.----`  _..--.'        |  "`-..-" __|'"'         .""-. ""'--.._
  /        '    /     ,  _.+-.'  ||._'   """". .         `     .__\
 `---    /        /  / j'       _/|..`  -. `-`\ \   \  \   `.  \ `-..
," _.-' /    /` ./  /`_|_,-"   ','|        `. | -'`._,   L  \ .  `.   |
`"' /  /  / ,__...-----| _.,  ,'            `|----.._`-.|' |. .` ..  .
   /  '| /.,/   \--.._ `-,' ,          .  '`.'  __,., '  ''``._ \ \`,'
  /_,'---  ,      \`._,-` \ //  / . \    `._,  -`,  / / _   |   `-L -
   /        `.      ,  ..._ ' `_/ '| |\ `._'       '-.'   `.,'     |
  '         /    /  ..   `.  `./ | ; `.'    ,"" ,.  `.    \      |
   `.      ,'   ,'   | |\  |        "        |  ,'\ |   \    `    ,L
   /|`.  /    '     | `-| '                 /`-' |    L    `._/  \
  / | .`|    |  .   `._.'                  `.__,'   .  |     |  (`
 '-""-'_|    `. `.__,._____     .   _,        ____ ,-  j     ".-'"'
        \      `-.  \/.    `"--.._    _,.---'""\/  "_,.'      /-'
         )        `-._ '-.        `--"      _.-'.-""        `.
        ./            `,. `".._________...""_.-"`.          _j
       /_\.__,"".   ,.'  "`-...________.---"     .".   ,.  / \
              \_/"""-'                           `-'--(_,`"`-`
        )"
    },
    {
        "Charizard", 
        "Pokemon Llama...", 
        {"Fuego", "Volador"}, 
        78, 100, 84, 109, 78, 85,
        {
            {"Garra Dragon", "Dragon", 80, false},
            {"Tajo Aereo", "Volador", 75, true},
            {"Lanzallamas", "Fuego", 90, true},
            {"Envite Igneo", "Fuego", 120, false}
        },
        R"(
           [ PEGA TU ASCII DE CHARIZARD AQUI ]
        )"
    },
    {
        "Blastoise", 
        "Pokemon Armazon...", 
        {"Agua", ""}, 
        79, 78, 83, 85, 100, 105,
        {
            {"Acua Cola", "Agua", 90, false},
            {"Mordisco", "Siniestro", 60, false},
            {"Surf", "Agua", 90, true},
            {"Rayo Hielo", "Hielo", 90, true}
        },
        R"(
           [ PEGA TU ASCII DE BLASTOISE AQUI ]
        )"
    },
    {
        "Pikachu", 
        "Pokemon Raton...", 
        {"Electrico", ""}, 
        35, 90, 55, 50, 40, 50,
        {
            {"Impactrueno", "Electrico", 40, true},
            {"Ataque Rapido", "Normal", 40, false},
            {"Rayo", "Electrico", 90, true},
            {"Cola Ferrea", "Acero", 100, false}
        },
        R"(
               \:.             .:/
                \``._________.''/ 
                 \             / 
         .--.--, / .':.   .':. \
        /__:  /  | '::' . '::' |
           / /   |`.   ._.   .'|
          / /    |.'         '.|
         /___-_-,|.\  \   /  /.|
              // |''\.;   ;,/ '|
              `==|:=         =:|
                 `.          .'
                   :-._____.-:
                  `''       `''
        )"
    },
    {
        "Gengar", "Pokemon Sombra...", {"Fantasma", "Veneno"}, 
        60, 110, 65, 130, 60, 75,
        {
            {"Golpe Bajo", "Siniestro", 70, false},
            {"Bola Sombra", "Fantasma", 80, true},
            {"Carga Toxica", "Veneno", 65, true},
            {"Punio Sombra", "Fantasma", 60, false}
        },
        R"(
           [ PEGA TU ASCII DE GENGAR AQUI ]
        )"
    },
    {
        "Snorlax", "Pokemon Dormilon...", {"Normal", ""}, 
        160, 30, 110, 65, 65, 110,
        {
            {"Placaje", "Normal", 40, false},
            {"Golpe Cuerpo", "Normal", 85, false},
            {"Fuerza Equina", "Tierra", 95, false},
            {"Triturar", "Siniestro", 80, false}
        },
        R"(
           [ PEGA TU ASCII DE SNORLAX AQUI ]
        )"
    },
    {
        "Dragonite", "Pokemon Dragon...", {"Dragon", "Volador"}, 
        91, 80, 134, 100, 95, 100,
        {
            {"Ciclon", "Dragon", 40, true},
            {"Vuelo", "Volador", 90, false},
            {"Garra Dragon", "Dragon", 80, false},
            {"Carga Dragon", "Dragon", 100, false}
        },
        R"(
           [ PEGA TU ASCII DE DRAGONITE AQUI ]
        )"
    },
    {
        "Mewtwo", "Pokemon Genetico...", {"Psiquico", ""}, 
        106, 130, 110, 154, 90, 90,
        {
            {"Confusion", "Psiquico", 50, true},
            {"Psiquico", "Psiquico", 90, true},
            {"Esfera Aural", "Lucha", 80, true},
            {"Golpe", "Normal", 90, false}
        },
        R"(
           [ PEGA TU ASCII DE MEWTWO AQUI ]
        )"
    },
    {
        "Lapras", "Pokemon Transporte...", {"Agua", "Hielo"}, 
        130, 60, 85, 85, 80, 95,
        {
            {"Canto Helado", "Hielo", 40, false},
            {"Rayo Aurora", "Hielo", 65, true},
            {"Surf", "Agua", 90, true},
            {"Rayo Hielo", "Hielo", 90, true}
        },
        R"(
           [ PEGA TU ASCII DE LAPRAS AQUI ]
        )"
    },
    {
        "Empoleon", "Pokemon Emperador...", {"Agua", "Acero"}, 
        84, 60, 86, 111, 88, 101,
        {
            {"Acua Jet", "Agua", 40, false},
            {"Pico Taladro", "Volador", 80, false},
            {"Foco Resplandor", "Acero", 80, true},
            {"Hidrobomba", "Agua", 110, true}
        },
        R"(
           [ PEGA TU ASCII DE EMPOLEON AQUI ]
        )"
    },
    {
        "Sylveon", "Pokemon Vínculo...", {"Hada", ""}, 
        95, 60, 65, 110, 65, 130,
        {
            {"Ataque Rapido", "Normal", 40, false},
            {"Fuerza Lunar", "Hada", 95, true},
            {"Brillo Magico", "Hada", 80, true},
            {"Mordisco", "Siniestro", 60, false}
        },
        R"(
           [ PEGA TU ASCII DE SYLVEON AQUI ]
        )"
    },
    {
        "Greninja", "Pokemon Ninja...", {"Agua", "Siniestro"}, 
        72, 122, 95, 103, 67, 71,
        {
            {"Shuriken de Agua", "Agua", 60, true},
            {"Tajo Umbrio", "Siniestro", 70, false},
            {"Pulso Umbrio", "Siniestro", 80, true},
            {"Rayo Hielo", "Hielo", 90, true}
        },
        R"(
           [ PEGA TU ASCII DE GRENINJA AQUI ]
        )"
    },
    {
        "Sceptile", "Pokemon Bosque...", {"Planta", ""}, 
        70, 120, 85, 105, 65, 85,
        {
            {"Ataque Rapido", "Normal", 40, false},
            {"Tijera X", "Bicho", 80, false},
            {"Hoja Aguda", "Planta", 90, false},
            {"Lluevehojas", "Planta", 130, true}
        },
        R"(
           [ PEGA TU ASCII DE SCEPTILE AQUI ]
        )"
    },
    {
        "Alakazam", "Pokemon Psi...", {"Psiquico", ""}, 
        55, 120, 50, 135, 45, 95,
        {
            {"Psicorrayo", "Psiquico", 65, true},
            {"Psiquico", "Psiquico", 90, true},
            {"Bola Sombra", "Fantasma", 80, true},
            {"Brillo Magico", "Hada", 80, true}
        },
        R"(
           [ PEGA TU ASCII DE ALAKAZAM AQUI ]
        )"
    },
    {
        "Gardevoir", "Pokemon Envolvente...", {"Psiquico", "Hada"}, 
        68, 80, 65, 125, 65, 115,
        {
            {"Hoja Magica", "Planta", 60, true},
            {"Rayo", "Electrico", 90, true},
            {"Psiquico", "Psiquico", 90, true},
            {"Fuerza Lunar", "Hada", 95, true}
        },
        R"(
           [ PEGA TU ASCII DE GARDEVOIR AQUI ]
        )"
    },
    {
        "Garchomp", "Pokemon Mach...", {"Dragon", "Tierra"}, 
        108, 102, 130, 80, 95, 85,
        {
            {"Triturar", "Siniestro", 80, false},
            {"Garra Dragon", "Dragon", 80, false},
            {"Terremoto", "Tierra", 100, false},
            {"Carga Dragon", "Dragon", 100, false}
        },
        R"(
           [ PEGA TU ASCII DE GARCHOMP AQUI ]
        )"
    },
    {
        "Houndoom", "Pokemon Siniestro...", {"Siniestro", "Fuego"}, 
        75, 95, 90, 110, 50, 80,
        {
            {"Lanzallamas", "Fuego", 90, true},
            {"Triturar", "Siniestro", 80, false},
            {"Bomba Lodo", "Veneno", 90, true},
            {"Colmillo Igneo", "Fuego", 65, false}
        },
        R"(
           [ PEGA TU ASCII DE HOUNDOOM AQUI ]
        )"
    },
    {
        "Metagross", "Pokemon Pata Hierro...", {"Acero", "Psiquico"}, 
        80, 70, 135, 95, 130, 90,
        {
            {"Punio Meteoro", "Acero", 90, false},
            {"Cabezazo Zen", "Psiquico", 80, false},
            {"Terremoto", "Tierra", 100, false},
            {"Punio Bala", "Acero", 40, false}
        },
        R"(
           [ PEGA TU ASCII DE METAGROSS AQUI ]
        )"
    },
    {
        "Lucario", "Pokemon Aura...", {"Lucha", "Acero"}, 
        70, 90, 110, 115, 70, 70,
        {
            {"Esfera Aural", "Lucha", 80, true},
            {"Foco Resplandor", "Acero", 80, true},
            {"A Bocajarro", "Lucha", 120, false},
            {"Velocidad Extrema", "Normal", 80, false}
        },
        R"(
           [ PEGA TU ASCII DE LUCARIO AQUI ]
        )"
    },
    {
        "Volcarona", "Pokemon Sol...", {"Bicho", "Fuego"}, 
        85, 100, 60, 135, 65, 105,
        {
            {"Zumbido", "Bicho", 90, true},
            {"Danza Llama", "Fuego", 80, true},
            {"Vendaval", "Volador", 110, true},
            {"Llamarada", "Fuego", 110, true}
        },
        R"(
           [ PEGA TU ASCII DE VOLCARONA AQUI ]
        )"
    },
    {
        "Annihilape", "Pokemon Mono Furia...", {"Lucha", "Fantasma"}, 
        110, 90, 115, 50, 80, 90,
        {
            {"Punio Furia", "Fantasma", 50, false},
            {"A Bocajarro", "Lucha", 120, false},
            {"Garra Umbria", "Fantasma", 70, false},
            {"Enfado", "Dragon", 120, false}
        },
        R"(
           [ PEGA TU ASCII DE ANNIHILAPE AQUI ]
        )"
    },
    {
        "Articuno", "Pokemon Congelar...", {"Hielo", "Volador"}, 
        90, 85, 85, 95, 100, 125,
        {
            {"Rayo Hielo", "Hielo", 90, true},
            {"Vendaval", "Volador", 110, true},
            {"Liofilizacion", "Hielo", 70, true},
            {"Poder Pasado", "Roca", 60, true}
        },
        R"(
           [ PEGA TU ASCII DE ARTICUNO AQUI ]
        )"
    },
    {
        "Zapdos", "Pokemon Electrico...", {"Electrico", "Volador"}, 
        90, 100, 90, 125, 85, 90,
        {
            {"Rayo", "Electrico", 90, true},
            {"Pico Taladro", "Volador", 80, false},
            {"Onda Ignea", "Fuego", 95, true},
            {"Chispazo", "Electrico", 80, true}
        },
        R"(
           [ PEGA TU ASCII DE ZAPDOS AQUI ]
        )"
    },
    {
        "Excadrill", "Pokemon Perforadora...", {"Tierra", "Acero"}, 
        110, 88, 135, 60, 60, 65,
        {
            {"Terremoto", "Tierra", 100, false},
            {"Punio Meteoro", "Acero", 90, false},
            {"Roca Afilada", "Roca", 100, false},
            {"Tijera X", "Bicho", 80, false}
        },
        R"(
           [ PEGA TU ASCII DE EXCADRILL AQUI ]
        )"
    },
    {
        "Darkrai", "Pokemon Oscuridad...", {"Siniestro", ""}, 
        70, 125, 90, 135, 90, 90,
        {
            {"Pulso Umbrio", "Siniestro", 80, true},
            {"Bomba Lodo", "Veneno", 90, true},
            {"Rayo Hielo", "Hielo", 90, true},
            {"Juego Sucio", "Siniestro", 95, false}
        },
        R"(
           [ PEGA TU ASCII DE DARKRAI AQUI ]
        )"
    },
    {
        "Lopunny", "Pokemon Conejo...", {"Normal", ""}, 
        65, 105, 76, 54, 84, 96,
        {
            {"Retribucion", "Normal", 102, false},
            {"Patada Salto Alta", "Lucha", 130, false},
            {"Puño Hielo", "Hielo", 75, false},
            {"Cabezazo Zen", "Psiquico", 80, false}
        },
        R"(
           [ PEGA TU ASCII DE LOPUNNY AQUI ]
        )"
    },
    {
        "Tyranitar", "Pokemon Coraza...", {"Roca", "Siniestro"}, 
        100, 61, 134, 95, 110, 100,
        {
            {"Roca Afilada", "Roca", 100, false},
            {"Triturar", "Siniestro", 80, false},
            {"Terremoto", "Tierra", 100, false},
            {"Puño Fuego", "Fuego", 75, false}
        },
        R"(
           [ PEGA TU ASCII DE TYRANITAR AQUI ]
        )"
    },
    {
        "Toxtricity", "Pokemon Punk...", {"Electrico", "Veneno"}, 
        75, 75, 98, 114, 70, 70,
        {
            {"Amplificador", "Electrico", 80, true},
            {"Bomba Lodo", "Veneno", 90, true},
            {"Estruendo", "Normal", 140, true},
            {"Alarido", "Siniestro", 55, true}
        },
        R"(
           [ PEGA TU ASCII DE TOXTRICITY AQUI ]
        )"
    },
    {
        "Heracross", "Pokemon Unicornio...", {"Bicho", "Lucha"}, 
        80, 85, 125, 40, 75, 95,
        {
            {"Megacuerno", "Bicho", 120, false},
            {"A Bocajarro", "Lucha", 120, false},
            {"Roca Afilada", "Roca", 100, false},
            {"Tajo Umbrio", "Siniestro", 70, false}
        },
        R"(
           [ PEGA TU ASCII DE HERACROSS AQUI ]
        )"
    },
    {
        "Lycanroc", "Pokemon Lobo...", {"Roca", ""}, 
        75, 112, 117, 55, 65, 65,
        {
            {"Roca Afilada", "Roca", 100, false},
            {"Acelerroca", "Roca", 40, false},
            {"Triturar", "Siniestro", 80, false},
            {"A Bocajarro", "Lucha", 120, false}
        },
        R"(
           [ PEGA TU ASCII DE LYCANROC AQUI ]
        )"
    }
};