#pragma once
#ifndef juego_H
#define juego_H

#include "Jugador.h"

using namespace std;
using namespace sf;

class Juego{
    public:
        Juego(Vector2u tam_pantalla);
        ~Juego();
        void iniciar();
    private:
        RenderWindow *ventana;
};

#endif

