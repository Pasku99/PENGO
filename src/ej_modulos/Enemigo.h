#ifndef enemigo_H
#define enemigo_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"

using namespace std;
using namespace sf;

enum DirE {Arriba, Derecha, Abajo, Izquierda, Quedate};

class Enemigo{
    public:
        bool right = false, left = false, down = false, up = false;
        Clock relojaso;
        float xxx = 0, yyy = 0, sgs = 0;
        float velocidad = 0;
        int gridX = 0, gridY = 0;
        int x = 0, avanza = 0;
        Texture *tex;
        Sprite *enemy;
        int xx = 0, yy = 0;
        Enemigo(int, int);
        ~Enemigo();
        void cambiarSpriteR(int);
        void cambiarSpriteD(int);
        bool isMoving();
        void warp(int gridX, int gridY);
        //void movement(DirE);
        void update(Map*);
        void procesarColisionesEnemigo(Map*);
        Vector2f getCoors();
        Sprite *getSprite();
        void restartSprite();
        void hacerTransparente();
        void Draw(RenderWindow&);
        int getVidas();  
    private:
        int vidas = 0;  
};

#endif