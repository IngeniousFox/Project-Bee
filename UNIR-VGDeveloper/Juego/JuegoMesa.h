// proyecto: Grupal/Juego
// arhivo:   JuegoMesa.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace juego {


    class JuegoMesa : public JuegoMesaBase {
    public:

        JuegoMesa ();

    private:

        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Cuarta sección - Los personajes - Segunda parte

        En esta sección se configuran los personajes del juego. 
        
        Consiste en declarar las variables que están destinadas a almacenar las instancias que 
        definen a los personajes. 

        El nombre de cada variable es similar al nombre del personaje correspondiente. Las variables 
        son de tipo puntero. 

        Programación
        ------------

        Se debe sustituir la lista de declaraciones de variables por una lista similar obtenida de
        la lista de personajes diseñados para el juego.

        *******************************************************************************************/
        ActorPersonaje * AbejaReina {};
        ActorPersonaje * AbejaGuardia {};
        ActorPersonaje * AbejaExploradora {};
        ActorPersonaje * AbejaNodriza {};
        ActorPersonaje * AranaReina {};
        ActorPersonaje * Avispa {};
        ActorPersonaje * Polilla {};
        ActorPersonaje * MoscaCarronera {};
        /*******************************************************************************************
        /******************************************************************************************/
 

        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Quinta sección - Las habilidades - Primera parte

        En esta sección se configuran las habilidades compartidas por los personajes del juego. 
        
        Consiste en declarar las variables que están destinadas a almacenar las instancias que 
        definen a las habilidades. 

        El nombre de cada variable es similar al de la habilidad correspondiente. Las variables son 
        de tipo puntero. 

        Programación
        ------------

        Se debe sustituir la lista de declaraciones de variables por una lista similar obtenida de
        la lista de habilidades diseñadas para el juego.

        *******************************************************************************************/
        // --- Habilidades de la Abeja Reina ---
        Habilidad * mandatoRegio    {};  // Debuff: multiplica x10 el coste de habilidades del enemigo
        Habilidad * feromonasJalea  {};  // Buff área: sube la defensa de los aliados
        Habilidad * decretoEnjambre {};  // Ataque melee + empuje 3 casillas
        Habilidad * inspiracion     {};  // Buff equipo: reduce el coste de habilidades en 1 PA

        // --- Habilidades de la Abeja Guardia ---
        Habilidad * escudoQuitina        {};  // Buff propia: +35 defensa por 2 turnos
        Habilidad * ataqueTronador       {};  // Ataque melee poderoso (daño 55)
        Habilidad * embestidaTerritorial {};  // Ataque melee potente + empuje 3 casillas
        Habilidad * aguijonCadena        {};  // Ataque a distancia: poco daño + atrae 3 casillas

        // --- Habilidades de la Reina Araña ---
        Habilidad * redDominio        {};  // Debuff área: multiplica x3 el coste de habilidades enemigas
        Habilidad * hiloTitiritero    {};  // Meta: el rival controla el objetivo hasta fin de ronda
        Habilidad * mordeduraVenenosa {};  // Ataque melee + veneno por turnos
        Habilidad * armadurasSeda     {};  // Buff área: sube la defensa de los aliados

        // --- Habilidades de la Abeja Exploradora ---
        Habilidad * vientoAscendente      {};  // Buff aliado: reduce el coste de habilidades
        Habilidad * turbulenciaDebilitadora{};  // Ataque melee + reduce el ataque del enemigo
        Habilidad * reflujoPolen          {};  // Crea un obstáculo temporal en una celda vacía
        Habilidad * alasResonantes        {};  // Ataque a distancia en área, coste muy elevado

        // --- Habilidades de la Abeja Nodriza ---
        Habilidad * jaleaRestauradora  {};  // Curación media a distancia (indirecto)
        Habilidad * mantoMiel          {};  // Buff de defensa a un aliado a distancia
        Habilidad * cuidadosIntensivos {};  // Curación alta a meleé + limpia estados negativos
        Habilidad * absorcionCera      {};  // Equipo: elimina obstáculos y cura aliados según cantidad

        // --- Habilidades de la Mosca Carroñera ---
        Habilidad * cargaIlusoria   {};  // Ataque en área a distancia (afecta a 1)
        Habilidad * ojosCarronero   {};  // Debuff: baja la defensa al objetivo
        Habilidad * arrastreVictima {};  // Carga melee: mueve a la Mosca y arrastra al enemigo
        Habilidad * huidaCobarde    {};  // Debuff ataque + empuje (escape)

        // --- Habilidades de la Avispa Asesina ---
        Habilidad * cargaAguijon       {};  // Carga melee: avanza hacia el enemigo, daña si llega adyacente
        Habilidad * precisionAguijon   {};  // Ataque melee: crítico garantizado si objetivo < 30 HP
        Habilidad * frenesi            {};  // Buff propia: +ataque y +defensa durante 2 turnos
        Habilidad * desgarrarFormacion {};  // Ataque melee débil + reduce la defensa del enemigo

        // --- Habilidades de la Polilla ---
        Habilidad * brebajeCorrupto {};  // Debuff área: reduce la defensa de los enemigos
        Habilidad * unguentoCera    {};  // Curación a distancia a un aliado
        Habilidad * ceraPegajosa    {};  // Crea un obstáculo temporal en una celda vacía
        Habilidad * vapores         {};  // Ataque mágico en área + buff de ataque a aliados

        // --- Habilidades placeholder (pendientes de personaje real) ---
        Habilidad * ataqueEspadaNormal {};
        Habilidad * ataqueArco {};
        Habilidad * ataqueEspadaPoderoso {};
        Habilidad * defensaFerrea {};
        Habilidad * curacionSimple {};
        Habilidad * curacionGrupo {};
        Habilidad * proyectilMagico {};
        Habilidad * bolaFuego {};
        Habilidad * venenoMortal {};
        /*******************************************************************************************
        /******************************************************************************************/


        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Sexta sección - Los tipos de ataque, defensa y daño (estadísticas) - Primera parte

        En esta sección se configuran los tipos de ataque, defensa y daño del juego, que son usados
        por los personajes y las habilidades del juego. 
        
        Consiste en declarar las variables que están destinadas a almacenar las instancias que 
        definen los tipos de ataque, defensa y daño. 

        El nombre de cada variable identifica el tipo correspondiente. Las variables son de 
        tipo puntero. El nombre de la clase (por ejemplo 'TipoAtaque' para los ataques) 
        establece si es un tipo de ataque, de defensa o de daño.

        Programación
        ------------

        Se debe sustituir la lista de declaraciones de variables por una lista similar obtenida de
        la lista de tipos de ataque, defensa y daño diseñados para el juego.

        *******************************************************************************************/
        TipoAtaque *  ataqueCuerpoACuerpo {};
        TipoAtaque *  ataqueADistancia {};
        TipoAtaque *  ataqueMagico {};
        TipoDefensa * defensaCuerpoACuerpo {};
        TipoDefensa * defensaADistancia {};
        TipoDefensa * defensaMagica {};
        TipoDano *    danoFisico {};
        TipoDano *    danoMagico {};
        /*******************************************************************************************
        /******************************************************************************************/


        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Séptima sección - Los grados de efectividad - Primera parte

        En esta sección se configuran los grados de efectividad de los ataques del juego. 
        
        Consiste en declarar las variables que están destinadas a almacenar las instancias que 
        definen los grados de efectividad de los ataques. 

        Cada variable tiene un nombre similar al nombre del grados de efectividad correspondiente. 
        Las variables son de tipo puntero. 

        Programación
        ------------

        Se debe sustituir la lista de declaraciones de variables por una lista similar obtenida de
        la lista de grados de efectividad diseñados para el juego.

        *******************************************************************************************/
        GradoEfectividad * fallo {};
        GradoEfectividad * roce {};
        GradoEfectividad * impacto {};
        GradoEfectividad * critico {};
        /*******************************************************************************************
        /******************************************************************************************/

    private:

        static string carpeta_activos_juego;
        static string carpeta_retratos_juego;
        static string carpeta_habilids_juego;
        static string carpeta_sonidos_juego;


        const std::wstring tituloVentana () const override;

        void preparaTablero () override;
        void preparaPersonajes () override;
        void preparaHabilidades () override;
        void preparaTiposEstadisticas () override;
        void agregaHabilidadesPersonajes () override;
        void agregaEstadisticasHabilidades () override;
        void agregaEstadisticasPersonajes () override;
        void preparaSistemaAtaque () override;
        void configuraJuego () override;
        void termina () override;

    };


}


