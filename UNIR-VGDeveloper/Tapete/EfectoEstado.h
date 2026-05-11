// proyecto: Grupal/Tapete
// archivo:  EfectoEstado.h
// versión:  1.0  (May-2026)


#pragma once


namespace tapete {


    // Tipos de efecto de estado que pueden afectar a un personaje
    enum class TipoEstado {
        VenenoDanoPorTurno,          // Aplica daño al personaje al final de cada turno
        ModificadorDefensa,          // Modifica todos los valores de defensa del personaje
        ModificadorAtaque,           // Modifica todos los valores de ataque del personaje
        ModificadorCosteHabilidades, // Modifica el coste en PA de las habilidades del personaje
    };


    // Representa un efecto de estado activo sobre un personaje
    struct EfectoEstado {
        TipoEstado tipo   {};  // tipo de efecto
        int        valor  {};  // magnitud del efecto (puede ser negativo)
        int        turnos {};  // turnos restantes de duración

        // Devuelve true si el efecto es perjudicial para el personaje
        bool esNegativo () const {
            return tipo == TipoEstado::VenenoDanoPorTurno || valor < 0;
        }
    };


}
