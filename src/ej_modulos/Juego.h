#pragma once
#ifndef juego_H
#define juego_H

#include "Jugador.h"
#include "Map.h"
#include "Enemigo.h"

using namespace std;
using namespace sf;

class Juego{
    public:
        int posx = 0, posy = 0;
        bool right = false, left = false, up = false, down = false;
        bool pulsado = false;
        int x = 0, y = 0, z = 0, j = 0;
        int xx = 0, yy = 0, xxx = 0, yyy = 0;
        int avanza = 0;
        float sgs = 0;
        Clock relojaso;
        bool dibujado = false;
        Juego(Vector2u tam_pantalla);
        ~Juego();
        void iniciar();
        void dibujar();
        void procesarEventos();
        void procesarColisiones();
        void procesarColisionesPengoSnoobee();
        void colisionBloqueMov(int, int);
        void choqueBloque();
        void choqueBloquePengo();
    private:
        bool gameover = false;
        RenderWindow *ventana;
        Jugador *j1;
        Event *evento;
        Map *maposo;
        Enemigo *enemy1;
        Enemigo *enemy2;
        Enemigo *enemy3;
};

#endif

