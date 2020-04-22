#ifndef hud_H
#define hud_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class hud{    
    public:
        hud();
        ~hud();
        void Draw1(RenderWindow&);
        void Draw2(RenderWindow&);
        void Draw3(RenderWindow&);
        void DrawTitulo(RenderWindow&);
    private:
        Texture *texti;
        Texture *texti2;
        Sprite *pengui[3];
        Sprite *titulo;
};

#endif