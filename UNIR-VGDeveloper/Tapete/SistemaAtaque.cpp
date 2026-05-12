// proyecto: Grupal/Tapete
// arhivo:   SistemaAtaque.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {


    SistemaAtaque::SistemaAtaque (JuegoMesaBase * juego) {
        this->juego = juego;
    }


    SistemaAtaque::~SistemaAtaque () {
        juego = nullptr;
        atacante_ = nullptr;
        habilidad_ = nullptr;
        //lista_oponentes.clear ();
    }


    const std::vector <GradoEfectividad *> & SistemaAtaque::efectividades () const {
        return grados_efectividad;
    }


    void SistemaAtaque::agregaEfectividad (GradoEfectividad * elemento) {
        grados_efectividad.push_back (elemento);
    }


    ActorPersonaje * SistemaAtaque::atacante () const {
        return atacante_;
    }


    Habilidad * SistemaAtaque::habilidad () const {
        return habilidad_;
    }


    const std::vector <SistemaAtaque::AtaqueOponente> & SistemaAtaque::ataquesOponente () const {
        return ataques_oponente;
    }


    const std::vector <SistemaAtaque::CuracionOponente> & SistemaAtaque::curacionesOponente () const {
        return curaciones_oponente;
    }


    const std::vector <SistemaAtaque::CambioEfecto> & SistemaAtaque::cambiosEfecto () const {
        return cambios_efecto;
    } 


    // Cálculo para una habilidad "auto-aplicada":
    void SistemaAtaque::calcula (
            ActorPersonaje * atacante, 
            Habilidad *      habilidad) {
        assert (habilidad->tipoEnfoque () == EnfoqueHabilidad::si_mismo);
        assert (habilidad->tipoAcceso  () == AccesoHabilidad::ninguno);
        assert (habilidad->antagonista () == Antagonista::si_mismo);  
        //
        reinicia ();
        this->atacante_  = atacante;
        this->habilidad_ = habilidad;
        //
        // ver: 'ValidacionJuego::EstadisticasHabilidades' '(i) (k)'
        if (habilidad_->efectosAtaque  ().size () == 0 &&
            habilidad_->efectosDefensa ().size () == 0 &&
            habilidad_->efectosEstado  ().size () == 0   ) {
            throw std::logic_error {
                    "Sistema de ataque mal configurado: habilidad auto-aplicada sin efectos definidos"};
        }
        //
        for (const std::pair <TipoAtaque *, int> & pareja : habilidad_->efectosAtaque ()) {
            CambioEfecto registro {};
            //                                                                                      
            registro.tipo_ataque         = pareja.first;   //get<0> (pareja);
            registro.valor_cambio_ataque = pareja.second;  //get<1> (pareja);
            registro.tipo_defensa        = nullptr;
            //
            // ver 'ValidacionJuego::EstadisticasPersonajes' '(d))
            if (! atacante_->apareceAtaque (registro.tipo_ataque)) {
                throw std::logic_error {
                        "Sistema de ataque mal configurado, aplicando efecto en ataque: tipo de ataque no admitido por el atacante"};
            }
            registro.valor_origen_ataque = atacante_->valorAtaque (registro.tipo_ataque);
            atacante_->cambiaAtaque (registro.tipo_ataque, registro.valor_cambio_ataque);
            //
            registro.valor_final_ataque = atacante_->valorAtaque (registro.tipo_ataque);
            //
            cambios_efecto.push_back (registro);
        }
        for (const std::pair <TipoDefensa *, int> & pareja : habilidad_->efectosDefensa ()) {
            CambioEfecto registro {};
            //
            registro.tipo_ataque          = nullptr;
            registro.tipo_defensa         = pareja.first;   //get<0> (pareja);
            registro.valor_cambio_defensa = pareja.second;  //get<1> (pareja);
            //
            // ver 'ValidacionJuego::EstadisticasPersonajes' '(b))
            if (! atacante_->apareceDefensa (registro.tipo_defensa)) {
                throw std::logic_error {
                        "Sistema de ataque mal configurado, aplicando efecto en defensa: tipo de defensa no admitido por el atacante"};
            }
            registro.valor_origen_defensa = atacante_->valorDefensa (registro.tipo_defensa);
            atacante_->cambiaDefensa (registro.tipo_defensa, registro.valor_cambio_defensa);
            //
            registro.valor_final_defensa = atacante_->valorDefensa (registro.tipo_defensa);
            //
            cambios_efecto.push_back (registro);
        }
        // Aplica los efectos de estado auto-infligidos (buffs/debuffs persistentes por turnos)
        for (const EfectoEstado & efecto : habilidad_->efectosEstado ()) {
            atacante_->aplicaEstado (efecto.tipo, efecto.valor, efecto.turnos);
        }
    }


    // Cálculo para una habilidad "de ataque" o "de curación", que "afecta a personaje"
    // Usado cuando la habilidad tiene: 
    //      tipoEnfoque = EnfoqueHabilidad::personaje
    //      tipoAcceso  = { AccesoHabilidad::directo, AccesoHabilidad::indirecto }
    //      antagonista = { Antagonista::oponente, Antagonista::aliado }
    // Clasificación de la habilidad:
    //      antagonista = Antagonista::oponente => "de ataque"
    //      antagonista = Antagonista::aliado   => "de curación"
    void SistemaAtaque::calcula (
            ActorPersonaje * atacante, 
            Habilidad *      habilidad,
            ActorPersonaje * oponente, 
            int              aleatorio_100) {
        assert (habilidad->tipoEnfoque () == EnfoqueHabilidad::personaje);
        assert (habilidad->tipoAcceso  () == AccesoHabilidad::directo ||
                habilidad->tipoAcceso  () == AccesoHabilidad::indirecto );
        assert (habilidad->antagonista () == Antagonista::oponente ||
                habilidad->antagonista () == Antagonista::aliado     );
        //        
        reinicia ();
        this->atacante_  = atacante;
        this->habilidad_ = habilidad;
        //
        if (habilidad_->antagonista () == Antagonista::oponente) {
            calculaAtaque (oponente, aleatorio_100);
        } else {
            calculaCuracion (oponente);
        }
    }


    // Cálculo para una habilidad "de ataque" o "de curación", que "afecta a un área"
    // Usado cuando la habilidad tiene: 
    //      tipoEnfoque = EnfoqueHabilidad::area
    //      tipoAcceso  = { AccesoHabilidad::directo, AccesoHabilidad::indirecto }
    //      antagonista = { Antagonista::oponente, Antagonista::aliado }
    // Clasificación de la habilidad:
    //      antagonista = Antagonista::oponente => "de ataque"
    //      antagonista = Antagonista::aliado   => "de curación"
    void SistemaAtaque::calcula (
            ActorPersonaje *               atacante, 
            Habilidad *                    habilidad,
            std::vector <ActorPersonaje *> lista_oponentes, 
            int                            aleatorio_100) {
        assert (habilidad->tipoEnfoque () == EnfoqueHabilidad::area);
        assert (habilidad->tipoAcceso  () == AccesoHabilidad::directo ||
                habilidad->tipoAcceso  () == AccesoHabilidad::indirecto );
        assert (habilidad->antagonista () == Antagonista::oponente ||
                habilidad->antagonista () == Antagonista::aliado     );
        //
        reinicia ();
        this->atacante_  = atacante;
        this->habilidad_ = habilidad;
        //
        ataques_oponente   .clear ();
        curaciones_oponente.clear ();
        cambios_efecto     .clear ();
        //
        for (ActorPersonaje * oponente : lista_oponentes) {
            if (habilidad_->antagonista () == Antagonista::oponente) {
                calculaAtaque (oponente, aleatorio_100);
            } else {
                calculaCuracion (oponente);
            }
        }
    }


    void SistemaAtaque::reinicia () {
        atacante_  = nullptr;
        habilidad_ = nullptr;
        ataques_oponente   .clear ();
        curaciones_oponente.clear ();
        cambios_efecto     .clear ();
    }


    // Cálculo para una habilidad "de ataque" y para uno de los personajes afectados
    void SistemaAtaque::calculaAtaque (ActorPersonaje * oponente, int aleatorio_100) {
        assert (habilidad_->antagonista () == Antagonista::oponente);
        //
        AtaqueOponente registro {};
        registro.oponente          = oponente;
        registro.celda_empuje_final = oponente->sitioFicha ();
        //
        registro.tipo_ataque = habilidad_->tipoAtaque ();
        //
        // Habilidades de debuff puro: sin tipo de ataque ni daño, solo aplican estados
        if (registro.tipo_ataque == nullptr) {
            registro.vitalidad_origen = oponente->vitalidad ();
            registro.vitalidad_final  = oponente->vitalidad ();
            // Aplica los efectos de estado (maldición/debuff), siempre acierta
            for (const EfectoEstado & efecto : habilidad_->efectosEstado ()) {
                if (registro.vitalidad_final > 0) {
                    oponente->aplicaEstado (efecto.tipo, efecto.valor, efecto.turnos);
                }
            }
            ataques_oponente.push_back (registro);
            return;
        }
        //
        // véase: 'ValidacionJuego::EstadisticasPersonajes' '(a)'
        if (! atacante_->apareceAtaque (registro.tipo_ataque)) {
            throw std::logic_error {"Sistema de ataque mal configurado, aplicando ataque: tipo de ataque no admitido por el atacante"};
        }
        registro.valor_ataque = atacante_->valorAtaque (registro.tipo_ataque);
        // véase: 'ValidacionJuego::EstadisticasPersonajes' '(a)'
        if (registro.valor_ataque <= 0 || ActorPersonaje::maximaVitalidad < registro.valor_ataque) {
            throw std::logic_error {"Sistema de ataque mal configurado, aplicando ataque: valor de ataque inválido"};
        }
        //
        registro.tipo_defensa = habilidad_->tipoDefensa ();
        // véase: 'ValidacionJuego::EstadisticasHabilidades' '(e)'
        if (registro.tipo_defensa == nullptr) {
            throw std::logic_error {"Sistema de ataque mal configurado, aplicando ataque: tipo de defensa no establecido en la habilidad"};
        }
        // véase: 'ValidacionJuego::EstadisticasPersonajes' 'b)'
        if (! oponente->apareceDefensa (registro.tipo_defensa)) {
            throw std::logic_error {"Sistema de ataque mal configurado, aplicando ataque: tipo de ataque no admitido por el oponente"};
        }
        registro.valor_defensa = oponente->valorDefensa (registro.tipo_defensa);
        // véase: 'ValidacionJuego::EstadisticasPersonajes' '(b)'
        if (registro.valor_defensa <= 0 || ActorPersonaje::maximaVitalidad < registro.valor_defensa) {
            throw std::logic_error {"Sistema de ataque mal configurado, aplicando ataque: valor de defensa inválido"};
        }
        //
        registro.ventaja            = registro.valor_ataque - registro.valor_defensa;
        registro.aleatorio_100      = aleatorio_100;
        registro.valor_final_ataque = registro.ventaja + registro.aleatorio_100;
        //
        // véase: 'ValidacionJuego::SistemaAtaque'
        if (grados_efectividad.size () == 0) {
            throw std::logic_error {"Sistema de ataque mal configurado: grados de efectividad no configurados"};
        }
        //
        // véase: 'ValidacionJuego::SistemaAtaque'
        for (GradoEfectividad * efectividad : grados_efectividad) {
            if (registro.valor_final_ataque <= efectividad->valorSuperioAtaque ()) {
                registro.efectividad    = efectividad;
                registro.porciento_dano = efectividad->porcentajeDano ();
                break;
            }
        }
        //
        registro.tipo_dano  = habilidad_->tipoDano ();
        registro.valor_dano = habilidad_->valorDano ();
        //
        // Habilidades con daño real
        if (registro.tipo_dano != nullptr && registro.valor_dano > 0) {
            registro.valor_ajustado_dano = (int) (registro.valor_dano * (((float) registro.porciento_dano) / 100.0f));
            //
            // véase: 'ValidacionJuego::EstadisticasPersonajes' '(c)'
            if (! oponente->apareceReduceDano (registro.tipo_dano)) {
                throw std::logic_error {"Sistema de ataque mal configurado, aplicando ataque: reducción de daño no establecido en el oponente"};
            }
            registro.valor_reduce_dano = oponente->valorReduceDano (registro.tipo_dano);
            registro.valor_final_dano  = std::max (0, registro.valor_ajustado_dano - registro.valor_reduce_dano);
            //
            registro.vitalidad_origen = oponente->vitalidad ();
            registro.vitalidad_final  = oponente->vitalidad ();
            if (registro.vitalidad_final > 0) {
                registro.vitalidad_final -= registro.valor_final_dano;
                if (registro.vitalidad_final < 0) {
                    registro.vitalidad_final = 0;
                }
                if (registro.vitalidad_final > ActorPersonaje::maximaVitalidad) {
                    registro.vitalidad_final = ActorPersonaje::maximaVitalidad;
                }
                oponente->ponVitalidad (registro.vitalidad_final);
            }
        } else {
            registro.vitalidad_origen = oponente->vitalidad ();
            registro.vitalidad_final  = oponente->vitalidad ();
        }
        //
        // Aplica los efectos de estado de la habilidad sobre el oponente (si sigue vivo)
        if (registro.porciento_dano > 0) {
            for (const EfectoEstado & efecto : habilidad_->efectosEstado ()) {
                if (registro.vitalidad_final > 0) {
                    oponente->aplicaEstado (efecto.tipo, efecto.valor, efecto.turnos);
                }
            }
        }
        //
        // Devuelve el vecino hex de 'desde' que está más cerca (en píxeles) de 'hacia'.
        // Necesario para desplazar paso a paso en una dirección hex arbitraria, ya que el
        // delta raw entre dos celdas no adyacentes NO es un vector unitario hex.
        auto proximaHacia = [] (Coord desde, Coord hacia) -> Coord {
            const std::array <Coord, 6> vecinos {{
                Coord (desde.fila () - 2, desde.coln ()    ),
                Coord (desde.fila () - 1, desde.coln () + 1),
                Coord (desde.fila () + 1, desde.coln () + 1),
                Coord (desde.fila () + 2, desde.coln ()    ),
                Coord (desde.fila () + 1, desde.coln () - 1),
                Coord (desde.fila () - 1, desde.coln () - 1),
            }};
            Vector objetivo = RejillaTablero::centroHexagono (hacia);
            Coord  mejor    = desde;
            float  dist_min = 1e9f;
            for (const Coord & c : vecinos) {
                if (! CalculoCaminos::celdaEnTablero (c)) {
                    continue;
                }
                float d = unir2d::norma (RejillaTablero::centroHexagono (c) - objetivo);
                if (d < dist_min) {
                    dist_min = d;
                    mejor    = c;
                }
            }
            return mejor;
        };
        //
        // Empuje: desplaza al oponente alejándolo del atacante, un paso hex por iteración
        if (habilidad_->celdasEmpuje () > 0 && registro.vitalidad_final > 0) {
            Coord celda_actual = oponente->sitioFicha ();
            // Celda ficticia "detrás" del atacante para que la dirección sea hacia ella
            // equivale a: partir del oponente, buscar el vecino más alejado del atacante
            // → usamos la celda opuesta: la que está más lejos del atacante desde la actual
            auto proximaLejos = [&] (Coord desde) -> Coord {
                const std::array <Coord, 6> vecinos {{
                    Coord (desde.fila () - 2, desde.coln ()    ),
                    Coord (desde.fila () - 1, desde.coln () + 1),
                    Coord (desde.fila () + 1, desde.coln () + 1),
                    Coord (desde.fila () + 2, desde.coln ()    ),
                    Coord (desde.fila () + 1, desde.coln () - 1),
                    Coord (desde.fila () - 1, desde.coln () - 1),
                }};
                Vector atacante_px = RejillaTablero::centroHexagono (atacante_->sitioFicha ());
                Coord  mejor       = desde;
                float  dist_max    = -1.0f;
                for (const Coord & c : vecinos) {
                    if (! CalculoCaminos::celdaEnTablero (c)) {
                        continue;
                    }
                    float d = unir2d::norma (RejillaTablero::centroHexagono (c) - atacante_px);
                    if (d > dist_max) {
                        dist_max = d;
                        mejor    = c;
                    }
                }
                return mejor;
            };
            for (int paso = 0; paso < habilidad_->celdasEmpuje (); ++ paso) {
                Coord celda_sig = proximaLejos (celda_actual);
                if (celda_sig == celda_actual) {
                    break;
                }
                if (CalculoCaminos::celdaEnMuro (juego, celda_sig)) {
                    break;
                }
                bool ocupada = false;
                for (ActorPersonaje * p : juego->personajes ()) {
                    if (p != oponente && p->sitioFicha () == celda_sig) {
                        ocupada = true;
                        break;
                    }
                }
                if (ocupada) {
                    break;
                }
                celda_actual = celda_sig;
            }
            oponente->ponSitioFicha (celda_actual);
            registro.celda_empuje_final = celda_actual;
        }
        //
        // Atracción: desplaza al oponente hacia el atacante, un paso hex por iteración
        // Solo actúa si el ataque impactó (porciento_dano > 0)
        if (habilidad_->celdasAtraccion () > 0 && registro.porciento_dano > 0 && registro.vitalidad_final > 0) {
            Coord celda_actual = oponente->sitioFicha ();
            for (int paso = 0; paso < habilidad_->celdasAtraccion (); ++ paso) {
                Coord celda_sig = proximaHacia (celda_actual, atacante_->sitioFicha ());
                if (celda_sig == celda_actual) {
                    break;
                }
                if (CalculoCaminos::celdaEnMuro (juego, celda_sig)) {
                    break;
                }
                // Detener si hay otro personaje (incluido el atacante), dejando al oponente adyacente
                bool ocupada = false;
                for (ActorPersonaje * p : juego->personajes ()) {
                    if (p != oponente && p->sitioFicha () == celda_sig) {
                        ocupada = true;
                        break;
                    }
                }
                if (ocupada) {
                    break;
                }
                celda_actual = celda_sig;
            }
            oponente->ponSitioFicha (celda_actual);
            registro.celda_empuje_final = celda_actual;
        }
        //
        ataques_oponente.push_back (registro);
    }


    // Cálculo para una habilidad "de curación" y para uno de los personajes afectados
    void SistemaAtaque::calculaCuracion (ActorPersonaje * oponente) {
        // la habilidad es de curación, el oponente puede ser del mismo equipo o no
        assert (habilidad_->antagonista () == Antagonista::aliado);
        //
        CuracionOponente registro {};
        registro.oponente = oponente;
        //
        registro.vitalidad_origen = oponente->vitalidad ();
        registro.vitalidad_final  = oponente->vitalidad ();
        //
        // Curación de vitalidad (si la habilidad tiene valor de curación)
        if (habilidad_->valorCuracion () > 0 && registro.vitalidad_final > 0) {
            registro.valor_curacion   = habilidad_->valorCuracion ();
            registro.vitalidad_final += registro.valor_curacion;
            if (registro.vitalidad_final < 0) {
                registro.vitalidad_final = 0;
            }
            if (registro.vitalidad_final > ActorPersonaje::maximaVitalidad) {
                registro.vitalidad_final = ActorPersonaje::maximaVitalidad;
            }
            oponente->ponVitalidad (registro.vitalidad_final);
        }
        //
        // Aplica los efectos de estado de la habilidad al objetivo (buff)
        if (registro.vitalidad_final > 0) {
            for (const EfectoEstado & efecto : habilidad_->efectosEstado ()) {
                oponente->aplicaEstado (efecto.tipo, efecto.valor, efecto.turnos);
            }
        }
        //
        curaciones_oponente.push_back (registro);
    }


    // Cálculo para una habilidad "de equipo" que afecta a todos los aliados del atacante
    void SistemaAtaque::calcula (
            ActorPersonaje *               atacante,
            Habilidad *                    habilidad,
            std::vector <ActorPersonaje *> aliados) {
        assert (habilidad->tipoEnfoque () == EnfoqueHabilidad::equipo);
        assert (habilidad->tipoAcceso  () == AccesoHabilidad::ninguno);
        assert (habilidad->antagonista () == Antagonista::aliado);
        //
        reinicia ();
        this->atacante_  = atacante;
        this->habilidad_ = habilidad;
        //
        for (ActorPersonaje * aliado : aliados) {
            calculaCuracion (aliado);
        }
    }


}