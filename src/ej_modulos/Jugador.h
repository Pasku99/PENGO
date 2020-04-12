#ifndef jugador_H
#define jugador_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Jugador{
    public:
        int x = 0;
        Texture *tex;
        Sprite *jugador;
        int xx = 0, yy = 0;
        Jugador();
        void movimiento(int);
        Sprite *getSprite();
        void Update(RenderWindow&);
        void restartSprite();
        void Draw(RenderWindow&);    
};

#endif