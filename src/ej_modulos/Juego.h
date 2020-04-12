#pragma once
#ifndef juego_H
#define juego_H

#include "Jugador.h"

using namespace std;
using namespace sf;

class Juego{
    public:
        int x = 0;
        Juego(Vector2u tam_pantalla);
        ~Juego();
        void iniciar();
        void dibujar();
        void procesarEventos();
    private:
        bool gameover = false;
        RenderWindow *ventana;
        Jugador *j1;
        Event *evento;
        Time *crono1;
        Clock *reloj1;
};

#endif

