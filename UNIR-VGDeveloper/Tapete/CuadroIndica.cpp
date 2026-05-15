// proyecto: Grupal/Tapete
// arhivo:   CuadroIndica.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {


    CuadroIndica::CuadroIndica (ActorTablero * actor_tablero) {
        this->actor_tablero = actor_tablero;
    }

    CuadroIndica::~CuadroIndica () {
        actor_tablero = nullptr;
    }


    void CuadroIndica::prepara () {
        rectangl_indica = new unir2d::Rectangulo ();
        trazos_indica   = new unir2d::Trazos ();
        texto_indica    = new unir2d::Texto ("DejaVuSans");
        rectangl_indica->ponIndiceZ (1);
        rectangl_indica->ponVisible (false);
        trazos_indica  ->ponIndiceZ (1);
        trazos_indica  ->ponVisible (false);
        texto_indica   ->ponIndiceZ (1);
        texto_indica   ->ponVisible (false);
        //
        actor_tablero->agregaDibujo (rectangl_indica);
        actor_tablero->agregaDibujo (rectangl_indica);
        actor_tablero->agregaDibujo (trazos_indica);
        actor_tablero->agregaDibujo (trazos_indica);
        actor_tablero->agregaDibujo (texto_indica);
        actor_tablero->agregaDibujo (texto_indica);
    }


    void CuadroIndica::libera () {
        delete texto_indica;
        texto_indica = nullptr;
        delete trazos_indica;
        trazos_indica = nullptr;
        delete rectangl_indica;
        rectangl_indica = nullptr;
    }


    void CuadroIndica::indica (Vector poscn, const wstring & cadena) {
        //
        texto_indica->ponTamano (12);
        texto_indica->ponColor (Color::Negro);
        texto_indica->ponCadena (cadena);
        float anchr = texto_indica->anchura ();
        //
        // Soporte multilínea: el alto del cuadro depende del número de líneas ('\n')
        int lineas = 1;
        for (wchar_t c : cadena) {
            if (c == L'\n') {
                ++ lineas;
            }
        }
        float alto = lineas * 16.0f + 6.0f;
        //
        // El anclaje original deja un cuadro de ~20 px justo encima del retrato.
        // Con varias líneas el cuadro se ancla por su base y crece hacia arriba,
        // para no tapar el retrato ni los paneles de habilidades.
        Vector pos = poscn - Vector {0.0f, alto - 20.0f};
        //
        rectangl_indica->ponPosicion (pos);
        rectangl_indica->ponBase (anchr + 8);
        rectangl_indica->ponAltura (alto);
        rectangl_indica->ponColor (colorIndica);
        //
        trazos_indica->ponPosicion (pos);
        trazos_indica->borraLineas ();
        float sup =  0.0f;
        float inf = alto;
        float der =  0.0f;
        float izq = anchr + 8;
        Vector sup_izq {izq, sup};
        Vector sup_der {der, sup};
        Vector inf_izq {izq, inf};
        Vector inf_der {der, inf};
        trazos_indica->agrega (unir2d::TrazoLinea {sup_izq, sup_der, Color::Negro});
        trazos_indica->agrega (unir2d::TrazoLinea {inf_izq, inf_der, Color::Negro});
        trazos_indica->agrega (unir2d::TrazoLinea {sup_izq, inf_izq, Color::Negro});
        trazos_indica->agrega (unir2d::TrazoLinea {sup_der, inf_der, Color::Negro});
        //
        texto_indica->ponPosicion (pos + Vector {4, 3});
        //
        rectangl_indica->ponVisible (true);
        trazos_indica  ->ponVisible (true);
        texto_indica   ->ponVisible (true);
    }


    void CuadroIndica::desindica () {
        rectangl_indica->ponVisible (false);
        trazos_indica  ->ponVisible (false);
        texto_indica   ->ponVisible (false);
    }


}