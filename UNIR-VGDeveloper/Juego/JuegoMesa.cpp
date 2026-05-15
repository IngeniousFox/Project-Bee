// proyecto: Grupal/Juego
// arhivo:   JuegoMesa.cpp
// versión:  1.1  (9-Ene-2023)


#include "juego.h"


namespace juego {


    /*******************************************************************************************
    /*******************************************************************************************
        
    CONFIGURACIÓN DEL JUEGO
    Primera sección - Los recursos

    En esta sección se establecen las carpetas en las que aparecen los recursos usados por el 
    juego, incluyendo las imágenes que aparecen en pantalla y los sonidos que se escuchan. Hay 
    una carpeta separada para los retratos de los personajes y otra para las imágenes de las 
    habilidades.

    Las carpetas están situadas en la carpeta donde están los archivos de código fuente del 
    proyecto.

    En principio no es necesario hacer ningún cambio en esta sección, si los recursos que se 
    cambian se sitúan en las mismas carpetas.

    *******************************************************************************************/
    string JuegoMesa::carpeta_activos_juego  {"./activos/"};
    string JuegoMesa::carpeta_retratos_juego {"./retratos/"};
    string JuegoMesa::carpeta_habilids_juego {"./habilidades/"};
    string JuegoMesa::carpeta_sonidos_juego  {"./sonidos/"};
    /*******************************************************************************************
    /******************************************************************************************/


    const std::wstring JuegoMesa::tituloVentana () const {
        return L"UNIR-2D :: Juego de Mesa";
    }


    JuegoMesa::JuegoMesa () {
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Segunda sección - El modo del juego

        En esta sección se configura el modo general del juego, es decir como se suceden las 
        jugadas, los turnos y las rondas. Y como se establece el personaje que realiza cada jugada.  

        La configuración del modo del juego se realiza mediante la elección de alguno de los
        modos preestablecidos. Es la única forma de configurar el modo del juego.

        Hay tres modos de juego preestablecidos:

            1) Modo de juego por pares
            2) Modo de juego por equipos
            3) Modo de juego libre de doble jugada

        Las siguientes definiciones se aplican a todos los modos de juego:

        Jugada:   
            Es una acción realizada con uno de los personajes. Puede ser un desplazamiento o la
            aplicación de una habilidad.

        Turno:
            Es una secuencia de jugadas realizadas por un grupo de personajes, normalmente 
            alternando a los dos equipos. los turnos se inician con la elección de los personajes 
            que van a participar en el turno, aunque en algunos modos de juego estos están 
            preestablecidos.

        Ronda:
            Es una secuencia de turnos en las que intervienen todos los personajes y que se 
            prolongan hasta que los personajes no pueden continuar, por haber perdido sus puntos de 
            acción o por haber perdido su vitalidad. Al inicio de la ronda, se recuperan los puntos 
            de acción de todos los personajes.

        Partida:
            Está formada por una secuencia de rondas. La partida termina cuando todos los personajes 
            de un equipo pierden su vitalidad. El otro equipo es el ganador.


        Modo de juego por pares
        --------------------------
        
        En este modo debe haber el mismo número de personajes en cada equipo.

        los turnos comienzan con los jugadores eligiendo un personaje de cada equipo. El primer 
        personaje en jugar es el que tiene más iniciativa, y en caso de tener la misma, se elige al 
        azar. A continuación se suceden las jugadas, alternando los dos personajes. 

        Cuando un personaje pierde sus puntos de acción o su vitalidad, el turno continua solo con 
        el otro. Y cuando lo pierden los dos, el turno termina.

        En el nuevo turno los jugador elige de nuevo a los dos personajes, evitando a los que han
        perdido sus puntos de acción o vitalidad.

        Cuando todos los personajes han perdido sus puntos de acción o su vitalidad, termina la 
        ronda.


        Modo de juego por equipos
        ----------------------------

        En este modo debe haber el mismo número de personajes en cada equipo.

        Al principio de la partida se establece un orden de juego para los personajes. Se toman los 
        personajes según aparecen en el tablero, de arriba a abajo, alternando los dos equipos. El 
        primero de los personajes será el que tenga más iniciativa de los dos primeros, eligiéndolos 
        al azar si coinciden. 
        
        Un turno consiste en una jugada de cada personaje, tomándolos en el orden de la lista y se 
        prolonga hasta que juega el último de los personajes de la lista. Si un personaje ha perdido 
        sus puntos de acción o su vitalidad, la jugada es nula y se pasa al siguiente personaje de 
        la lista. 
        
        Los turnos se suceden hasta que todos los personajes han perdido sus puntos de acción o su 
        vitalidad, momento en que se inicia el siguiente ronda.


        Modo de juego libre de doble jugada
        --------------------------------------

        En este modo debe haber el mismo número de personajes en cada equipo.

        Al principio de la partida se establece un equipo inicial, tomando el que tiene el personaje 
        con más iniciativa o eligiéndolo al azar si coinciden. A continuación se alternan turnos de 
        uno y otro equipo. 
        
        Al principio de cada turno, el jugador elije un personaje del equipo correspondiente. El 
        turno consiste en dos jugadas seguidas del mismo personaje, tras las cuales se pasa a el 
        siguiente turno, en la que el jugador elige un personaje del otro equipo. Si un personaje 
        ha perdido sus puntos de acción o su vitalidad, no puede ser elegido.

        Cuando todos los personajes de un equipo han perdido sus puntos de acción o vitalidad, 
        termina el turno (a pesar de que el otro equipo si pueda continuar).


        Programación
        ------------

        Para cambiar el modo del juego es suficiente con cambiar los identificadores usados en 
        las dos líneas de código siguientes. Debe aparecer una de estas tres parejas:

            · ModoJuegoPares       SucesosJuegoPares       
            · ModoJuegoEquipo      SucesosJuegoEquipo    
            · ModoJuegoLibreDoble  SucesosJuegoLibreDoble

        *******************************************************************************************/
        ModoJuegoPares    * modo    = new ModoJuegoPares {this};
        SucesosJuegoPares * sucesos = new SucesosJuegoPares {this, modo};
        /*******************************************************************************************
        /******************************************************************************************/
        //
        JuegoMesaBase::configura (sucesos, modo);
    }


    /*******************************************************************************************
    /*******************************************************************************************
        
    CONFIGURACIÓN DEL JUEGO
    Tercera sección - El tablero - Primera parte

    En esta sección se preparan los muros que aparecen en el tablero de juego.

    En el juego aparecen imágenes que muestran muros que ocupan algunas casillas hexagonales
    del tablero. Los jugadores no pueden situar a los personajes sobre los muros, ni 
    atravesarlos. Tampoco pueden realizar ataque a través de los muros (excepto si están 
    marcados como ataques indirectos).  

    Existen muchas posibilidades de diseño para los muros. Es posible que los muros se usen solo
    para delimitar un área del tablero, como ocurre con el ejemplo que aparece a continuación,
    llamado 'grafico_muros_area_central'. Otra posibilidad es diseñar una especie de laberinto
    con pasillos y cámaras, como en el ejemplo: 'grafico_muros_pasillos'. Aunque, lo más 
    aconsejable es crear unos muros que sean simplemente obstáculos para los ataques entre los 
    personajes.

    Especificación de los muros
    ---------------------------

    Para especificar los muros del tablero se debe crear un array similar al que aparece en los 
    ejemplos. Es preferible crear uno nuevo y mantener los ejemplos, en ese caso , la variable 
    debe tener un nombre diferente.

    El array está formado por 51 cadenas de caracteres, cada una de ellas de 145 caracteres de 
    longitud (mas el carácter \0 final, que no es visible). La mayor parte de los caracteres de 
    la cadena son espacios en blanco. En determinadas posiciones, y solo en ellas, puede haber: 
    o bien un guion, o bien la letra O mayúscula. 
        
    Esta disposición está pensada para indicar las posiciones de las celdas de la rejilla del 
    tablero. Al ser celdas hexagonales, no es posible usar una tabla formada por filas y 
    columnas, que, además, no daría una representación visual clara del tablero.

    Si se quiere que en una celda del tablero no aparezca un fragmento del muro, se debe 
    escribir un guion en la posición correspondiente del array. Si, por el contrario, se quiere 
    que si aparezca, se debe escribir la letra o mayúscula.

    El programa es muy sensible a la colocación de los caracteres en el array. Si uno de ellos
    está desplazado (por poco que sea), se producirá una excepción y el programa no se podrá 
    ejecutar.

    Programación
    ------------

    Véase la tercera parte de esta sección.
        
    *******************************************************************************************/
    static ActorTablero::GraficoMuros grafico_muros_vacio { 
//                                      1  1  1  1  1  1  1  1  1  1  2  2  2  2  2  2  2  2  2  2  3  3  3  3  3  3  3  3  3  3  4  4  4  4  4  4  4  4  4  4
//           1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9
//                                                                                                                11111111111111111111111111111111111111111111
//                     111111111122222222223333333333444444444455555555556666666666777777777788888888889999999999000000000011111111112222222222333333333344444  
//           0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",  
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -"};


    static ActorTablero::GraficoMuros grafico_muros_area_central { 
//                                      1  1  1  1  1  1  1  1  1  1  2  2  2  2  2  2  2  2  2  2  3  3  3  3  3  3  3  3  3  3  4  4  4  4  4  4  4  4  4  4
//           1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9
//                                                                                                                11111111111111111111111111111111111111111111
//                     111111111122222222223333333333444444444455555555556666666666777777777788888888889999999999000000000011111111112222222222333333333344444  
//           0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234
            "-     -     -     -     -     -     -     -     O     O     O     O     -     O     O     O     O     -     -     -     -     -     -     -     -",  
            "   -     -     -     -     -     -     -     O     O     O     O     -     -     O     O     O     O     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     O     O     O     O     -     -     -     O     O     O     O     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     O     O     O     O     -     -     -     -     O     O     O     O     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     O     O     O     O     -     -     -     -     -     O     O     O     O     -     -     -     -     -     -",
            "   -     -     -     -     -     O     O     O     O     -     -     -     -     -     -     O     O     O     O     -     -     -     -     -   ",
            "-     -     -     -     -     O     O     O     O     -     -     -     -     -     -     -     O     O     O     O     -     -     -     -     -",
            "   -     -     -     -     O     O     O     O     -     -     -     -     -     -     -     -     O     O     O     O     -     -     -     -   ",
            "-     -     -     -     O     O     O     O     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -     -     -",
            "   -     -     -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -     -   ",
            "-     -     -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -     -",
            "   -     -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -   ",
            "-     -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -",
            "   -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -   ",
            "-     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -",
            "   -     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     -   ",
            "-     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     -",
            "   -     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     -   ",
            "-     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     -",
            "   -     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     -   ",
            "-     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     -     -",
            "   -     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     -     -   ",
            "-     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     -     -     -",
            "   -     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     -",
            "   -     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     -   ",
            "-     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     -   ",
            "-     -     -     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     -",
            "   -     -     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     -   ",
            "-     -     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     -",
            "   -     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     -   ",
            "-     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     -",
            "   -     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     -   ",
            "-     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     -",
            "   -     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     -   ",
            "-     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -",
            "   -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -   ",
            "-     -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -",
            "   -     -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -   ",
            "-     -     -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -     -",
            "   -     -     -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -     -   ",
            "-     -     -     -     O     O     O     O     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -     -     -",
            "   -     -     -     -     O     O     O     O     -     -     -     -     -     -     -     -     O     O     O     O     -     -     -     -   ",
            "-     -     -     -     -     O     O     O     O     -     -     -     -     -     -     -     O     O     O     O     -     -     -     -     -",
            "   -     -     -     -     -     O     O     O     O     -     -     -     -     -     -     O     O     O     O     -     -     -     -     -   ",
            "-     -     -     -     -     -     O     O     O     O     -     -     -     -     -     O     O     O     O     -     -     -     -     -     -",
            "   -     -     -     -     -     -     O     O     O     O     -     -     -     -     O     O     O     O     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     O     O     O     O     -     -     -     O     O     O     O     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     O     O     O     O     -     -     O     O     O     O     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     O     O     O     O     -     O     O     O     O     -     -     -     -     -     -     -     -"};

    static ActorTablero::GraficoMuros grafico_muros{
        //                                      1  1  1  1  1  1  1  1  1  1  2  2  2  2  2  2  2  2  2  2  3  3  3  3  3  3  3  3  3  3  4  4  4  4  4  4  4  4  4  4
        //           1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9
        //                                                                                                                11111111111111111111111111111111111111111111
        //                     111111111122222222223333333333444444444455555555556666666666777777777788888888889999999999000000000011111111112222222222333333333344444  
        //           0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234
                    "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     -     -     O     O     -     -     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     O     O     O     -     -     O     O     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     O     O     -     -     -     -     O     O     O     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     O     O     -     -     -     -     -     -     -     O     O     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     O     O     -     -     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     O     -     -     -     O     O     O     -     -     -     -     O     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     O     -     O     -     -     -     -     O     -     -     -     -     O     -     -     -     -     -     -     -   ",
                    "-     -     -     -     O     -     -     O     -     -     -     -     O     -     -     -     -     O     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     O     -     -     -     -     O     -     -     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     O     -     -     O     O     -     O     -     -     O     -     -     -     O     -     -     -     -     -     -     -",
                    "   -     -     -     O     -     -     O     -     O     -     O     -     -     O     O     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     O     -     -     O     -     -     O     -     O     -     -     O     -     -     O     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     -     -     O     -     -     -     -     -     O     -     -     -     -     -     -   ",
                    "-     -     -     O     -     -     O     -     O     -     -     -     O     -     -     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     -     -     -     O     -     -     -     -     O     -     -     -     -     -     -   ",
                    "-     -     -     O     O     -     O     -     O     -     -     -     -     O     -     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     O     -     O     -     O     -     O     -     -     -     -     -     -     -     -     O     -     -     -     -     -     -   ",
                    "-     -     O     -     -     -     -     O     -     O     -     -     -     -     -     -     -     -     O     -     -     -     -     -     -",
                    "   -     -     -     -     O     -     -     -     -     O     -     -     -     -     -     -     -     -     O     -     -     -     -     -   ",
                    "-     -     O     -     -     -     -     -     -     -     O     -     -     -     O     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     O     -     -     -     -     -     O     -     -     O     -     -     -     -     O     -     -     -     -     -   ",
                    "-     -     O     -     -     -     -     -     -     -     -     O     -     O     -     -     -     -     O     -     -     -     -     -     -",
                    "   -     -     -     -     O     -     -     -     -     -     -     O     O     -     -     -     -     O     -     -     -     -     -     -   ",
                    "-     -     O     -     O     -     -     -     -     O     -     -     O     -     -     -     -     -     O     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     O     O     -     -     -     -     -     -     -     -     O     -     -     -     -     -   ",
                    "-     -     O     -     -     -     -     -     O     -     O     -     -     -     -     O     -     -     -     -     -     -     -     -     -",
                    "   -     -     O     -     -     -     -     O     -     -     O     -     -     -     O     -     -     -     O     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     -     -     O     -     -     -     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     O     -     -     -     -     O     -     -     -     O     -     -     O     -     -     O     O     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     -     -     -     O     -     O     -     -     -     O     -     -     -     -     -     -",
                    "   -     -     O     -     -     -     -     O     -     O     -     -     O     -     -     -     -     O     -     -     -     -     -     -   ",
                    "-     -     -     O     -     -     -     -     -     -     O     -     -     -     O     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     O     -     -     -     O     -     -     O     -     O     -     -     -     -     O     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     -     -     O     -     -     O     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     O     -     -     -     -     -     -     -     -     O     -     -     -     O     O     -     -     -     -     -     -   ",
                    "-     -     -     -     O     -     -     -     -     -     -     O     -     -     O     -     -     O     -     -     -     -     -     -     -",
                    "   -     -     -     -     O     -     -     -     -     -     -     -     O     -     O     -     O     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     O     -     -     -     -     -     O     -     -     -     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     O     -     O     -     -     -     O     -     -     O     -     O     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     O     O     O     -     -     -     O     -     O     O     O     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     O     -     O     -     -     -     -     -     -     O     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     O     -     O     O     -     O     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     O     O     O     O     O     -     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     -     O     -     -     O     -     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -" };

    /*******************************************************************************************
    /******************************************************************************************/


    void JuegoMesa::preparaTablero () {
        agregaTablero (new ActorTablero (this));
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Tercera sección - El tablero - Segunda parte

        En esta sección se configura el fondo del tablero. Para rellenar el fondo del tablero se usa
        un conjunto de imágenes colocadas en una rejilla (en filas y columnas), que ocupan toda la 
        superficie de la ventana.
        
        La imagen usada para rellenar el fondo del tablero no se usa directamente, se divide en 16
        partes, con 4 filas y 4 columnas, y continuación se colocan en el fondo del tablero, 
        seleccionado las partes de manera aleatoria. La razón de este funcionamiento es que se 
        consiguen evitar los patrones visuales que pueden aparecer si se colocan de forma uniforme.

        El tamaño de la imagen usada es de 128x128 px (y cada parte es de 32x32 px). 
        
        Programación
        ------------

        Para cambiar la imagen del fondo es suficiente con situar la imagen nueva en la carpeta de 
        activos del juego y cambiar el nombre en la línea de código siguiente. 
        
        Es conveniente usar un archivo de tipo PNG. Además se deben respetar las medidas indicadas
        previamente.

        *******************************************************************************************/
        tablero ()->ponArchivoBaldosas (carpeta_activos_juego + "fondo_concept.png");
        /*******************************************************************************************
        /******************************************************************************************/
        //
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Cuarta sección - Los personajes - Primera parte

        En esta sección se configuran los equipos del juego. 

        Cada equipo tiene un nombre y un escudo que aparece sobre la bandera en la parte superior de
        los paneles laterales del juego. En escudo se superpone a la bandera, sin taparla. El tamaño
        de las dos imágenes es de 40x40 px.
        
        Programación
        ------------

        Para cambiar los nombres de los equipos, se deben cambiar las dos líneas de código 
        siguientes. 
        
        Para cambiar las imágenes de los escudos es suficiente con situar las imágenes nuevas en la 
        carpeta de activos del juego y cambiar los nombres en las líneas de código siguiente. 
        
        Es conveniente usar archivos de tipo PNG que permiten la transparencia. Además se deben 
        respetar las medidas indicadas previamente.

        *******************************************************************************************/
        tablero ()->equipa (LadoTablero::Izquierda, L"Colmena Dorada",  carpeta_activos_juego + "BanderaColmenaDorada_1.png");
        tablero ()->equipa (LadoTablero::Derecha,   L"Corte de Seda y Veneno", carpeta_activos_juego + "Bandera_cortedeseda_1.png");
        /*******************************************************************************************
        /******************************************************************************************/
        //
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Tercera sección - El tablero - Tercera parte

        En esta sección se preparan los muros que aparecen en el tablero de juego. En la primera
        parte de la sección se preparan los muros que aparecen en el tablero, en esta tercera parte 
        se establecen los muros que usará el juego.

        Programación
        ------------

        Para cambiar los muros que aparecen en el tablero de juego es suficiente con cambiar el 
        nombre de la variable que contiene el array que los especifica en la línea de código que 
        aparece a continuación.
        
        *******************************************************************************************/
        tablero ()->situaMuros (grafico_muros);
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::preparaPersonajes () {
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Cuarta sección - Los personajes - Tercera parte

        En esta sección se configuran los personajes del juego. En la segunda parte se establecen
        las variables destinadas a almacenar las instancias que definen los personajes. En esta 
        parte se crean las instancias y se configuran.

        Las variable usan un nombre similar al nombre del personaje correspondiente. Las variables 
        son de tipo puntero, la creación de las instancias utiliza la palabra reservada 'new'. 

        Atributos
        ---------

        Se asignan los siguientes atributos a los personajes:

             a) Nombre: Asignado en la creación de la instancia en una cadena de caracteres. Deben 
                ser evitados los nombres compuestos y los nombres largos.

             b) Equipo: Se establece indicando si el personaje aparece en el panel de la izquierda o 
                en el panel de la derecha en el tablero de juego.

             c) Orden en equipo: Debe ser un índice a partir de 0 y consecutivo.

             d) Iniciativa: Establece que personaje actúa en primer lugar en algunas de las 
                circunstancias del juego. Debe ser positivo.

        Imágenes
        --------

        Cada personaje tiene un retrato con el que aparece en la pantalla del juego. El tamaño de la
        imagen usada es de 75x75 px. La imagen puede tener zonas transparentes, en cuyo caso aparece 
        sobre un fondo gris oscuro. El retrato se especifica en la creación de la instancia.

        De la misma forma, cada personaje tiene una imagen para la ficha con la que aparece en el 
        tablero. El tamaño de la imagen usada es de 31x31 px.

        Programación
        ------------

        Se deben modificar las lineas de código que aparecen a continuación.

        Se debe sustituir las listas de creaciones de instancias y las listas de llamadas a los 
        métodos por listas similares, obtenidas a partir de la lista de personajes diseñados para el 
        juego.

        Se deben cambiar los valores de los parámetros según los valores establecidos para cada 
        personaje en el diseño del juego.

        Para cambiar las imágenes de los retratos de los personajes es suficiente con situar las 
        imágenes nuevas en la carpeta de retratos del juego y cambiar los nombres de los archivos en 
        las llamadas al método correspondientes. Lo mismo ocurre con las imágenes de las fichas.
        
        Es conveniente usar archivos de tipo PNG que permiten la transparencia. Además se deben 
        respetar las medidas indicadas previamente.

        *******************************************************************************************/
        //
        AbejaReina       = new ActorPersonaje {this, LadoTablero::Izquierda, 0, L"Abeja Reina"};
        AbejaGuardia     = new ActorPersonaje {this, LadoTablero::Izquierda, 1, L"Guardiana"};
        AbejaExploradora = new ActorPersonaje {this, LadoTablero::Izquierda, 2, L"Exploradora"};
        AbejaNodriza     = new ActorPersonaje {this, LadoTablero::Izquierda, 3, L"Nodriza"};
        AranaReina       = new ActorPersonaje {this, LadoTablero::Derecha,   0, L"Reina Araña"};
        Avispa           = new ActorPersonaje {this, LadoTablero::Derecha,   1, L"Avispa"};
        Polilla          = new ActorPersonaje {this, LadoTablero::Derecha,   2, L"Polilla"};
        MoscaCarronera   = new ActorPersonaje {this, LadoTablero::Derecha,   3, L"Mosca"};
        //
        AbejaReina      ->ponArchivoRetrato (carpeta_retratos_juego + "PB_Bee01_Queen.png");
        AbejaGuardia    ->ponArchivoRetrato (carpeta_retratos_juego + "PB_Bee02_Guard.png");
        AbejaExploradora->ponArchivoRetrato (carpeta_retratos_juego + "PB_Bee03_Explorer.png");
        AbejaNodriza    ->ponArchivoRetrato (carpeta_retratos_juego + "PB_Bee04_Nodriza.png");
        AranaReina      ->ponArchivoRetrato (carpeta_retratos_juego + "PB_Spider01_Queen.png");
        Avispa          ->ponArchivoRetrato (carpeta_retratos_juego + "PB_Spider02_Avispa.png");
        Polilla         ->ponArchivoRetrato (carpeta_retratos_juego + "PB_Spider03_Polilla.png");
        MoscaCarronera  ->ponArchivoRetrato (carpeta_retratos_juego + "PB_Spider04_Mosca.png");
        //
        AbejaReina      ->ponArchivoFicha (carpeta_retratos_juego + "ficha_roja_reina.png");
        AbejaGuardia    ->ponArchivoFicha (carpeta_retratos_juego + "ficha_roja.png");
        AbejaExploradora->ponArchivoFicha (carpeta_retratos_juego + "ficha_roja.png");
        AbejaNodriza    ->ponArchivoFicha (carpeta_retratos_juego + "ficha_roja.png");
        AranaReina      ->ponArchivoFicha (carpeta_retratos_juego + "ficha_azul_reina.png");
        Avispa          ->ponArchivoFicha (carpeta_retratos_juego + "ficha_azul.png");
        Polilla         ->ponArchivoFicha (carpeta_retratos_juego + "ficha_azul.png");
        MoscaCarronera  ->ponArchivoFicha (carpeta_retratos_juego + "ficha_azul.png");
        //
        AbejaReina      ->ponIniciativa (20);
        AbejaGuardia    ->ponIniciativa (19);
        AbejaExploradora->ponIniciativa (18);
        AbejaNodriza    ->ponIniciativa (17);
        AranaReina      ->ponIniciativa (20);
        Avispa          ->ponIniciativa (19);
        Polilla         ->ponIniciativa (18);
        MoscaCarronera  ->ponIniciativa (17);
        //
        agregaPersonaje (AbejaReina);
        agregaPersonaje (AbejaGuardia);
        agregaPersonaje (AbejaExploradora);
        agregaPersonaje (AbejaNodriza);
        agregaPersonaje (AranaReina);
        agregaPersonaje (Avispa);
        agregaPersonaje (Polilla);
        agregaPersonaje (MoscaCarronera);
        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::preparaHabilidades () {
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Quinta sección - Las habilidades - Segunda parte

        En esta sección se configuran las habilidades compartidas por los personajes del juego. En 
        la primera parte se establecen las variables destinadas a almacenar las instancias que 
        definen las habilidades. En esta segunda parte se crean las instancias y se configuran.

        Las variable usan un nombre similar al nombre de la habilidad correspondiente. Las variables 
        son de tipo puntero, la creación de las instancias utiliza la palabra reservada 'new'. 

        Atributos
        ---------

        Se asignan los siguientes atributos a las habilidades:

             a) Nombre: Asignado en la creación de la instancia en una cadena de caracteres. 

             b) Enfoque: Indica a que esta enfocada la habilidad. Puede ser a un personaje, a un 
                área formada por varias celdas del tablero o hacia el mismo personaje que usa la 
                habilidad. 

             c) Acceso: Indica si el efecto de la habilidad puede atravesar muros. Puede ser directo,
                indirecto o ninguno.

             d) Antagonista: Indica a que grupo de personajes se dirige la habilidad. Puede ser a un
                oponente, a un aliado o a sí mismo.

             e) Descripción: Es un texto largo que describe la habilidad.

        Imágenes
        --------

        Cada habilidad tiene una imagen con el que aparece en la pantalla del juego. El tamaño de la
        imagen usada es de 50x50 px. La imagen puede tener zonas transparentes, en cuyo caso aparece 
        sobre una imagen de fondo, que puede ser distinta para cada habilidad o la misma para todas. 
        Las dos imágenes de cada habilidad se especifican la misma llamada a un método.

        Sonidos
        -------

        Cada habilidad tiene un sonido que suena cuando el personaje la usa. El sonido se carga de 
        un archivo de tipo 'wav', 'ogg' o 'flac', pero no 'mp3'. El tiempo de emisión del sonido
        debe ser corto (escasos segundos).

        Programación
        ------------

        Se deben modificar las lineas de código que aparecen a continuación.

        Se debe sustituir las listas de creaciones de instancias y las listas de llamadas a los 
        métodos por listas similares, obtenidas a partir de la lista de habilidades diseñadas para 
        el juego.

        Se deben cambiar los valores de los parámetros según los valores establecidos para cada 
        habilidad en el diseño del juego.

        Para cambiar las imágenes de las habilidad es suficiente con situar las imágenes nuevas en 
        la carpeta de habilidades del juego y cambiar los nombres en las llamadas al método 
        correspondiente. 
        
        Para cambiar los sonidos de las habilidad es suficiente con situar los sonidos nuevos en 
        la carpeta de sonidos del juego y cambiar los nombres en las llamadas al método 
        correspondiente. 
        
        Es conveniente usar archivos de tipo PNG que permiten la transparencia. Además se deben 
        respetar las medidas indicadas previamente.

        *******************************************************************************************/
        //
        // ── Abeja Reina ──────────────────────────────────────────────────────────
        mandatoRegio    = new Habilidad {
                L"Mandato Regio",
                EnfoqueHabilidad::personaje, AccesoHabilidad::indirecto, Antagonista::oponente};
        feromonasJalea  = new Habilidad {
                L"Feromonas de Jalea Real",
                EnfoqueHabilidad::area,      AccesoHabilidad::indirecto, Antagonista::aliado};
        decretoEnjambre = new Habilidad {
                L"Decreto de Enjambre",
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        inspiracion  = new Habilidad {
                L"Inspiración",
                EnfoqueHabilidad::equipo,    AccesoHabilidad::ninguno,   Antagonista::aliado};
        //
        mandatoRegio   ->ponDescripcion (
                L"La Reina dicta un mandato inapelable: el enemigo elegido ve multiplicado por 10 el coste de todas sus habilidades durante 1 turno. La Reina se queda con un único punto de acción.");
        feromonasJalea ->ponDescripcion (
                L"La Reina libera feromonas de jalea real que refuerzan la coraza de todos los aliados en el área, aumentando su defensa durante 2 turnos.");
        decretoEnjambre->ponDescripcion (
                L"La Reina lidera una carga en masa: ataca cuerpo a cuerpo y empuja al enemigo 3 casillas hacia atrás.");
        inspiracion ->ponDescripcion (
                L"La Reina inspira a todos sus aliados vivos: durante 3 turnos, el coste de todas sus habilidades se reduce en 1 punto de acción.");
        //
        mandatoRegio   ->ponArchivosImagenes (
                carpeta_habilids_juego + "AbejaReina/mandato.png",     carpeta_habilids_juego + "fondo_5.png");
        feromonasJalea ->ponArchivosImagenes (
                carpeta_habilids_juego + "AbejaReina/feromonas.png",   carpeta_habilids_juego + "fondo_5.png");
        decretoEnjambre->ponArchivosImagenes (
                carpeta_habilids_juego + "AbejaReina/decreto.png",     carpeta_habilids_juego + "fondo_5.png");
        inspiracion ->ponArchivosImagenes (
                carpeta_habilids_juego + "AbejaReina/inspiracion.png", carpeta_habilids_juego + "fondo_5.png");
        //
        mandatoRegio   ->ponArchivoSonido (carpeta_sonidos_juego + "Colmena/Ataque_Ranged_Colmena.wav");
        feromonasJalea ->ponArchivoSonido (carpeta_sonidos_juego + "Colmena/Defensa_Colmena.wav");
        decretoEnjambre->ponArchivoSonido (carpeta_sonidos_juego + "Colmena/Ataque_melee_Colmena.wav");
        inspiracion ->ponArchivoSonido (carpeta_sonidos_juego + "Colmena/Defensa_Colmena.wav");
        //
        agregaHabilidad (mandatoRegio);
        agregaHabilidad (feromonasJalea);
        agregaHabilidad (decretoEnjambre);
        agregaHabilidad (inspiracion);
        // ── Abeja Guardia ────────────────────────────────────────────────────────
        escudoQuitina        = new Habilidad {
                L"Escudo de Quitina",
                EnfoqueHabilidad::si_mismo,  AccesoHabilidad::ninguno,   Antagonista::si_mismo};
        ataqueTronador       = new Habilidad {
                L"Ataque Tronador",
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        embestidaTerritorial = new Habilidad {
                L"Embestida Territorial",
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        aguijonCadena        = new Habilidad {
                L"Aguijón Cadena",
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        //
        escudoQuitina       ->ponDescripcion (
                L"La Guardiana endurece su exoesqueleto de quitina: obtiene +35 de defensa en todos los tipos durante 2 turnos, convirtiéndose en un muro casi infranqueable.");
        ataqueTronador      ->ponDescripcion (
                L"La Guardiana descarga un golpe devastador con toda su masa: ataque cuerpo a cuerpo de alto daño que sacude al enemigo.");
        embestidaTerritorial->ponDescripcion (
                L"La Guardiana carga como una apisonadora: ataque cuerpo a cuerpo potente que empuja al enemigo 3 casillas en dirección contraria al atacante.");
        aguijonCadena       ->ponDescripcion (
                L"La Guardiana lanza su aguijón encadenado: ataque a distancia de poco daño que arrastra al objetivo hasta 3 casillas hacia ella. No arrastra si el ataque falla.");
        //
        escudoQuitina       ->ponArchivosImagenes (
                carpeta_habilids_juego + "AbejaGuardiana/escudo.png",    carpeta_habilids_juego + "fondo_5.png");
        ataqueTronador      ->ponArchivosImagenes (
                carpeta_habilids_juego + "AbejaGuardiana/tronador.png",  carpeta_habilids_juego + "fondo_5.png");
        embestidaTerritorial->ponArchivosImagenes (
                carpeta_habilids_juego + "AbejaGuardiana/embestida.png", carpeta_habilids_juego + "fondo_5.png");
        aguijonCadena       ->ponArchivosImagenes (
                carpeta_habilids_juego + "AbejaGuardiana/cadena.png",    carpeta_habilids_juego + "fondo_5.png");
        //
        escudoQuitina       ->ponArchivoSonido (carpeta_sonidos_juego + "Colmena/Defensa_Colmena.wav");
        ataqueTronador      ->ponArchivoSonido (carpeta_sonidos_juego + "Colmena/Ataque_melee_Colmena.wav");
        embestidaTerritorial->ponArchivoSonido (carpeta_sonidos_juego + "Colmena/Ataque_melee_Colmena.wav");
        aguijonCadena       ->ponArchivoSonido (carpeta_sonidos_juego + "Colmena/Ataque_Ranged_Colmena.wav");
        //
        agregaHabilidad (escudoQuitina);
        agregaHabilidad (ataqueTronador);
        agregaHabilidad (embestidaTerritorial);
        agregaHabilidad (aguijonCadena);
        // ── Reina Araña ──────────────────────────────────────────────────────────
        redDominio        = new Habilidad {
                L"Red de Dominio",
                EnfoqueHabilidad::area,      AccesoHabilidad::indirecto, Antagonista::oponente};
        hiloTitiritero    = new Habilidad {
                L"Hilo del Titiritero",
                EnfoqueHabilidad::personaje, AccesoHabilidad::indirecto, Antagonista::oponente};
        mordeduraVenenosa = new Habilidad {
                L"Mordedura Venenosa",
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        armadurasSeda     = new Habilidad {
                L"Armaduras de Seda",
                EnfoqueHabilidad::area,      AccesoHabilidad::directo,   Antagonista::aliado};
        //
        redDominio       ->ponDescripcion (
                L"La Araña teje una red invisible que enturbia la mente de los enemigos cercanos: todos los que estén en el área ven triplicado el coste de sus habilidades durante 2 turnos.");
        hiloTitiritero   ->ponDescripcion (
                L"La Araña clava su hilo telepático en un enemigo. El jugador rival controlará a ese personaje durante el resto de la ronda, pero gastar todos los PA de la Araña. El afectado actúa normalmente.");
        mordeduraVenenosa->ponDescripcion (
                L"La Araña muerde a su objetivo inyectando un veneno paralizante: daño físico inmediato más 10 puntos de veneno por turno durante 3 turnos.");
        armadurasSeda    ->ponDescripcion (
                L"La Araña envuelve a sus aliados cercanos con hilos de seda endurecida, aumentando la defensa de todos ellos en 20 puntos durante 2 turnos.");
        //
        redDominio       ->ponArchivosImagenes (
                carpeta_habilids_juego + "AranaReina/red.png",        carpeta_habilids_juego + "fondo_5.png");
        hiloTitiritero   ->ponArchivosImagenes (
                carpeta_habilids_juego + "AranaReina/titiritero.png", carpeta_habilids_juego + "fondo_5.png");
        mordeduraVenenosa->ponArchivosImagenes (
                carpeta_habilids_juego + "AranaReina/mordedura.png",  carpeta_habilids_juego + "fondo_5.png");
        armadurasSeda    ->ponArchivosImagenes (
                carpeta_habilids_juego + "AranaReina/seda.png",       carpeta_habilids_juego + "fondo_5.png");
        //
        redDominio       ->ponArchivoSonido (carpeta_sonidos_juego + "Corte/Ataque_ranged_Corte.wav");
        hiloTitiritero   ->ponArchivoSonido (carpeta_sonidos_juego + "Corte/Ataque_ranged_Corte.wav");
        mordeduraVenenosa->ponArchivoSonido (carpeta_sonidos_juego + "Corte/Ataque_melee_Corte.wav");
        armadurasSeda    ->ponArchivoSonido (carpeta_sonidos_juego + "Corte/Defensa_Corte.wav");
        //
        agregaHabilidad (redDominio);
        agregaHabilidad (hiloTitiritero);
        agregaHabilidad (mordeduraVenenosa);
        agregaHabilidad (armadurasSeda);
        // ── Abeja Exploradora ────────────────────────────────────────────────────
        vientoAscendente       = new Habilidad {
                L"Viento Ascendente",
                EnfoqueHabilidad::personaje, AccesoHabilidad::indirecto, Antagonista::aliado};
        turbulenciaDebilitadora = new Habilidad {
                L"Turbulencia Debilitadora",
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        reflujoPolen           = new Habilidad {
                L"Reflujo de Polen",
                EnfoqueHabilidad::area,      AccesoHabilidad::indirecto, Antagonista::oponente};
        alasResonantes         = new Habilidad {
                L"Alas Resonantes",
                EnfoqueHabilidad::area,      AccesoHabilidad::directo,   Antagonista::oponente};
        //
        vientoAscendente       ->ponDescripcion (
                L"La Exploradora canaliza una corriente de aire cálido que envuelve a un aliado, aligerando su mente y reduciendo el coste de sus habilidades durante 3 turnos.");
        turbulenciaDebilitadora->ponDescripcion (
                L"La Exploradora impacta al enemigo con una ráfaga de turbulencias: golpe melee moderado que además perturba su musculatura, reduciendo su ataque durante 2 turnos.");
        reflujoPolen           ->ponDescripcion (
                L"La Exploradora lanza una nube de polen paralizante sobre una casilla vacía a distancia, bloqueándola durante 3 turnos. Si hay un enemigo en esa casilla, también sufre -15 de ataque durante 2 turnos.");
        alasResonantes         ->ponDescripcion (
                L"La Exploradora bate sus alas a máxima frecuencia creando una onda de choque que golpea a todos los enemigos en un área amplia. Devastadora pero agotadora: consume la mayor parte de sus puntos de acción.");
        //
        vientoAscendente       ->ponArchivosImagenes (
                carpeta_habilids_juego + "AbejaExploradora/viento.png",      carpeta_habilids_juego + "fondo_5.png");
        turbulenciaDebilitadora->ponArchivosImagenes (
                carpeta_habilids_juego + "AbejaExploradora/turbulencia.png", carpeta_habilids_juego + "fondo_5.png");
        reflujoPolen           ->ponArchivosImagenes (
                carpeta_habilids_juego + "AbejaExploradora/reflujo.png",     carpeta_habilids_juego + "fondo_5.png");
        alasResonantes         ->ponArchivosImagenes (
                carpeta_habilids_juego + "AbejaExploradora/alas.png",        carpeta_habilids_juego + "fondo_5.png");
        //
        vientoAscendente       ->ponArchivoSonido (carpeta_sonidos_juego + "Colmena/Defensa_Colmena.wav");
        turbulenciaDebilitadora->ponArchivoSonido (carpeta_sonidos_juego + "Colmena/Ataque_melee_Colmena.wav");
        reflujoPolen           ->ponArchivoSonido (carpeta_sonidos_juego + "Colmena/Ataque_Ranged_Colmena.wav");
        alasResonantes         ->ponArchivoSonido (carpeta_sonidos_juego + "Colmena/Ataque_Ranged_Colmena.wav");
        //
        agregaHabilidad (vientoAscendente);
        agregaHabilidad (turbulenciaDebilitadora);
        agregaHabilidad (reflujoPolen);
        agregaHabilidad (alasResonantes);
        // ── Avispa Asesina ───────────────────────────────────────────────────────
        cargaAguijon       = new Habilidad {
                L"Carga de Aguijón",
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        precisionAguijon   = new Habilidad {
                L"Precisión de Aguijón",
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        frenesi            = new Habilidad {
                L"Frenesí", 
                EnfoqueHabilidad::si_mismo,  AccesoHabilidad::ninguno,   Antagonista::si_mismo};
        desgarrarFormacion = new Habilidad {
                L"Desgarrar Formación",
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        //
        cargaAguijon      ->ponDescripcion (
                L"La Avispa se lanza como una bala hacia el enemigo elegido. Si consigue ponerse adyacente a él (sin obstáculos de por medio), le clava el aguijón con toda su inercia. Si algo bloquea la carga, el impacto no se produce.");
        precisionAguijon  ->ponDescripcion (
                L"La Avispa elige el momento exacto: cuando su objetivo está gravemente herido (menos del 30% de vitalidad), el aguijón encuentra siempre un punto vital, garantizando un golpe crítico.");
        frenesi           ->ponDescripcion (
                L"La Avispa entra en estado de frenesí depredador: aumenta su ataque y su defensa durante 2 turnos, volviéndose más peligrosa y difícil de detener.");
        desgarrarFormacion->ponDescripcion (
                L"La Avispa rasga la coraza del enemigo con sus mandíbulas, infligiendo poco daño pero reduciendo su defensa durante 2 turnos y dejándolo expuesto a los ataques siguientes.");
        //
        cargaAguijon      ->ponArchivosImagenes (
                carpeta_habilids_juego + "AvispaAsesina/carga.png",     carpeta_habilids_juego + "fondo_5.png");
        precisionAguijon  ->ponArchivosImagenes (
                carpeta_habilids_juego + "AvispaAsesina/precision.png", carpeta_habilids_juego + "fondo_5.png");
        frenesi           ->ponArchivosImagenes (
                carpeta_habilids_juego + "AvispaAsesina/frenesi.png",   carpeta_habilids_juego + "fondo_5.png");
        desgarrarFormacion->ponArchivosImagenes (
                carpeta_habilids_juego + "AvispaAsesina/desgarrar.png", carpeta_habilids_juego + "fondo_5.png");
        //
        cargaAguijon      ->ponArchivoSonido (carpeta_sonidos_juego + "Corte/Ataque_melee_Corte.wav");
        precisionAguijon  ->ponArchivoSonido (carpeta_sonidos_juego + "Corte/Ataque_melee_Corte.wav");
        frenesi           ->ponArchivoSonido (carpeta_sonidos_juego + "Corte/Defensa_Corte.wav");
        desgarrarFormacion->ponArchivoSonido (carpeta_sonidos_juego + "Corte/Ataque_melee_Corte.wav");
        //
        agregaHabilidad (cargaAguijon);
        agregaHabilidad (precisionAguijon);
        agregaHabilidad (frenesi);
        agregaHabilidad (desgarrarFormacion);
        // ── Abeja Nodriza ────────────────────────────────────────────────────────
        jaleaRestauradora  = new Habilidad {
                L"Jalea Restauradora",
                EnfoqueHabilidad::personaje, AccesoHabilidad::indirecto, Antagonista::aliado};
        mantoMiel          = new Habilidad {
                L"Manto de Miel",
                EnfoqueHabilidad::personaje, AccesoHabilidad::indirecto, Antagonista::aliado};
        cuidadosIntensivos = new Habilidad {
                L"Cuidados Intensivos",
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::aliado};
        absorcionCera      = new Habilidad {
                L"Absorción de Cera",
                EnfoqueHabilidad::equipo,    AccesoHabilidad::ninguno,   Antagonista::aliado};
        //
        jaleaRestauradora ->ponDescripcion (
                L"La Nodriza segrega jalea real a distancia, restaurando una cantidad moderada de vitalidad a un aliado sin necesidad de contacto.");
        mantoMiel         ->ponDescripcion (
                L"La Nodriza recubre a un aliado con una capa de miel protectora, aumentando su defensa durante varios turnos.");
        cuidadosIntensivos->ponDescripcion (
                L"La Nodriza atiende en distancia de contacto a un aliado gravemente herido: curación intensa y limpieza de todos sus estados negativos activos.");
        absorcionCera     ->ponDescripcion (
                L"La Nodriza absorbe la cera solidificada de los obstáculos creados en combate. Por cada obstáculo destruido, canaliza energía vital hacia todos sus aliados.");
        //
        jaleaRestauradora ->ponArchivosImagenes (
                carpeta_habilids_juego + "AbejaNodriza/gota.png",      carpeta_habilids_juego + "fondo_5.png");
        mantoMiel         ->ponArchivosImagenes (
                carpeta_habilids_juego + "AbejaNodriza/manto.png",     carpeta_habilids_juego + "fondo_5.png");
        cuidadosIntensivos->ponArchivosImagenes (
                carpeta_habilids_juego + "AbejaNodriza/cuidados.png",  carpeta_habilids_juego + "fondo_5.png");
        absorcionCera     ->ponArchivosImagenes (
                carpeta_habilids_juego + "AbejaNodriza/absorcion.png", carpeta_habilids_juego + "fondo_5.png");
        //
        jaleaRestauradora ->ponArchivoSonido (carpeta_sonidos_juego + "Colmena/Curar_Colmena.wav");
        mantoMiel         ->ponArchivoSonido (carpeta_sonidos_juego + "Colmena/Defensa_Colmena.wav");
        cuidadosIntensivos->ponArchivoSonido (carpeta_sonidos_juego + "Colmena/Curar_Colmena.wav");
        absorcionCera     ->ponArchivoSonido (carpeta_sonidos_juego + "Colmena/Curar_Colmena.wav");
        //
        agregaHabilidad (jaleaRestauradora);
        agregaHabilidad (mantoMiel);
        agregaHabilidad (cuidadosIntensivos);
        agregaHabilidad (absorcionCera);
        // ── Mosca Carroñera ──────────────────────────────────────────────────────
        cargaIlusoria   = new Habilidad {
                L"Carga Ilusoria",
                EnfoqueHabilidad::area,      AccesoHabilidad::indirecto, Antagonista::oponente};
        ojosCarronero   = new Habilidad {
                L"Ojos del Carroñero",
                EnfoqueHabilidad::personaje, AccesoHabilidad::indirecto, Antagonista::oponente};
        arrastreVictima = new Habilidad {
                L"Arrastre de Víctima",
                EnfoqueHabilidad::area,      AccesoHabilidad::directo,   Antagonista::aliado};
        huidaCobarde    = new Habilidad {
                L"Huida Cobarde",
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        //
        cargaIlusoria  ->ponDescripcion (
                L"La Mosca lanza un embate fantasmal a distancia sobre una única celda. Puede usarse sin línea de visión directa.");
        ojosCarronero  ->ponDescripcion (
                L"La Mosca detecta los puntos débiles del objetivo y erosiona su armadura, reduciendo drásticamente su defensa durante varios turnos.");
        arrastreVictima->ponDescripcion (
                L"La Mosca se lanza sobre el enemigo adyacente y lo arrastra consigo al retroceder, desplazando a ambos.");
        huidaCobarde   ->ponDescripcion (
                L"La Mosca distrae a un enemigo cercano, reduciéndole el ataque, y lo empuja para escapar de su alcance.");
        //
        cargaIlusoria  ->ponArchivosImagenes (
                carpeta_habilids_juego + "MoscaCarronera/cargailusoria.png", carpeta_habilids_juego + "fondo_5.png");
        ojosCarronero  ->ponArchivosImagenes (
                carpeta_habilids_juego + "MoscaCarronera/ojos.png",          carpeta_habilids_juego + "fondo_5.png");
        arrastreVictima->ponArchivosImagenes (
                carpeta_habilids_juego + "MoscaCarronera/arrastre.png",      carpeta_habilids_juego + "fondo_5.png");
        huidaCobarde   ->ponArchivosImagenes (
                carpeta_habilids_juego + "MoscaCarronera/huida.png",         carpeta_habilids_juego + "fondo_5.png");
        //
        cargaIlusoria  ->ponArchivoSonido (carpeta_sonidos_juego + "Corte/Ataque_ranged_Corte.wav");
        ojosCarronero  ->ponArchivoSonido (carpeta_sonidos_juego + "Corte/Ataque_ranged_Corte.wav");
        arrastreVictima->ponArchivoSonido (carpeta_sonidos_juego + "Corte/Movimiento_Corte.wav");
        huidaCobarde   ->ponArchivoSonido (carpeta_sonidos_juego + "Corte/Movimiento_Corte.wav");
        //
        agregaHabilidad (cargaIlusoria);
        agregaHabilidad (ojosCarronero);
        agregaHabilidad (arrastreVictima);
        agregaHabilidad (huidaCobarde);
        // ── Polilla ──────────────────────────────────────────────────────────────
        brebajeCorrupto = new Habilidad {
                L"Brebaje Corrupto",
                EnfoqueHabilidad::area,      AccesoHabilidad::indirecto, Antagonista::oponente};
        unguentoCera    = new Habilidad {
                L"Ungüento de Cera",
                EnfoqueHabilidad::personaje, AccesoHabilidad::indirecto, Antagonista::aliado};
        ceraPegajosa    = new Habilidad {
                L"Cera Pegajosa",
                EnfoqueHabilidad::area,      AccesoHabilidad::indirecto, Antagonista::oponente};
        vapores         = new Habilidad {
                L"Vapores",
                EnfoqueHabilidad::area,      AccesoHabilidad::indirecto, Antagonista::oponente};
        //
        brebajeCorrupto->ponDescripcion (
                L"La Polilla rocía un brebaje corrosivo en área: reduce la defensa de todos los enemigos alcanzados durante 3 rondas.");
        unguentoCera   ->ponDescripcion (
                L"La Polilla aplica un ungüento de cera regeneradora a un aliado a distancia, restaurando una cantidad moderada de vitalidad.");
        ceraPegajosa   ->ponDescripcion (
                L"La Polilla segrega cera pegajosa sobre una casilla vacía a distancia, bloqueándola durante 3 rondas. Si hay un enemigo en esa casilla, también sufre -15 de ataque durante 2 turnos.");
        vapores        ->ponDescripcion (
                L"La Polilla libera una nube de vapores tóxicos que daña a todos los enemigos del área y, a la vez, estimula el instinto de caza de sus aliados, aumentando su ataque.");
        //
        brebajeCorrupto->ponArchivosImagenes (
                carpeta_habilids_juego + "Polilla/brebaje.png",  carpeta_habilids_juego + "fondo_5.png");
        unguentoCera   ->ponArchivosImagenes (
                carpeta_habilids_juego + "Polilla/unguento.png", carpeta_habilids_juego + "fondo_5.png");
        ceraPegajosa   ->ponArchivosImagenes (
                carpeta_habilids_juego + "Polilla/cera.png",     carpeta_habilids_juego + "fondo_5.png");
        vapores        ->ponArchivosImagenes (
                carpeta_habilids_juego + "Polilla/vapores.png",  carpeta_habilids_juego + "fondo_5.png");
        //
        brebajeCorrupto->ponArchivoSonido (carpeta_sonidos_juego + "Corte/Ataque_ranged_Corte.wav");
        unguentoCera   ->ponArchivoSonido (carpeta_sonidos_juego + "Corte/Curar_Corte.wav");
        ceraPegajosa   ->ponArchivoSonido (carpeta_sonidos_juego + "Corte/Ataque_ranged_Corte.wav");
        vapores        ->ponArchivoSonido (carpeta_sonidos_juego + "Corte/Ataque_ranged_Corte.wav");
        //
        agregaHabilidad (brebajeCorrupto);
        agregaHabilidad (unguentoCera);
        agregaHabilidad (ceraPegajosa);
        agregaHabilidad (vapores);
        // ── Habilidades placeholder ──────────────────────────────────────────────
        ataqueEspadaNormal   = new Habilidad {
                L"Ataque cuerpo a cuerpo normal",
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        ataqueArco           = new Habilidad {
                L"Ataque a distancia normal",     
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        ataqueEspadaPoderoso = new Habilidad {
                L"Ataque poderoso",               
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        defensaFerrea        = new Habilidad {
                L"Defensa férrea",                
                EnfoqueHabilidad::si_mismo,  AccesoHabilidad::ninguno,   Antagonista::si_mismo};
        curacionSimple       = new Habilidad {
                L"Curación",                      
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::aliado};
        curacionGrupo        = new Habilidad {
                L"Curación en grupo",             
                EnfoqueHabilidad::area,      AccesoHabilidad::directo,   Antagonista::aliado};
        proyectilMagico      = new Habilidad {
                L"Proyectil mágico",              
                EnfoqueHabilidad::personaje, AccesoHabilidad::indirecto, Antagonista::oponente};
        bolaFuego            = new Habilidad {
                L"Bola de fuego",
                EnfoqueHabilidad::area,      AccesoHabilidad::directo,   Antagonista::oponente};
        venenoMortal         = new Habilidad {
                L"Veneno mortal",
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        //
        ataqueEspadaNormal  ->ponDescripcion (
                L"El personaje usa su espada para atacar a un enemigo que se encuentra en una casilla próxima.");
        ataqueArco          ->ponDescripcion (
                L"El personaje usa su arco para atacar a un enemigo que se encuentra en una casilla próxima.");
        ataqueEspadaPoderoso->ponDescripcion (
                L"El personaje blande su espada con fuerza para atacar a un enemigo que se encuentra en una casilla próxima.");
        defensaFerrea       ->ponDescripcion (
                L"El personaje aumenta su defensa hasta su próximo ronda.");
        curacionSimple      ->ponDescripcion (
                L"El personaje canaliza poder divino para sanar a un aliado.");
        curacionGrupo      ->ponDescripcion (
                L"El personaje canaliza poder divino para sanar a todos los personajes en un área.");
        proyectilMagico     ->ponDescripcion (
                L"El personaje acumula energía mágica y la lanza contra un enemigo.");
        bolaFuego           ->ponDescripcion (
                L"El personaje acumula energía mágica y la lanza contra un grupo de enemigos.");
        venenoMortal        ->ponDescripcion (
                L"La polilla inocula un veneno paralizante: inflige daño inmediato y envenena al objetivo durante 3 turnos.");
        //
        ataqueEspadaNormal  ->ponArchivosImagenes (
                carpeta_habilids_juego + "espada.png",          carpeta_habilids_juego + "fondo_5.png");
        ataqueArco          ->ponArchivosImagenes (
                carpeta_habilids_juego + "arco_flecha.png",     carpeta_habilids_juego + "fondo_5.png");
        ataqueEspadaPoderoso->ponArchivosImagenes (
                carpeta_habilids_juego + "espada_poderosa.png", carpeta_habilids_juego + "fondo_5.png");
        defensaFerrea       ->ponArchivosImagenes (
                carpeta_habilids_juego + "escudo.png",          carpeta_habilids_juego + "fondo_5.png");
        curacionSimple      ->ponArchivosImagenes (
                carpeta_habilids_juego + "vela.png",            carpeta_habilids_juego + "fondo_5.png");
        curacionGrupo       ->ponArchivosImagenes (
                carpeta_habilids_juego + "vela_triple.png",     carpeta_habilids_juego + "fondo_5.png");
        proyectilMagico     ->ponArchivosImagenes (
                carpeta_habilids_juego + "cristales.png",       carpeta_habilids_juego + "fondo_5.png");
        bolaFuego           ->ponArchivosImagenes (
                carpeta_habilids_juego + "bola_fuego.png",      carpeta_habilids_juego + "fondo_5.png");
        venenoMortal        ->ponArchivosImagenes (
                carpeta_habilids_juego + "cristales.png",        carpeta_habilids_juego + "fondo_5.png");
        //
        ataqueEspadaNormal  ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        ataqueArco          ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        ataqueEspadaPoderoso->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        defensaFerrea       ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        curacionSimple      ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        curacionGrupo       ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        proyectilMagico     ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        bolaFuego           ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        venenoMortal        ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        //
        agregaHabilidad (ataqueEspadaNormal);
        agregaHabilidad (ataqueArco);
        agregaHabilidad (ataqueEspadaPoderoso);
        agregaHabilidad (defensaFerrea );
        agregaHabilidad (curacionSimple);
        agregaHabilidad (curacionGrupo );
        agregaHabilidad (proyectilMagico );
        agregaHabilidad (bolaFuego );
        agregaHabilidad (venenoMortal);
        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::preparaTiposEstadisticas () {
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Sexta sección - Los tipos de ataque, defensa y daño (estadísticas) - Segunda parte

        En esta sección se configuran los tipos de ataque, defensa y daño del juego. Estos tipos  
        son usados para establecer las estadisticas del juego en los personajes y en las habilidades. 
        En la primera parte se establecen las variables destinadas a almacenar las instancias que 
        definen los tipos de ataque, defensa y daño. En esta parte se crean las instancias y se 
        configuran.

        Las variable usan un nombre similar al nombre de los tipos correspondiente. Las variables 
        son de tipo puntero, la creación de las instancias utiliza la palabra reservada 'new'. 

        Atributos
        ---------

        Se asignan los siguientes atributos a los tipos:

             a) Descripción: Asignado en la creación de la instancia en una cadena de caracteres. 
                Deben ser cortos y deben comenzar con la palabra 'Ataque', 'Defensa' o 'Daño'.

        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se debe sustituir las listas de creaciones de instancias por listas similares, obtenidas a 
        partir de la lista de tipos diseñados para el juego. El nombre de la clase (por ejemplo 
        'TipoAtaque' para los ataques) establece si es un tipo de ataque, de defensa o de daño.

        Se deben cambiar los valores de los parámetros según los valores establecidos para cada 
        tipo en el diseño del juego.

        *******************************************************************************************/
        //
        ataqueCuerpoACuerpo  = new TipoAtaque  {L"Ataque cuerpo a cuerpo"};
        ataqueADistancia     = new TipoAtaque  {L"Ataque a distancia"};
        ataqueMagico         = new TipoAtaque  {L"Ataque mágico"};
        defensaCuerpoACuerpo = new TipoDefensa {L"Defensa cuerpo a cuerpo"};
        defensaADistancia    = new TipoDefensa {L"Defensa a distancia"};
        defensaMagica        = new TipoDefensa {L"Defensa mágica"};
        danoFisico           = new TipoDano    {L"Daño físico"};
        danoMagico           = new TipoDano    {L"Daño mágico"};
        //
        agregaAtaque  (ataqueCuerpoACuerpo );
        agregaAtaque  (ataqueADistancia);
        agregaAtaque  (ataqueMagico);
        agregaDefensa (defensaCuerpoACuerpo);
        agregaDefensa (defensaADistancia );
        agregaDefensa (defensaMagica );
        agregaDano    (danoFisico);
        agregaDano    (danoMagico);
        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::agregaHabilidadesPersonajes () {
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Octava sección - Las habilidades de los personajes

        En esta sección se establecen que habilidades que tiene cada personajes del juego.

        Cada personaje debe tener entre 1 y 10 habilidades.

        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se deben sustituir las listas de habilidades de cada personaje por listas similares, 
        obtenidas a partir del diseño del juego.

        *******************************************************************************************/
        //
        AbejaReina      ->agregaHabilidad (mandatoRegio);
        AbejaReina      ->agregaHabilidad (feromonasJalea);
        AbejaReina      ->agregaHabilidad (decretoEnjambre);
        AbejaReina      ->agregaHabilidad (inspiracion);
        //
        AbejaGuardia    ->agregaHabilidad (escudoQuitina);
        AbejaGuardia    ->agregaHabilidad (ataqueTronador);
        AbejaGuardia    ->agregaHabilidad (embestidaTerritorial);
        AbejaGuardia    ->agregaHabilidad (aguijonCadena);
        //
        AbejaExploradora->agregaHabilidad (vientoAscendente);
        AbejaExploradora->agregaHabilidad (turbulenciaDebilitadora);
        AbejaExploradora->agregaHabilidad (reflujoPolen);
        AbejaExploradora->agregaHabilidad (alasResonantes);
        //
        AranaReina      ->agregaHabilidad (redDominio);
        AranaReina      ->agregaHabilidad (hiloTitiritero);
        AranaReina      ->agregaHabilidad (mordeduraVenenosa);
        AranaReina      ->agregaHabilidad (armadurasSeda);
        //
        Avispa          ->agregaHabilidad (cargaAguijon);
        Avispa          ->agregaHabilidad (precisionAguijon);
        Avispa          ->agregaHabilidad (frenesi);
        Avispa          ->agregaHabilidad (desgarrarFormacion);
        //
        AbejaNodriza->agregaHabilidad (jaleaRestauradora);
        AbejaNodriza->agregaHabilidad (mantoMiel);
        AbejaNodriza->agregaHabilidad (cuidadosIntensivos);
        AbejaNodriza->agregaHabilidad (absorcionCera);
        //
        Polilla    ->agregaHabilidad (brebajeCorrupto);
        Polilla    ->agregaHabilidad (unguentoCera);
        Polilla    ->agregaHabilidad (ceraPegajosa);
        Polilla    ->agregaHabilidad (vapores);
        //
        MoscaCarronera ->agregaHabilidad (cargaIlusoria);
        MoscaCarronera ->agregaHabilidad (ojosCarronero);
        MoscaCarronera ->agregaHabilidad (arrastreVictima);
        MoscaCarronera ->agregaHabilidad (huidaCobarde);
        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::agregaEstadisticasHabilidades () {
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Novena sección - Las estadísticas de las habilidades

        En esta sección se establecen diversos atributos y valores para las habilidades del juego,
        incluyendo las estadisticas del juego.

        Estadísticas
        ------------

        Las habilidades se clasifican en habilidades de ataque, de curación y auto-aplicada. Esta 
        clasificación se establece mediante el atributo 'Antagonista' de la habilidad. 

            - Si 'Antagonista' es 'oponente' la habilidad es de ataque. El ataque puede afectar a un 
              personaje o a los personajes de un área del tablero.
            - Si 'Antagonista' es 'aliado' la habilidad es de curación. La curación puede afectar a 
              un personaje o a los personajes de un área del tablero.
            - Si 'Antagonista' es 'si_mismo' la habilidad es auto-aplicada.

        Los valores que se establecen para las habilidades son:

             a) Coste: Es el número de puntos de acción que se gastan al usar la habilidad.

             b) Alcance: En las habilidades de ataque y curación debe estar establecido el alcance 
                de la habilidad. La habilidad solo se puede usar si el alcance lo permite. Es un 
                valor que indica un número de casillas del tablero y debe ser positivo.

             c) Radio de ara de alcance: En las habilidades de ataque y curación que afectan a un 
                área del tablero, debe estar establecido el radio del área. Es un valor que indica 
                un número de casillas del tablero y debe ser positivo. 

             d) Tipo de ataque: Cuando una habilidad es de ataque, debe tener establecido un tipo de 
                ataque. El tipo de ataque se usa en el personaje atacante.

             e) Tipo de defensa: Cuando una habilidad es de ataque, debe tener establecido un tipo 
                de defensa. El tipo de defensa se usa en el personaje atacado.

             f) Tipo de daño: Cuando una habilidad es de ataque, debe tener establecido un tipo de 
                daño. El tipo de daño se usa en el personaje atacado.

             g) Valor del daño: Cuando una habilidad es de ataque, debe tener establecido un valor 
                para el daño en puntos de vitalidad. El valor del daño se usa con el personaje 
                atacado.

             h) Curación: Cuando una habilidad es de curación, debe tener establecido un valor de 
                curación en puntos.

             i) Efecto en ataque: Cuando una habilidad es auto-aplicada, puede tener establecido uno 
                o más tipos de ataque, asignado como tipo de efecto en ataque. Alternativamente 
                (y excluyentemente) puede tener establecido un efecto en defensa (véase k).

             j) Valor del efecto en ataque: Cuando una habilidad es auto-aplicada, para cada tipo de 
                efecto en ataque establecido (véase i), debe tener establecido un valor del efecto
                en ataque en puntos de vitalidad.

             k) Efecto en defensa: Cuando una habilidad es auto-aplicada, puede tener establecido 
                uno o más tipos de defensa, asignado como tipo de efecto en defensa. Alternativamente 
                (excluyentemente) puede tener establecido un efecto en ataque (véase i).

             l) Valor del efecto en defensa: Cuando una habilidad es auto-aplicada, para cada tipo de 
                efecto en defensa establecido (véase k), debe tener establecido un valor del efecto
                en defensa en puntos de vitalidad.


        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se deben sustituir las asignaciones de valores por asignaciones similares, obtenidas a 
        partir del diseño del juego.

        Los métodos usados en las líneas de código siguientes establecen si se debe usar un tipo de 
        ataque, de defensa o de daño. Por ejemplo, el método 'asignaAtaque' debe ser llamado con un 
        parámetro del tipo (puntero) 'TipoAtaque'.  

        *******************************************************************************************/
        //
        // ── Abeja Reina ──────────────────────────────────────────────────────────
        // Mandato Regio: debuff puro (sin daño), cuesta el máximo de PA menos 1 (coste fijo)
        mandatoRegio->ponCoste (ActorPersonaje::maximoPuntosAccion - 1);
        mandatoRegio->ponAlcance (RejillaTablero::filas + RejillaTablero::columnas - 1); // alcance total
        mandatoRegio->ponEfectoEstado (TipoEstado::MultiplicadorCosteHabilidades, 10, -1); // -1 = hasta fin de ronda
        //
        // Feromonas de Jalea Real: buff de defensa en área a aliados (sin curación de HP)
        feromonasJalea->ponCoste (2);
        feromonasJalea->ponAlcance (5);
        feromonasJalea->ponRadioAlcance (2);
        feromonasJalea->ponEfectoEstado (TipoEstado::ModificadorDefensa, 20, 2);
        //
        // Decreto de Enjambre: ataque melee físico + empuje 3 casillas
        decretoEnjambre->ponCoste (2);
        decretoEnjambre->ponAlcance (1);
        decretoEnjambre->asignaAtaque  (ataqueCuerpoACuerpo);
        decretoEnjambre->asignaDefensa (defensaCuerpoACuerpo);
        decretoEnjambre->asignaDano    (danoFisico, 35);
        decretoEnjambre->ponEmpuje (3);
        //
        // Inspiración: buff equipo, reduce coste de habilidades en 1 PA durante 3 turnos
        inspiracion->ponCoste (4);
        inspiracion->ponEfectoEstado (TipoEstado::ModificadorCosteHabilidades, -1, 3);
        // ── Abeja Guardia ────────────────────────────────────────────────────────
        // Escudo de Quitina: buff de defensa propio, dura 2 turnos
        // Con base C-C 65, llega a 85 efectiva → más difícil de golpear pero no invulnerable
        escudoQuitina->ponCoste (2);
        escudoQuitina->ponEfectoEstado (TipoEstado::ModificadorDefensa, 20, 2);
        //
        // Ataque Tronador: golpe melee potente (55 daño bruto)
        // vs def 50: E[daño] ≈ 41 bruto, ~36 neto (5 reducción). 5 PA → 7 daño/PA
        ataqueTronador->ponCoste (2);
        ataqueTronador->ponAlcance (1);
        ataqueTronador->asignaAtaque  (ataqueCuerpoACuerpo);
        ataqueTronador->asignaDefensa (defensaCuerpoACuerpo);
        ataqueTronador->asignaDano    (danoFisico, 55);
        //
        // Embestida Territorial: golpe melee + empuje 3 casillas (45 daño bruto)
        // Más caro que Tronador por la utilidad del empuje; daño menor pero reposiciona
        embestidaTerritorial->ponCoste (3);
        embestidaTerritorial->ponAlcance (1);
        embestidaTerritorial->asignaAtaque  (ataqueCuerpoACuerpo);
        embestidaTerritorial->asignaDefensa (defensaCuerpoACuerpo);
        embestidaTerritorial->asignaDano    (danoFisico, 45);
        embestidaTerritorial->ponEmpuje (3);
        //
        // Aguijón Cadena: ataque a distancia de poco daño + atrae hacia la Guardiana
        // Daño bajo (20), pero el gancho trae al enemigo adyacente si el camino está libre
        // Solo arrastra si el ataque impacta (roce, impacto o crítico)
        aguijonCadena->ponCoste (2);
        aguijonCadena->ponAlcance (6);   // desde cuántos casillas se puede lanzar
        aguijonCadena->asignaAtaque  (ataqueADistancia);
        aguijonCadena->asignaDefensa (defensaADistancia);
        aguijonCadena->asignaDano    (danoFisico, 20);
        aguijonCadena->ponAtraccion (RejillaTablero::filas + RejillaTablero::columnas); // arrastra hasta quedar adyacente
        // ── Reina Araña ──────────────────────────────────────────────────────────
        // Red de Dominio: debuff de área puro (sin daño), triplica coste habilidades 2 turnos
        // alcance 4, radio 2 → cubre un buen área pero no todo el mapa
        redDominio->ponCoste (2);
        redDominio->ponAlcance (4);
        redDominio->ponRadioAlcance (2);
        redDominio->ponEfectoEstado (TipoEstado::MultiplicadorCosteHabilidades, 3, 2);
        //
        // Hilo del Titiritero: debuff puro al personaje, siempre acierta; cuesta TODOS los PA
        // turnos=-1 → dura hasta fin de ronda (se limpia en restauraPersonajes)
        hiloTitiritero->ponCoste (ActorPersonaje::maximoPuntosAccion);
        hiloTitiritero->ponAlcance (RejillaTablero::filas + RejillaTablero::columnas - 1);
        hiloTitiritero->ponEfectoEstado (TipoEstado::HiloTitiritero, 1, -1);
        //
        // Mordedura Venenosa: melee con veneno (daño 30 + 10/turno durante 3 turnos)
        // coste 5 PA, adyacente, contra defensaCaC → daño moderado más DoT persistente
        mordeduraVenenosa->ponCoste (2);
        mordeduraVenenosa->ponAlcance (1);
        mordeduraVenenosa->asignaAtaque  (ataqueCuerpoACuerpo);
        mordeduraVenenosa->asignaDefensa (defensaCuerpoACuerpo);
        mordeduraVenenosa->asignaDano    (danoFisico, 30);
        mordeduraVenenosa->ponEfectoEstado (TipoEstado::VenenoDanoPorTurno, 10, 3);
        //
        // Armaduras de Seda: buff de defensa en área para aliados, +20 defensa 2 turnos
        // alcance 3, radio 2; no cura HP, solo aplica el estado defensivo
        armadurasSeda->ponCoste (2);
        armadurasSeda->ponAlcance (3);
        armadurasSeda->ponRadioAlcance (2);
        armadurasSeda->ponEfectoEstado (TipoEstado::ModificadorDefensa, 20, 2);
        // ── Abeja Exploradora ────────────────────────────────────────────────────
        // Viento Ascendente: buff a aliado a distancia (indirecto), -2 coste habilidades 3 turnos
        vientoAscendente->ponCoste (1);
        vientoAscendente->ponAlcance (7);
        vientoAscendente->ponEfectoEstado (TipoEstado::ModificadorCosteHabilidades, -2, 3);
        //
        // Turbulencia Debilitadora: melee + reduce ataque enemigo -20 durante 2 turnos
        turbulenciaDebilitadora->ponCoste (2);
        turbulenciaDebilitadora->ponAlcance (1);
        turbulenciaDebilitadora->asignaAtaque  (ataqueCuerpoACuerpo);
        turbulenciaDebilitadora->asignaDefensa (defensaCuerpoACuerpo);
        turbulenciaDebilitadora->asignaDano    (danoFisico, 25);
        turbulenciaDebilitadora->ponEfectoEstado (TipoEstado::ModificadorAtaque, -20, 2);
        //
        // Reflujo de Polen: crea un obstáculo en la celda seleccionada durante 3 turnos
        reflujoPolen->ponCoste (2);
        reflujoPolen->ponAlcance (6);
        reflujoPolen->ponRadioAlcance (0);
        reflujoPolen->ponCreaObstaculo (3);
        //
        // Alas Resonantes: ataque a distancia en área amplia, coste muy elevado
        alasResonantes->ponCoste (4);
        alasResonantes->ponAlcance (7);
        alasResonantes->ponRadioAlcance (2);
        alasResonantes->asignaAtaque  (ataqueADistancia);
        alasResonantes->asignaDefensa (defensaADistancia);
        alasResonantes->asignaDano    (danoFisico, 45);
        // ── Avispa Asesina ───────────────────────────────────────────────────────
        // Carga de Aguijón: melee directo con carga hacia el objetivo (alcance 5 hex)
        // Daño solo si la Avispa llega adyacente; obstáculos bloquean el daño
        cargaAguijon->ponCoste (2);
        cargaAguijon->ponAlcance (5);
        cargaAguijon->asignaAtaque  (ataqueCuerpoACuerpo);
        cargaAguijon->asignaDefensa (defensaCuerpoACuerpo);
        cargaAguijon->asignaDano    (danoFisico, 45);
        cargaAguijon->ponCarga ();
        //
        // Precisión de Aguijón: melee adyacente; crítico garantizado si objetivo < 30 HP
        precisionAguijon->ponCoste (2);
        precisionAguijon->ponAlcance (1);
        precisionAguijon->asignaAtaque  (ataqueCuerpoACuerpo);
        precisionAguijon->asignaDefensa (defensaCuerpoACuerpo);
        precisionAguijon->asignaDano    (danoFisico, 35);
        precisionAguijon->ponCriticoSiObjetivoDebil ();
        //
        // Frenesí: buff propio → +15 ataque y +15 defensa durante 2 turnos
        frenesi->ponCoste (2);
        frenesi->ponEfectoEstado (TipoEstado::ModificadorAtaque,  15, 2);
        frenesi->ponEfectoEstado (TipoEstado::ModificadorDefensa, 15, 2);
        //
        // Desgarrar Formación: ataque melee débil + reduce 20 pts de defensa al enemigo 2 turnos
        desgarrarFormacion->ponCoste (1);
        desgarrarFormacion->ponAlcance (1);
        desgarrarFormacion->asignaAtaque  (ataqueCuerpoACuerpo);
        desgarrarFormacion->asignaDefensa (defensaCuerpoACuerpo);
        desgarrarFormacion->asignaDano    (danoFisico, 15);
        desgarrarFormacion->ponEfectoEstado (TipoEstado::ModificadorDefensa, -20, 2);
        // ── Abeja Nodriza ────────────────────────────────────────────────────────
        // Jalea Restauradora: curación media a distancia (indirecto), sin contacto
        jaleaRestauradora->ponCoste (2);
        jaleaRestauradora->ponAlcance (5);
        jaleaRestauradora->asignaCuracion (30);
        //
        // Manto de Miel: buff de defensa a un aliado a distancia
        mantoMiel->ponCoste (1);
        mantoMiel->ponAlcance (5);
        mantoMiel->ponEfectoEstado (TipoEstado::ModificadorDefensa, 25, 3);
        //
        // Cuidados Intensivos: curación alta a meleé + limpia todos los estados negativos
        cuidadosIntensivos->ponCoste (3);
        cuidadosIntensivos->ponAlcance (1);
        cuidadosIntensivos->asignaCuracion (60);
        cuidadosIntensivos->ponLimpiaEstadosNegativos ();
        //
        // Absorción de Cera: elimina obstáculos temporales del tablero y cura aliados
        // valorCuracion = curación por cada obstáculo absorbido (0 obstáculos = 0 curación)
        absorcionCera->ponCoste (2);
        absorcionCera->asignaCuracion (20);
        absorcionCera->ponEliminaObstaculos ();
        // ── Polilla ──────────────────────────────────────────────────────────────
        // Brebaje Corrupto: debuff puro en área — reduce defensa -25 durante 3 rondas
        brebajeCorrupto->ponCoste (2);
        brebajeCorrupto->ponAlcance (5);
        brebajeCorrupto->ponRadioAlcance (2);
        brebajeCorrupto->ponEfectoEstado (TipoEstado::ModificadorDefensa, -25, 3);
        //
        // Ungüento de Cera: curación moderada a distancia a un aliado
        unguentoCera->ponCoste (2);
        unguentoCera->ponAlcance (5);
        unguentoCera->asignaCuracion (30);
        //
        // Cera Pegajosa: crea obstáculo temporal en celda vacía (idéntico a Reflujo de Polen)
        ceraPegajosa->ponCoste (2);
        ceraPegajosa->ponAlcance (6);
        ceraPegajosa->ponRadioAlcance (0);
        ceraPegajosa->ponCreaObstaculo (3);
        //
        // Vapores: ataque a distancia en área + buff de ataque +20 a todos los aliados vivos durante 2 turnos
        vapores->ponCoste (3);
        vapores->ponAlcance (5);
        vapores->ponRadioAlcance (2);
        vapores->asignaAtaque  (ataqueADistancia);
        vapores->asignaDefensa (defensaADistancia);
        vapores->asignaDano    (danoFisico, 40);
        vapores->ponEfectoEstadoAliados (TipoEstado::ModificadorAtaque, 20, 2);
        // ── Habilidades placeholder ──────────────────────────────────────────────
        ataqueEspadaNormal->ponCoste (1);
        ataqueEspadaNormal->ponAlcance (1);
        ataqueEspadaNormal->asignaAtaque  (ataqueCuerpoACuerpo); 
        ataqueEspadaNormal->asignaDefensa (defensaCuerpoACuerpo); 
        ataqueEspadaNormal->asignaDano    (danoFisico, 20); 
        //
        ataqueArco->ponCoste (2);
        ataqueArco->ponAlcance (15);
        ataqueArco->asignaAtaque  (ataqueADistancia);
        ataqueArco->asignaDefensa (defensaADistancia);
        ataqueArco->asignaDano    (danoFisico, 20);
        //
        ataqueEspadaPoderoso->ponCoste (2);
        ataqueEspadaPoderoso->ponAlcance (1);
        ataqueEspadaPoderoso->asignaAtaque  (ataqueCuerpoACuerpo);
        ataqueEspadaPoderoso->asignaDefensa (defensaCuerpoACuerpo);
        ataqueEspadaPoderoso->asignaDano    (danoFisico, 50);
        //
        defensaFerrea->ponCoste (1);
        defensaFerrea->agregaEfectoDefensa (defensaCuerpoACuerpo, 30);
        defensaFerrea->agregaEfectoDefensa (defensaADistancia,    30);
        //
        curacionSimple->ponCoste (2);
        curacionSimple->ponAlcance (3);  
        curacionSimple->asignaCuracion (40);
        //
        curacionGrupo->ponCoste (4);
        curacionGrupo->ponAlcance (3);  
        curacionGrupo->ponRadioAlcance (3);
        curacionGrupo->asignaCuracion (40);
        //
        proyectilMagico->ponCoste (3);
        proyectilMagico->ponAlcance (15);                                            
        proyectilMagico->asignaAtaque  (ataqueADistancia);
        proyectilMagico->asignaDefensa (defensaADistancia);
        proyectilMagico->asignaDano    (danoFisico, 30);
        //
        bolaFuego->ponCoste (4);
        bolaFuego->ponAlcance (8);
        bolaFuego->ponRadioAlcance (3);
        bolaFuego->asignaAtaque  (ataqueADistancia);
        bolaFuego->asignaDefensa (defensaADistancia);
        bolaFuego->asignaDano    (danoFisico, 50);
        //
        // Veneno mortal: inflige daño inmediato + 8 pts de veneno por turno durante 3 turnos
        venenoMortal->ponCoste (3);
        venenoMortal->ponAlcance (1);
        venenoMortal->asignaAtaque  (ataqueCuerpoACuerpo);
        venenoMortal->asignaDefensa (defensaCuerpoACuerpo);
        venenoMortal->asignaDano    (danoFisico, 10);
        venenoMortal->ponEfectoEstado (TipoEstado::VenenoDanoPorTurno, 8, 3);
        // ── Mosca Carroñera ─────────────────────────────────────────────────────
        // Carga Ilusoria: ataque en área indirecto, radio=0 (celda única), rango largo
        // Ataca como a distancia (la Mosca lanza desde lejos sin línea de visión directa)
        cargaIlusoria->ponCoste (2);
        cargaIlusoria->ponAlcance (6);
        cargaIlusoria->ponRadioAlcance (0);
        cargaIlusoria->asignaAtaque  (ataqueADistancia);
        cargaIlusoria->asignaDefensa (defensaADistancia);
        cargaIlusoria->asignaDano    (danoFisico, 35);
        //
        // Ojos del Carroñero: debuff puro a distancia — baja defensa del objetivo -35 pts por 3 rondas
        ojosCarronero->ponCoste (1);
        ojosCarronero->ponAlcance (7);
        ojosCarronero->ponEfectoEstado (TipoEstado::ModificadorDefensa, -35, 3);
        //
        // Arrastre de Víctima: selecciona celda libre; la Mosca se mueve allí y arrastra al enemigo adyacente
        arrastreVictima->ponCoste (2);
        arrastreVictima->ponAlcance (4);
        arrastreVictima->ponRadioAlcance (0);
        arrastreVictima->ponMueveAtacante ();
        //
        // Huida Cobarde: ataque corto + debuff ataque -20 por 1 ronda + la Mosca escapa a celda aleatoria
        huidaCobarde->ponCoste (1);
        huidaCobarde->ponAlcance (2);
        huidaCobarde->asignaAtaque  (ataqueCuerpoACuerpo);
        huidaCobarde->asignaDefensa (defensaCuerpoACuerpo);
        huidaCobarde->asignaDano    (danoFisico, 10);
        huidaCobarde->ponEfectoEstado (TipoEstado::ModificadorAtaque, -20, 1);
        huidaCobarde->ponEscapaAleatorio ();
        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::agregaEstadisticasPersonajes () {
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Décima sección - Los tipos de ataque, defensa y reducción de daño de los personajes

        En esta sección se establecen que tipos de ataque, defensa y reducción de daño tiene cada 
        personajes del juego, junto con la correspondiente puntuación.

        Configuración
        -------------

        La configuración de los tipos se debe realizar de la siguiente forma:

             a) Si un personaje tiene una habilidad y esta habilidad tiene un tipo de ataque, el 
                personaje debe tener ese tipo de ataque.

             b) Cada personaje debe tener todos los tipos de defensa.

             c) Cada personaje debe tener todos los tipos de daño, en forma de reducción de daño.

             d) Si un personaje tiene una habilidad y esta habilidad tiene un efecto en ataque,
                que está definido usando un tipo de ataque, el personaje debe tener dicho tipo de 
                ataque.

             e) Si un personaje tiene una habilidad y esta habilidad tiene un efecto en defensa,
                que está definido usando un tipo de defensa, el personaje debe tener dicho tipo de 
                defensa. Esta propiedad está establecida previamente mediante el punto (b)

             f) Cada tipo de ataque, defensa y reducción de daño del personaje debe tener una 
                puntuación. La puntuación no puede ser negativa.        

        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se deben sustituir las listas de tipos de ataque, defensa y reducción de daño de cada 
        personaje por listas similares, obtenidas a partir del diseño del juego.

        Los métodos usados en las líneas de código siguientes establecen si el tipo es ataque, 
        defensa o daño. Por ejemplo, el método 'agregaReduceDano' debe ser llamado con un parámetro 
        del tipo (puntero) 'TipoDano'.  

        *******************************************************************************************/
        //
        AbejaReina      ->agregaAtaque     (ataqueCuerpoACuerpo,  70);
        AbejaReina      ->agregaAtaque     (ataqueADistancia,     50);
        AbejaReina      ->agregaDefensa    (defensaCuerpoACuerpo, 70);
        AbejaReina      ->agregaDefensa    (defensaADistancia,    70);
        AbejaReina      ->agregaDefensa    (defensaMagica,        20);
        AbejaReina      ->agregaReduceDano (danoFisico,           10);
        AbejaReina      ->agregaReduceDano (danoMagico,            5);
        //
        AbejaGuardia    ->agregaAtaque     (ataqueCuerpoACuerpo,  60);  // tanque melee
        AbejaGuardia    ->agregaAtaque     (ataqueADistancia,     50);  // para Aguijón Cadena
        AbejaGuardia    ->agregaDefensa    (defensaCuerpoACuerpo, 65);  // alta resistencia física
        AbejaGuardia    ->agregaDefensa    (defensaADistancia,    55);
        AbejaGuardia    ->agregaDefensa    (defensaMagica,        40);
        AbejaGuardia    ->agregaReduceDano (danoFisico,           10);  // armadura física sólida
        AbejaGuardia    ->agregaReduceDano (danoMagico,            5);
        //
        AbejaExploradora->agregaAtaque     (ataqueCuerpoACuerpo,  60);
        AbejaExploradora->agregaAtaque     (ataqueADistancia,     70);
        AbejaExploradora->agregaDefensa    (defensaCuerpoACuerpo, 50);
        AbejaExploradora->agregaDefensa    (defensaADistancia,    50);
        AbejaExploradora->agregaDefensa    (defensaMagica,        50);
        AbejaExploradora->agregaReduceDano (danoFisico,            7);
        AbejaExploradora->agregaReduceDano (danoMagico,            7);
        //
        AranaReina      ->agregaAtaque     (ataqueCuerpoACuerpo,  70);
        AranaReina      ->agregaAtaque     (ataqueADistancia,     50);
        AranaReina      ->agregaDefensa    (defensaCuerpoACuerpo, 70);
        AranaReina      ->agregaDefensa    (defensaADistancia,    70);
        AranaReina      ->agregaDefensa    (defensaMagica,        20);
        AranaReina      ->agregaReduceDano (danoFisico,           10);
        AranaReina      ->agregaReduceDano (danoMagico,            5);
        //
        Avispa          ->agregaAtaque     (ataqueCuerpoACuerpo,  65);  // atacante melee veloz
        Avispa          ->agregaDefensa    (defensaCuerpoACuerpo, 45);  // armadura ligera
        Avispa          ->agregaDefensa    (defensaADistancia,    40);
        Avispa          ->agregaDefensa    (defensaMagica,        35);
        Avispa          ->agregaReduceDano (danoFisico,            5);
        Avispa          ->agregaReduceDano (danoMagico,            5);
        //
        Polilla   ->agregaAtaque     (ataqueADistancia,     70);  // solo Vapores usa ataque a distancia
        Polilla   ->agregaDefensa    (defensaCuerpoACuerpo, 40);
        Polilla   ->agregaDefensa    (defensaADistancia,    40);
        Polilla   ->agregaDefensa    (defensaMagica,        30);
        Polilla   ->agregaReduceDano (danoFisico,            0);
        Polilla   ->agregaReduceDano (danoMagico,           15);
        //
        AbejaNodriza->agregaDefensa    (defensaCuerpoACuerpo, 45);  // soporte — poca resistencia
        AbejaNodriza->agregaDefensa    (defensaADistancia,    45);
        AbejaNodriza->agregaDefensa    (defensaMagica,        35);
        AbejaNodriza->agregaReduceDano (danoFisico,            5);
        AbejaNodriza->agregaReduceDano (danoMagico,            5);
        //
        MoscaCarronera  ->agregaAtaque     (ataqueCuerpoACuerpo,  55);  // Mosca Carroñera: melee y distancia física
        MoscaCarronera  ->agregaAtaque     (ataqueADistancia,     60);  // para Carga Ilusoria
        MoscaCarronera  ->agregaDefensa    (defensaCuerpoACuerpo, 40);  // ligera, evasiva
        MoscaCarronera  ->agregaDefensa    (defensaADistancia,    45);
        MoscaCarronera  ->agregaDefensa    (defensaMagica,        30);
        MoscaCarronera  ->agregaReduceDano (danoFisico,            5);
        MoscaCarronera  ->agregaReduceDano (danoMagico,            5);
        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::preparaSistemaAtaque () {
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Séptima sección - Los grados de efectividad - Segunda parte

        En esta sección se configuran los grados de efectividad de los ataques del juego. En la 
        primera parte se establecen las variables destinadas a almacenar las instancias que definen 
        los grados de efectividad. En esta parte se crean las instancias y se configuran.

        Las variable usan un nombre similar al nombre de los tipos correspondiente. Las variables 
        son de tipo puntero, la creación de las instancias utiliza la palabra reservada 'new'. 

        Atributos
        ---------

        Se asignan los siguientes atributos a los tipos:

             a) Descripción: Asignado en la creación de la instancia en una cadena de caracteres. 
                Deben ser cortos.

             b) Intervalo de puntos: Es el intervalo de puntos al que se aplica la efectividad. 
                Se establece con un valor mínimo y uno máximo. En el primer intervalo el valor 
                mínimo es el número entero mínimo y en el último intervalo, el valor máximo es 
                el número entero máximo.

             c) Efectividad: Es un porcentaje que se aplica a una puntuación para modificar su 
                valor cuando dicha puntuación esta en el intervalo definido por el intervalo
                correspondiente. 
            
        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se debe sustituir las listas de creaciones de instancias por listas similares, obtenidas a 
        partir de la lista de grados de efectividad diseñados para el juego. 

        Se deben cambiar los valores de los parámetros según los valores establecidos para cada 
        grados de efectividad en el diseño del juego.

        *******************************************************************************************/
        //
        GradoEfectividad * fallo   = new GradoEfectividad {L"Fallo"};
        GradoEfectividad * roce    = new GradoEfectividad {L"Roce"};
        GradoEfectividad * impacto = new GradoEfectividad {L"Impacto"};
        GradoEfectividad * critico = new GradoEfectividad {L"Impacto crítico"};
        //
        fallo  ->estableceRango (INT_MIN,       9,    0);
        roce   ->estableceRango (     10,      49,   50);
        impacto->estableceRango (     50,      89,  100);
        critico->estableceRango (     90, INT_MAX,  150);
        //
        agregaEfectividad (fallo);
        agregaEfectividad (roce);
        agregaEfectividad (impacto);
        agregaEfectividad (critico);
        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::configuraJuego () {
        agregaMusica (new ActorMusica {this});
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Undécima sección - Configuración miscelánea del juego.

        En esta sección se establecen varios valores de configuración que no tienen sitio en otras 
        secciones.

        Configuración
        -------------

        La configuración tiene los siguientes aspectos:

                 a) Se establece el consumo de puntos de acción de los desplazamientos de los 
                    personajes. Para ello se indica el número píxeles de desplazamiento que 
                    originan el consumo de un punto de acción.

                 b) Se establece la posición inicial de las fichas de los personajes en el tablero 
                    de juego.
         
                 c) Se establecen los archivos de sonido, que se escuchan en momentos concretos del
                    juego. Se deben especificar los sonidos:

                      - Sonido de una pulsación con el ratón (clic)
                      - Sonido de desplazamiento de una ficha.

                 d) Se establece la música que se escucha con el juego. En un fragmento musical que 
                    se repite en bucle.

                 e) Se almacenan los nombres de los alumnos diseñadores del juego. Estos nombres
                    aparecen en la ayuda del juego.

                 f) Se almacena el curso académico durante el que los alumnos han elaborado el 
                    diseño del juego.

        Sonidos y música
        ----------------

        Los sonidos se cargan de archivos de tipo 'wav', 'ogg' o 'flac', pero no 'mp3'. El tiempo de
        emisión del sonido debe ser corto (escasos segundos).
        
        Los sonidos y la música se han tomado de:
                https://opengameart.org/content/metal-click
                https://opengameart.org/content/walking-on-snow-sound
        La licencia aparece en esas mismas páginas.

        La música que suena en momentos determinados del juego también se carga de un archivo. Sin 
        embargo, no es necesario que sea corta, por que se atenúa a los pocos segundos.

        La música se han tomado de:
                https://opengameart.org/content/unused-music
        La licencia aparece en esa misma página.

        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se deben sustituir las listas de personajes por listas similares, obtenidas a partir del 
        diseño del juego.

        *******************************************************************************************/
        //
        modo ()->configuraDesplaza (RejillaTablero::distanciaCeldas);
        //
        AbejaReina      ->ponSitioFicha (Coord {17, 15});
        AbejaGuardia    ->ponSitioFicha (Coord {23, 15});
        AbejaExploradora->ponSitioFicha (Coord {29, 15});
        AbejaNodriza    ->ponSitioFicha (Coord {35, 15});
        AranaReina      ->ponSitioFicha (Coord {17, 35});
        Avispa          ->ponSitioFicha (Coord {23, 35});
        Polilla         ->ponSitioFicha (Coord {29, 35});
        MoscaCarronera      ->ponSitioFicha (Coord {35, 35});
        //
        // Sonido específico al seleccionar cada personaje
        AbejaReina      ->ponArchivoSonidoSeleccion (carpeta_sonidos_juego + "Colmena/Seleccion_AbejaReina_Colmena.wav");
        AbejaGuardia    ->ponArchivoSonidoSeleccion (carpeta_sonidos_juego + "Colmena/Seleccion_Guardiana_Colmena.wav");
        AbejaExploradora->ponArchivoSonidoSeleccion (carpeta_sonidos_juego + "Colmena/Seleccion_Exploradora_Colmena.wav");
        AbejaNodriza    ->ponArchivoSonidoSeleccion (carpeta_sonidos_juego + "Colmena/Seleccion_Nodriza_Colmena.wav");
        AranaReina      ->ponArchivoSonidoSeleccion (carpeta_sonidos_juego + "Corte/Seleccion_ReinaArana_Corte.wav");
        Avispa          ->ponArchivoSonidoSeleccion (carpeta_sonidos_juego + "Corte/Seleccion_Avispa_Corte.wav");
        Polilla         ->ponArchivoSonidoSeleccion (carpeta_sonidos_juego + "Corte/Seleccion_Polilla_Corte.wav");
        MoscaCarronera  ->ponArchivoSonidoSeleccion (carpeta_sonidos_juego + "Corte/Seleccion_Mosca_Corte.wav");
        //
        tablero ()->asignaSonidoEstablece (carpeta_sonidos_juego + "Metal Click.wav", 100);
        tablero ()->asignaSonidoDesplaza  (carpeta_sonidos_juego + "SnowWalk.ogg",    100);
        musica  ()->asignaMusica          (carpeta_sonidos_juego + "Musica_Juego.wav", 100);
        //
        agregaNombreAlumno (L"Virginia Martín Pérez");
        agregaNombreAlumno (L"Gema Virginia Toyos Lanza");
        agregaNombreAlumno(L"Eduardo Briz Merino");
        agregaNombreAlumno(L"Elvira Bermúdez Fernández");
        agregaNombreAlumno (L"Jonathan Raya Ríos");
        indicaCursoAcademico (L"2025 - 2026");
        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::termina () {
        //
        JuegoMesaBase::termina ();
        //
        AbejaReina       = nullptr;
        AbejaGuardia     = nullptr;
        AbejaExploradora = nullptr;
        AbejaNodriza     = nullptr;
        AranaReina       = nullptr;
        Avispa           = nullptr;
        Polilla          = nullptr;
        MoscaCarronera       = nullptr;
        //
        mandatoRegio    = nullptr;
        feromonasJalea  = nullptr;
        decretoEnjambre = nullptr;
        inspiracion  = nullptr;
        //
        escudoQuitina        = nullptr;
        ataqueTronador       = nullptr;
        embestidaTerritorial = nullptr;
        aguijonCadena        = nullptr;
        //
        redDominio        = nullptr;
        hiloTitiritero    = nullptr;
        mordeduraVenenosa = nullptr;
        armadurasSeda     = nullptr;
        //
        vientoAscendente        = nullptr;
        turbulenciaDebilitadora = nullptr;
        reflujoPolen            = nullptr;
        alasResonantes          = nullptr;
        //
        jaleaRestauradora  = nullptr;
        mantoMiel          = nullptr;
        cuidadosIntensivos = nullptr;
        absorcionCera      = nullptr;
        //
        brebajeCorrupto = nullptr;
        unguentoCera    = nullptr;
        ceraPegajosa    = nullptr;
        vapores         = nullptr;
        //
        cargaIlusoria   = nullptr;
        ojosCarronero   = nullptr;
        arrastreVictima = nullptr;
        huidaCobarde    = nullptr;
        //
        cargaAguijon       = nullptr;
        precisionAguijon   = nullptr;
        frenesi            = nullptr;
        desgarrarFormacion = nullptr;
        //
        ataqueEspadaNormal   = nullptr;
        ataqueArco           = nullptr;
        ataqueEspadaPoderoso = nullptr;
        defensaFerrea        = nullptr;
        curacionSimple       = nullptr;
        curacionGrupo        = nullptr;
        proyectilMagico      = nullptr;
        bolaFuego            = nullptr;
        venenoMortal         = nullptr;
        //
        ataqueCuerpoACuerpo  = nullptr;
        ataqueADistancia     = nullptr;
        ataqueMagico         = nullptr;
        defensaCuerpoACuerpo = nullptr;
        defensaADistancia    = nullptr;
        defensaMagica        = nullptr;
        danoFisico           = nullptr;
        danoMagico           = nullptr;
    }


}