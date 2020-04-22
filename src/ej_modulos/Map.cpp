#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

#define kVel 0.04

#include "Map.h"

Map::Map(int matriz[16][16]){
    tex2 = new Texture();
    if (!tex2->loadFromFile("resources/mapa.jpeg")) {
        std::cerr << "Error cargando la imagen mapa.jpeg";
        exit(0);
    }
    tex = new Texture(); 
    if (!tex->loadFromFile("resources/mapaza.jpeg")) {
        std::cerr << "Error cargando la imagen mapaza.jpeg";
        exit(0);
    }
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            if(matriz[j][i] == 0){
                sprites[j][i] = NULL;
            }
            else if(matriz[j][i] == 1){
                sprites[j][i] = new Sprite(*tex);    
                sprites[j][i]->setOrigin(8, 8);
                sprites[j][i]->setTextureRect(sf::IntRect(251.5, 151.5, 16, 16));
                sprites[j][i]->setPosition((i+1) * 16, (j+2) * 16);
            }
            else if(matriz[j][i] == 2){ 
                sprites[j][i] = new Sprite(*tex2);    
                sprites[j][i]->setOrigin(8, 8);
                sprites[j][i]->setTextureRect(sf::IntRect(16, 16, 16, 16));
                sprites[j][i]->setPosition((i+1) * 16, (j+2) * 16);
            }
            else if(matriz[j][i] == 3){ 
                sprites[j][i] = new Sprite(*tex2);    
                sprites[j][i]->setOrigin(8, 8);
                sprites[j][i]->setTextureRect(sf::IntRect(32, 0, 16, 16));
                sprites[j][i]->setPosition((i+1) * 16, (j+2) * 16);
            }
            else if(matriz[j][i] == 4){  
                sprites[j][i] = new Sprite(*tex2);    
                sprites[j][i]->setOrigin(8, 8);
                sprites[j][i]->setTextureRect(sf::IntRect(32, 16, 16, 16));
                sprites[j][i]->setPosition((i+1) * 16, (j+2) * 16);
            }
            else if(matriz[j][i] == 5){ 
                sprites[j][i] = new Sprite(*tex2);    
                sprites[j][i]->setOrigin(8, 8);
                sprites[j][i]->setTextureRect(sf::IntRect(48, 0, 16, 16));
                sprites[j][i]->setPosition((i+1) * 16, (j+2) * 16);
            }
            else if(matriz[j][i] == 6){ 
                sprites[j][i] = new Sprite(*tex2);    
                sprites[j][i]->setOrigin(8, 8);
                sprites[j][i]->setTextureRect(sf::IntRect(0, 16, 16, 16));
                sprites[j][i]->setPosition((i+1) * 16, (j+2) * 16);
            }
        }
    }
}

Map::~Map(){

}

void Map::dibujarMapa(RenderWindow &window){
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            if(sprites[j][i] != nullptr){
                window.draw(*sprites[j][i]);
            }
        }
    }
}