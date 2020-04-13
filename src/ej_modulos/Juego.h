#pragma once
#ifndef juego_H
#define juego_H

#include "Jugador.h"
#include "Map.h"

using namespace std;
using namespace sf;

class Juego{
    public:
        int x = 0, y = 0, z = 0, j = 0;
        bool dibujado = false;
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
        Map *maposo;
};

#endif

