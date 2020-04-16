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
        bool right = false, left = false, down = false, up = false, mueveUp = false;
        Clock relojaso, relojero;
        float xxx = 0, yyy = 0, sgs = 0, sgs2 = 0;
        float velocidad = 0;
        float posicion = 0;
        int gridX = 0, gridY = 0;
        int direccion = 0;
        int x = 0, avanza = 0;
        Texture *tex;
        Sprite *enemy;
        int xx = 0, yy = 0;
        Enemigo(int, int);
        ~Enemigo();
        void cambiarSpriteR(int);
        void cambiarSpriteD(int);
        void cambiarSpriteU(int);
        void cambiarSpriteL(int);
        bool isMoving();
        void warp(int gridX, int gridY);
        void move(DirE);
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