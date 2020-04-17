#ifndef map_H
#define map_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

enum DirM {Upa, Righta, Downa, Lefta, Staya};

class Map{
    public:
        float xxx = 0, yyy = 0;
        float velocidad = 0;
        int gridX = 0, gridY = 0;
        bool intersecta = false;
        Clock reloj;
        float sgs = 0;
        int cont2 = 0;
        int posx = 0, posy = 0;
        int matrixMapa[16][16]={
            {0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0},
            {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5},
            {3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 5},
            {3, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 5},
            {3, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 5},
            {3, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 6, 0, 1, 5},
            {3, 0, 1, 0, 1, 6, 0, 1, 0, 0, 0, 0, 1, 0, 1, 5},
            {3, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 5},
            {3, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 5},
            {3, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 5},
            {3, 0, 1, 0, 0, 1, 0, 0, 0, 1, 6, 0, 1, 0, 1, 5},
            {3, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 5},
            {3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 5},
            {3, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 5},
            {3, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 5},
            {0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0}
        };
        Texture *tex2;
        Sprite* sprites[16][16];
        Map();  
        ~Map();
        bool isMoving();
        /*
        void warp(int, int);
        void move(DirM);
        void update(bool, int, int);
        */
        void dibujarMapa(RenderWindow&);
        /*
        void colisionBloqueMov(bool, int, int);
        */
        //bool update(bool, int, int);
};

#endif