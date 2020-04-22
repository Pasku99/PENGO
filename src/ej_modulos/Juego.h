#pragma once
#ifndef juego_H
#define juego_H

#include "Jugador.h"
#include "Map.h"
#include "Enemigo.h"
#include "hud.h"
#include <sstream>

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
        int comienza = 0, animaAvanza = 0, empujar = 0;
        float sgs = 0, sgs2 = 0, sgs3 = 0, sgsR = 0, sgsA = 0, animaEmpuja = 0;
        Clock relojaso, relojero, reloja, reiniciador;
        Clock nuevoEnemigo, relojAnimator, relojEmpujador;
        Clock andador;
        float puntuacion = 0;
        bool walkR = false;
        int andandico = 0; 
        int contaorR = 0;
        float sgsEnemy = 0, sgsAnd = 0;
        bool eliminao = false, eliminao2 = false, eliminao3 = false;
        bool dibujado = false, chocado = false, chocadoD = false, chocadoA = false, chocadoDo = false, espacio = false;
        bool firstTime = false, secondTime = false, secondTime2 = false, secondTime3 = false;
        int contMuertos = 0;
        bool juegoPasado = false, muere1 = false, muere2 = false, muere3 = false;
        bool dibujaisimo = false;
        bool restarteo = false, godmode = false, pulsarG = false;
        bool empujeR = false, empujeL = false, empujeD = false, empujeU = false;
        int contarRestarteo = 0, contadorG = 0;
        int cargaNivel = 0;
        Juego(Vector2u tam_pantalla);
        ~Juego();
        void iniciar();
        void inicializarTodo();
        void dibujar();
        void controlarHUD();
        void tablaPuntuaciones();
        void DrawPuntuaciones(RenderWindow&);
        void animacionAndarDerecha();
        void spriteAndarDerecha(int);
        void procesarEventos();
        void procesarColisiones();
        void procesarColisionesPengoSnoobee();
        void comprobarJuegoPasado();
        void regenerarSnoobee();
        void regenerarSnoobee2();
        void regenerarSnoobee3();
        void colisionBloqueMov(int, int);
        void animacionEmpujarIzda();
        void cambiarEmpujeIzda(int);
        void choqueBloqueIz();
        void cambiaAnimacionIz(int);
        void animacionEmpujarRight();
        void cambiarEmpujeRight(int);
        void choqueBloqueDe();
        void animacionDe();
        void animacionEmpujarUp();
        void cambiarEmpujeUp(int);
        void choqueBloqueUp();
        void animacionUp();
        void animacionEmpujarDown();
        void cambiarEmpujeDown(int);
        void choqueBloqueDown();
        void animacionDown();
        void choqueBloquePengoIz();
        void cambiaAnimacionDe(int);
        void choqueBloquePengoDe();
        void cambiaAnimacionUp(int);
        void choqueBloquePengoUp();
        void cambiaAnimacionDown(int);
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
        void EscribirTexto();
        bool creareloj = false;
        Clock relojpasando;
        int antepos = 256, postepos = 0;
    private:
        bool gameover = false;
        RenderWindow *ventana;
        Jugador *j1;
        Event *evento;
        Map *maposo;
        Map *maposo2;
        hud *hudio;
        Enemigo *enemigos[3];
        Sprite *guardado;
        Sprite *guardadoD;
        Sprite *guardadoA;
        Sprite *guardadoDo;
        Text *puntuar;
        Font *letra;
        Texture *texti = new Texture();
        int matrixMapa1[16][16]={
            {0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0},
            {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
            {3, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 5},
            {3, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 5},
            {3, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 5},
            {3, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 5},
            {3, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 5},
            {3, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 5},
            {3, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 5},
            {3, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 5},
            {3, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 5},
            {3, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 5},
            {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 5},
            {3, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 5},
            {3, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 5},
            {0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0}
        };

        int matrixMapa2[16][16]={
            {0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0},
            {3, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 5},
            {3, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 5},
            {3, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 5},
            {3, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 5},
            {3, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 5},
            {3, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 5},
            {3, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 5},
            {3, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 5},
            {3, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 5},
            {3, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 5},
            {3, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 5},
            {3, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 5},
            {3, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 5},
            {3, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 5},
            {0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0}
        };
};

#endif

