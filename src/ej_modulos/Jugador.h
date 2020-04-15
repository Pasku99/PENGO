#ifndef jugador_H
#define jugador_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

enum Dir {Up, Right, Down, Left, Stay};

class Jugador{
    public:
        float xxx = 0, yyy = 0;
        float velocidad = 0;
        int gridX = 0, gridY = 0;
        int x = 0;
        Texture *tex;
        Sprite *jugador;
        int xx = 0, yy = 0;
        Jugador();
        ~Jugador();
        bool isMoving();
        void warp(int gridX, int gridY);
        void move(Dir);
        void update();
        Vector2f getCoors();
        /*
        void movimientoR(int);
        void movimientoL(int);
        void movimientoUp(int);
        void movimientoDown(int);
        */
        Sprite *getSprite();
        void restartSprite();
        void hacerTransparente();
        void Draw(RenderWindow&);
        int getVidas();  
    private:
        int vidas = 0;  
};

#endif