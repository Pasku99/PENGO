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
        bool entrando = false;
        int x = 0, y = 0, z = 0, j = 0;
        bool izda = false, arriba = false, dreta = false, abajo = false;
        bool reventao = false, toparao = false;
        int xx = 0, yy = 0, xxd = 0, yyd = 0, xxdd = 0, yydd = 0, xxx = 0, yyy = 0;
        int ux = 0, uy = 0, uxx = 0, uyy = 0, dx = 0, dy = 0, dxx = 0, dyy = 0;
        int avanza = 0, palante = 0;
        int posAnt = 0, posDesp = 0, posAntDe = 0, posDespDe = 0, posAntUp = 0, posDespUp = 0, posAntDo = 0, posDespDo = 0;
        int contIt = 0, conti = 0, contiD = 0, contiA = 0, contiAb = 0;
        int nuevax = 0, nuevay = 0;
        int comienza = 0;
        float sgs = 0, sgs2 = 0, sgs3 = 0, sgsR = 0;
        Clock relojaso, relojero, reloja, reiniciador;
        Clock nuevoEnemigo;
        float sgsEnemy = 0;
        bool eliminao = false, eliminao2 = false, eliminao3 = false;
        bool dibujado = false, chocado = false, chocadoD = false, chocadoA = false, chocadoDo = false, espacio = false;
        bool firstTime = false, secondTime = false;
        Juego(Vector2u tam_pantalla);
        ~Juego();
        void iniciar();
        void dibujar();
        void procesarEventos();
        void procesarColisiones();
        void procesarColisionesPengoSnoobee();
        void regenerarSnoobee();
        void regenerarSnoobee2();
        void regenerarSnoobee3();
        void colisionBloqueMov(int, int);
        void choqueBloqueIz();
        void choqueBloqueDe();
        void choqueBloqueUp();
        void choqueBloqueDown();
        void choqueBloquePengoIz();
        void choqueBloquePengoDe();
        void choqueBloquePengoUp();
        void choqueBloquePengoDown();
        void romperBloque();
        void romperBloqueD();
        void romperBloqueUp();
        void romperBloqueDown();
        void cambiarSprite(int, Sprite*);
        void cambiarSpriteR(int, Sprite*);
        void cambiarSpriteUp(int, Sprite*);
        void cambiarSpriteDown(int, Sprite*);
        void AnimacionPengoMuriendo();
        void SpriteMuerto(int);
    private:
        bool gameover = false;
        RenderWindow *ventana;
        Jugador *j1;
        Event *evento;
        Map *maposo;
        Enemigo *enemigos[3];
        Sprite *guardado;
        Sprite *guardadoD;
        Sprite *guardadoA;
        Sprite *guardadoDo;
        Texture *tex = new Texture();
};

#endif

