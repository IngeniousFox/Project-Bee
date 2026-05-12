// proyecto: Grupal/Tapete
// archivo:  EfectoEstado.h
// versión:  1.0  (May-2026)


#pragma once


namespace tapete {


    // Tipos de efecto de estado que pueden afectar a un personaje
    enum class TipoEstado {
        VenenoDanoPorTurno,              // Aplica daño al personaje al final de cada turno
        ModificadorDefensa,              // Modifica (suma) todos los valores de defensa del personaje
        ModificadorAtaque,               // Modifica (suma) todos los valores de ataque del personaje
        ModificadorCosteHabilidades,     // Modifica (suma, puede ser negativo) el coste en PA de las habilidades
        MultiplicadorCosteHabilidades,   // Multiplica el coste en PA de las habilidades (valor >= 1)
        HiloTitiritero,                  // Meta-efecto: el rival controla este personaje hasta fin de ronda
    };


    // Representa un efecto de estado activo sobre un personaje
    //
    // Duración especial:
    //   turnos > 0  →  expira normalmente al llegar a 0 con procesaEstados()
    //   turnos = -1 →  "hasta fin de ronda": procesaEstados() lo ignora;
    //                  solo se elimina con limpiaEstados() al restaurar personajes
    struct EfectoEstado {
        TipoEstado tipo   {};  // tipo de efecto
        int        valor  {};  // magnitud del efecto (puede ser negativo)
        int        turnos {};  // turnos restantes de duración (ver convención arriba)

        // Devuelve true si el efecto es perjudicial para el personaje
        bool esNegativo () const {
            return tipo == TipoEstado::VenenoDanoPorTurno || valor < 0;
        }
    };


}
