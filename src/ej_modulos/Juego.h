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
        bool pulsado = false, pulsadoD = false, pulsadoA = false, pulsadoDown = false;
        bool esGolpeado = false, esGolpeado2 = false, esGolpeado3 = false;
        int x = 0, y = 0, z = 0, j = 0;
        bool izda = false, arriba = false, dreta = false, abajo = false;
        int xx = 0, yy = 0, xxd = 0, yyd = 0, xxdd = 0, yydd = 0, xxx = 0, yyy = 0;
        int ux = 0, uy = 0, uxx = 0, uyy = 0, dx = 0, dy = 0, dxx = 0, dyy = 0;
        int avanza = 0;
        int posAnt = 0, posDesp = 0, posAntDe = 0, posDespDe = 0, posAntUp = 0, posDespUp = 0, posAntDo = 0, posDespDo = 0;
        int contIt = 0, conti = 0, contiD = 0, contiA = 0, contiAb = 0;
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
        void choqueBloqueIz();
        void choqueBloqueDe();
        void choqueBloqueUp();
        void choqueBloqueDown();
        void choqueBloquePengoIz();
        void choqueBloquePengoDe();
        void choqueBloquePengoUp();
        void choqueBloquePengoDown();
    private:
        bool gameover = false;
        RenderWindow *ventana;
        Jugador *j1;
        Event *evento;
        Map *maposo;
        Enemigo *enemigos[3];
};

#endif

