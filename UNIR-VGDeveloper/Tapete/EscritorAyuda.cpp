// proyecto: Grupal/Tapete   
// arhivo:   ModoJuegoBase.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {


    
    void EscritorAyuda::escribeGeneral (JuegoMesaBase & juego) {
        ListadoAyuda & listado = juego.tablero ()->listadoAyuda ();
        listado.borra ();
        //


        // para que esto funcione hay que guardar este archivo con codificación:
        //      Europeo occidental (Windows) - Página de códigos 1252
        // o bien con codificación
        //      Unicode (UTF-8 con signatura) - Página de códigos 65001
        
        //std::wstring ws {L"Ññ Çç @ € \200 \u20ac # ~ % & ¿? ¡! áéíóúÁÉÍÓÚ" };
        //std::wcout << "5) " << ws << std::endl;


        //const char * s = "Ññ Çç @ € # ~ % & ¿? ¡! áéíóúÁÉÍÓÚ";
        //listado.escribe (L"Ññ Çç @ € # ~ % & ¿? ¡! áéíóúÁÉÍÓÚ");



        listado.saltaLinea ();
        listado.saltaLinea ();
        listado.enNegrita ();
        listado.escribe (L"                          UNIR-2D :: Juego de Mesa");
        listado.escribe (L"                          ========================");
        listado.saltaLinea ();
        listado.saltaLinea ();
        listado.enClaro ();
        listado.escribe (L"    Proyecto de Videojuego.");
        listado.saltaLinea ();
        listado.saltaLinea ();
        listado.escribe (L"    Asignatura");
        listado.escribe (L"    ----------");
        listado.saltaLinea ();
        listado.escribe (L"      Proyecto Grupal I.");
        listado.escribe (L"      Grado en Diseño y Desarrollo de Videojuegos.");
        listado.escribe (L"      UNIR - Universidad Internacional de La Rioja.");
        listado.saltaLinea ();
        listado.saltaLinea ();
        listado.escribe (L"    Alumnos desarrolladores");
        listado.escribe (L"    -----------------------");
        listado.saltaLinea ();
        int numero = 1;
        for (const wstring & nombre : juego.nombresAlumnos ()) {
            listado.escribe (std::format (L"     {:2}) {}", numero, nombre)); 
            numero ++;
        }
        listado.saltaLinea ();
        listado.escribe (std::format (L"    Curso académico: {}", juego.cursoAcademico ()));
        listado.saltaLinea ();
        listado.saltaLinea ();
        listado.enNegrita ();
        listado.escribe (L"    La leyenda de la Colmena");
        listado.escribe (L"    -----------------------");
        listado.enClaro ();
        listado.saltaLinea ();
        listado.escribe (L"      «Cuentan los olivos milenarios que, para que las flores");
        listado.escribe (L"      bailaran con el sol, primero tuvo que alzarse un reino de");
        listado.escribe (L"      murmullo y oro líquido. Así nació la Colmena, y bajo el");
        listado.escribe (L"      mandato de su Reina hizo suya la misión de promover la");
        listado.escribe (L"      vida, estación tras estación, trabajando incesantemente");
        listado.escribe (L"      para traer de vuelta el color a páramos de hielo y frío.");
        listado.escribe (L"      Pero, desde las sombras, Otra comenzó a tejer su ascenso.");
        listado.escribe (L"      A su llamada acudieron criaturas del desorden,");
        listado.escribe (L"      hambrientas, y juntas juraron hacerse con el dominio de la");
        listado.escribe (L"      Colmena, aquel castillo rebosante de riqueza que abastecía");
        listado.escribe (L"      sin descanso a sus habitantes.»");
        listado.saltaLinea ();
        listado.escribe (L"      Project Bee recoge esta fábula: la Colmena Dorada");
        listado.escribe (L"      defiende su hogar frente a la Corte de Seda y Veneno, los");
        listado.escribe (L"      insectos que la Reina Araña ha reunido desde las sombras");
        listado.escribe (L"      para arrebatarle su reino de oro líquido.");
        while (listado.linea () < 44) {
            listado.saltaLinea ();
        }
        listado.escribe (L"    -----------------------------------------------------------------------"); 
        listado.saltaLinea ();
        listado.escribe (L"    Copyright (C) 2022 UNIR-Universidad Internacional de La Rioja."); 
        listado.escribe (L"    Todos los derechos reservados."); 
        listado.escribe (L"    El sofware se entrega solo para uso educativo, sin ninguna garantía de"); 
        listado.escribe (L"    adecuación para ningún proposito particular.");
        listado.saltaLinea ();
        listado.escribe (L"    Bibliotecas de código usadas:"); 
        listado.escribe (L"        1) SFML - Simple and Fast Multimedia Library.");  
        listado.escribe (L"           Licencia: https://www.sfml-dev.org/license.php");  
        listado.saltaLinea ();
        //
        listado.muestra ();
    }


    void EscritorAyuda::escribePersonaje (JuegoMesaBase & juego, ActorPersonaje * personaje) {
        ListadoAyuda & listado = juego.tablero ()->listadoAyuda ();
        listado.borra ();
        listado.saltaLinea ();
        listado.saltaLinea ();
        listado.enNegrita ();
        listado.escribe (std::format (L"    {}", personaje->nombre ()));    
        listado.enClaro ();
        listado.escribe (
                std::format (L"    personaje {} del equipo '{}'", 
                personaje->indiceEnEquipo () + 1, 
                juego.tablero ()->nombreEquipo (personaje->ladoTablero ())));
        listado.saltaLinea ();
        listado.escribe (std::format (L"    - Iniciativa: {}", personaje->iniciativa ()));
        listado.escribe (std::format (L"    - Vitalidad: {}", personaje->vitalidad ()));
        listado.escribe (std::format (L"    - Puntos acción: {}", personaje->puntosAccion ()));
        listado.saltaLinea ();
        listado.saltaLinea ();
        listado.escribe (L"    Estadísticas");
        listado.escribe (L"    ------------");
        // Los atributos mágicos no se muestran en el tooltip (su nombre contiene "gic":
        // "Ataque mágico", "Defensa mágica", "Daño mágico"). El juego no usa magia.
        for (TipoAtaque * tipo_ataque : juego.ataques ()) {
            if (tipo_ataque->nombre ().find (L"gic") != std::wstring::npos) {
                continue;
            }
            if (personaje->apareceAtaque (tipo_ataque)) {
                listado.escribe (std::format (L"    {:30}  {:-3}",
                                    tipo_ataque->nombre (), personaje->valorAtaque (tipo_ataque)));
            }
        }
        for (TipoDefensa * tipo_defensa : juego.defensas ()) {
            if (tipo_defensa->nombre ().find (L"gic") != std::wstring::npos) {
                continue;
            }
            if (personaje->apareceDefensa (tipo_defensa)) {
                listado.escribe (std::format (L"    {:30}  {:-3}",
                                    tipo_defensa->nombre (), personaje->valorDefensa (tipo_defensa)));
            }
        }
        for (TipoDano * tipo_dano : juego.danos ()) {
            if (tipo_dano->nombre ().find (L"gic") != std::wstring::npos) {
                continue;
            }
            if (personaje->apareceReduceDano (tipo_dano)) {
                listado.escribe (std::format (L"    Reducción {:20}  {:-3}",
                                    tipo_dano->nombre (), personaje->valorReduceDano (tipo_dano)));
            }
        }
        listado.saltaLinea ();
        listado.saltaLinea ();
        listado.escribe (L"    Habilidades");
        listado.escribe (L"    -----------");
        for (Habilidad * habilidad : personaje->habilidades ()) {
            listado.saltaLinea ();
            escribeHabilidad (listado, habilidad);
        }
        listado.saltaLinea ();
        listado.muestra ();
    }


    void EscritorAyuda::escribeCalculo (JuegoMesaBase & juego) {
        // solo usado en 'ModoJuegoComun'
        //
        assert (juego.sistemaAtaque ().atacante () != nullptr);
        //
        ListadoAyuda & listado = juego.tablero ()->listadoAyuda ();
        listado.borra ();
        SistemaAtaque & sistema = juego.sistemaAtaque ();
        //
        listado.saltaLinea ();
        listado.saltaLinea ();
        listado.enNegrita ();
        switch (sistema.habilidad ()->antagonista ()) {
        case Antagonista::oponente:
            listado.escribe (L"                             Cálculo del Ataque");
            listado.escribe (L"                             ==================");
            break;
        case Antagonista::aliado:
            listado.escribe (L"                           Cálculo de la Curación");
            listado.escribe (L"                           ======================");
            break;
        case Antagonista::si_mismo:
            listado.escribe (L"                             Cálculo del Efecto");
            listado.escribe (L"                             ==================");
            break;
        }
        listado.saltaLinea ();
        listado.saltaLinea ();
        listado.enClaro ();
        listado.escribe (std::format (L"    Personaje:        {}", sistema.atacante () ->nombre ()));
        listado.escribe (std::format (L"    Habilidad usada:  {}", sistema.habilidad ()->nombre ()));
        //
        switch (sistema.habilidad ()->antagonista ()) {
        case Antagonista::oponente:
            for (const SistemaAtaque::AtaqueOponente & registro : sistema.ataquesOponente ()) {
                escribeAtaque (listado, sistema, registro);
            }
            break;
        case Antagonista::aliado:
            for (const SistemaAtaque::CuracionOponente & registro : sistema.curacionesOponente ()) {
                escribeCuracion (listado, sistema, registro);
            }
            break;
        case Antagonista::si_mismo:
            for (const SistemaAtaque::CambioEfecto & registro : sistema.cambiosEfecto ()) {
                escribeEfecto (listado, sistema, registro);
            }
            break;
        }
        listado.muestra ();
    }


    void EscritorAyuda::borra (JuegoMesaBase & juego) {
        juego.tablero ()->listadoAyuda ().borra ();
        juego.tablero ()->listadoAyuda ().oculta ();
    }


    void EscritorAyuda::escribeHabilidad (
            ListadoAyuda & listado, 
            Habilidad *    habilidad) {
        wstring tipo {};
        switch (habilidad->tipoEnfoque ()) {
        case EnfoqueHabilidad::personaje:
            switch (habilidad->tipoAcceso ()) {
            case AccesoHabilidad::directo:
                tipo = L"oponente directo";
                break;
            case AccesoHabilidad::indirecto:
                tipo = L"oponente indirecto";
                break;
            }
            break;
        case EnfoqueHabilidad::area:
            switch (habilidad->tipoAcceso ()) {
            case AccesoHabilidad::directo:
                tipo = L"área directa";
                break;
            case AccesoHabilidad::indirecto:
                tipo = L"área indirecta";
                break;
            }
            break;
        case EnfoqueHabilidad::si_mismo:
            tipo = L"simple";
            break;
        }
        listado.escribe (std::format (L"    * {} ({})", habilidad->nombre (), tipo)); 
        std::vector <wstring> describe = parrafea (68, habilidad->descripcion ());
        for (const wstring & parrafo : describe) {
            listado.escribe (std::format (L"      {}", parrafo));        
        }
        // Nombre legible de un tipo de estado (no existe TipoEstado::nombre())
        auto nombreEstado = [] (TipoEstado tipo) -> wstring {
            switch (tipo) {
            case TipoEstado::VenenoDanoPorTurno:            return L"Veneno por turno";
            case TipoEstado::ModificadorDefensa:            return L"Modificador de defensa";
            case TipoEstado::ModificadorAtaque:             return L"Modificador de ataque";
            case TipoEstado::ModificadorCosteHabilidades:   return L"Modificador de coste";
            case TipoEstado::MultiplicadorCosteHabilidades: return L"Multiplicador de coste";
            case TipoEstado::HiloTitiritero:                return L"Control del rival";
            }
            return L"Efecto";
        };
        switch (habilidad->antagonista ()) {
        case Antagonista::oponente:
            // Las habilidades de debuff puro no tienen tipo de ataque/defensa/daño:
            // hay que comprobar nullptr antes de acceder a su nombre (evita el cierre).
            if (habilidad->tipoAtaque () != nullptr) {
                listado.escribe (std::format (L"      - {}", habilidad->tipoAtaque ()->nombre ()));
            }
            if (habilidad->tipoDefensa () != nullptr) {
                listado.escribe (std::format (L"      - {}", habilidad->tipoDefensa ()->nombre ()));
            }
            if (habilidad->tipoDano () != nullptr) {
                listado.escribe (std::format (L"      - {}: {}",
                                    habilidad->tipoDano ()->nombre (), habilidad->valorDano ()));
            }
            break;
        case Antagonista::aliado:
            if (habilidad->valorCuracion () > 0) {
                listado.escribe (std::format (L"      - Curación: {}", habilidad->valorCuracion ()));
            }
            break;
        case Antagonista::si_mismo:
            for (const std::pair <TipoAtaque *, int> & efect : habilidad->efectosAtaque ()) {
                listado.escribe (std::format (L"      - Efecto {}: {}",    efect.first->nombre (), efect.second));
            }
            for (const std::pair <TipoDefensa *, int> & efect : habilidad->efectosDefensa ()) {
                listado.escribe (std::format (L"      - Efecto {}: {}",    efect.first->nombre (), efect.second));
            }
            break;
        }
        // Efectos de estado (debuffs/buffs/veneno), para cualquier tipo de habilidad
        for (const EfectoEstado & efecto : habilidad->efectosEstado ()) {
            if (efecto.turnos < 0) {
                listado.escribe (std::format (L"      - {}: {}  (hasta fin de ronda)",
                                    nombreEstado (efecto.tipo), efecto.valor));
            } else {
                listado.escribe (std::format (L"      - {}: {}  ({} turnos)",
                                    nombreEstado (efecto.tipo), efecto.valor, efecto.turnos));
            }
        }
        if (habilidad->alcance () > 0) {
            if (habilidad->radioAlcance () == 0) {
                listado.escribe (std::format (L"      - Alcance (casillas): {}", habilidad->alcance ()));       
            } else {
                listado.escribe (std::format (L"      - Alcance (casillas): {}  radio área: {}", 
                                    habilidad->alcance (), habilidad->radioAlcance ()));       
            }
        }
        listado.escribe (std::format (L"      - Coste (puntos acción): {}", habilidad->coste ()));       
    }


    void EscritorAyuda::escribeAtaque    (
            ListadoAyuda                        & listado, 
            const SistemaAtaque                 & sistema, 
            const SistemaAtaque::AtaqueOponente & registro) {
        listado.saltaLinea ();
        // Habilidad de debuff puro: no tiene tipo de ataque/defensa/daño ni efectividad
        // (SistemaAtaque::calculaAtaque sale antes de calcularlos). Evita el null deref.
        if (registro.tipo_ataque == nullptr) {
            listado.escribe (std::format (L"    · Efecto sobre '{}' (sin daño directo).",
                                registro.oponente->nombre ()));
            listado.escribe (std::format (L"    · Vitalidad de '{}':  {} puntos",
                                registro.oponente->nombre (), registro.vitalidad_final));
            listado.saltaLinea ();
            return;
        }
        listado.escribe (std::format (L"    · {} con valor de {} puntos.",
                            registro.tipo_ataque->nombre (), registro.valor_ataque));
        listado.escribe (std::format (L"    · Contra '{}', provisto de:",
                            registro.oponente->nombre ()));
        listado.escribe (std::format (L"          {} con valor de {} puntos.", 
                            registro.tipo_defensa->nombre (), registro.valor_defensa));
        listado.saltaLinea ();
        listado.escribe (std::format (L"    · Ventaja del ataque:  {}  (valor ataque - valor defensa)", 
                            registro.ventaja));
        listado.escribe (std::format (L"    · Valor aleatorio obtenido:  {} puntos", 
                            registro.aleatorio_100));
        listado.escribe (std::format (L"    · Valor final ataque:  {}  (ventaja + valor aleatorio)", 
                            registro.valor_final_ataque));
        listado.escribe (std::format (L"    · Efectividad: {}, {}% del daño", 
                            registro.efectividad->nombre (), registro.porciento_dano));
        listado.saltaLinea ();
        listado.escribe (std::format (L"    · {} (de la habilidad) con valor de {} puntos", 
                            registro.tipo_dano->nombre (), registro.valor_dano));
        listado.escribe (std::format (L"    · Valor ajustado del daño:  {}  (al {}%)", 
                            registro.valor_ajustado_dano, registro.porciento_dano));
        listado.escribe (std::format (L"    · Reducción de daño de '{}':  {}", 
                            registro.oponente->nombre (), registro.valor_reduce_dano));
        listado.escribe (std::format (L"    · Valor final del daño:  {}  (valor ajustado - valor reducción)", 
                            registro.valor_final_dano));
        listado.saltaLinea ();
        listado.escribe (std::format (L"    · Vitalidad original de '{}':  {} puntos", 
                            registro.oponente->nombre (), 
                            registro.vitalidad_origen));
        listado.escribe (std::format (L"    · Vitalidad resultante:  {}  (vitalidad - daño)", 
                            registro.vitalidad_final));
        listado.saltaLinea ();
    }


    void EscritorAyuda::escribeCuracion  (
            ListadoAyuda                          & listado, 
            const SistemaAtaque                   & sistema, 
            const SistemaAtaque::CuracionOponente & registro) {
        listado.saltaLinea ();
        listado.escribe (std::format (L"    · Valor de {} puntos.", 
                            registro.valor_curacion));
        listado.escribe (std::format (L"    · A favor de '{}'.", 
                            registro.oponente->nombre ()));  
        listado.saltaLinea ();
        listado.escribe (std::format (L"    · Vitalidad original de '{}':  {} puntos", 
                            registro.oponente->nombre (), registro.vitalidad_origen));
        listado.escribe (std::format (L"    · Vitalidad resultante:  {}  (vitalidad + valor)", 
                            registro.vitalidad_final));
        listado.saltaLinea ();
    }


    void EscritorAyuda::escribeEfecto    (
            ListadoAyuda                      & listado, 
            const SistemaAtaque               & sistema, 
            const SistemaAtaque::CambioEfecto & registro) {
        listado.saltaLinea ();
        if (registro.tipo_ataque != nullptr) {
            listado.escribe (std::format (L"    · Cambio en el {}.", 
                                registro.tipo_ataque->nombre ()));
            listado.escribe (std::format (L"    · Valor del cambio:  {:-3} puntos.", 
                                registro.valor_cambio_ataque));
            listado.escribe (std::format (L"    · Valor original:    {:-3} puntos", 
                                registro.valor_origen_ataque));
            listado.escribe (std::format (L"    · Valor resultante:  {:-3} puntos", 
                                registro.valor_final_ataque));

        }
        if (registro.tipo_defensa != nullptr) {
            listado.escribe (std::format (L"    · Cambio en la {}.", 
                                registro.tipo_defensa->nombre ()));
            listado.escribe (std::format (L"    · Valor del cambio:  {:-3} puntos.", 
                                registro.valor_cambio_defensa));
            listado.escribe (std::format (L"    · Valor original:    {:-3} puntos", 
                                registro.valor_origen_defensa));
            listado.escribe (std::format (L"    · Valor resultante:  {:-3} puntos", 
                                registro.valor_final_defensa));

        }
    }


    std::vector <wstring> EscritorAyuda::parrafea (int anchura, const wstring & parrafo) {
        std::vector <wstring> lineas {};
        int inicio = 0;
        while (true) {
            if (inicio >= parrafo.length ()) {
                return lineas;
            }
            int sigue = inicio + anchura;
            if (sigue >= parrafo.length ()) {
                lineas.push_back (parrafo.substr (inicio, anchura));
                return lineas;
            }
            while (true) {
                if (parrafo.at (sigue) == ' ') {
                    lineas.push_back (parrafo.substr (inicio, sigue - inicio));
                    inicio = sigue + 1;
                    break;
                }
                sigue --;
            }
        }
    }


}