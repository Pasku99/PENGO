#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

#define kVel 0.04

#include "Map.h"

Map::Map(){
    tex2 = new Texture();
    if (!tex2->loadFromFile("resources/mapa.jpeg")) {
        std::cerr << "Error cargando la imagen mapa.jpeg";
        exit(0);
    } 
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            if(matrixMapa[j][i] == 0){
                sprites[j][i] = NULL;
            }
            else if(matrixMapa[j][i] == 1){
                sprites[j][i] = new Sprite(*tex2);    
                sprites[j][i]->setOrigin(8, 8);
                sprites[j][i]->setTextureRect(sf::IntRect(16, 0, 16, 16));
                sprites[j][i]->setPosition((i+8) * 16, (j+8) * 16);
            }
            else if(matrixMapa[j][i] == 2){ 
                sprites[j][i] = new Sprite(*tex2);    
                sprites[j][i]->setOrigin(8, 8);
                sprites[j][i]->setTextureRect(sf::IntRect(16, 16, 16, 16));
                sprites[j][i]->setPosition((i+8) * 16, (j+8) * 16);
            }
            else if(matrixMapa[j][i] == 3){ 
                sprites[j][i] = new Sprite(*tex2);    
                sprites[j][i]->setOrigin(8, 8);
                sprites[j][i]->setTextureRect(sf::IntRect(32, 0, 16, 16));
                sprites[j][i]->setPosition((i+8) * 16, (j+8) * 16);
            }
            else if(matrixMapa[j][i] == 4){  
                sprites[j][i] = new Sprite(*tex2);    
                sprites[j][i]->setOrigin(8, 8);
                sprites[j][i]->setTextureRect(sf::IntRect(32, 16, 16, 16));
                sprites[j][i]->setPosition((i+8) * 16, (j+8) * 16);
            }
            else if(matrixMapa[j][i] == 5){ 
                sprites[j][i] = new Sprite(*tex2);    
                sprites[j][i]->setOrigin(8, 8);
                sprites[j][i]->setTextureRect(sf::IntRect(48, 0, 16, 16));
                sprites[j][i]->setPosition((i+8) * 16, (j+8) * 16);
            }
            else if(matrixMapa[j][i] == 6){ 
                sprites[j][i] = new Sprite(*tex2);    
                sprites[j][i]->setOrigin(8, 8);
                sprites[j][i]->setTextureRect(sf::IntRect(0, 16, 16, 16));
                sprites[j][i]->setPosition((i+8) * 16, (j+8) * 16);
            }
        }
    }
}

Map::~Map(){

}

void Map::dibujarMapa(RenderWindow &window){
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            if(sprites[j][i] != NULL){
                //sprites[j][i]->setPosition((i+4) * 16, 200);
                // cout << sprites[j][i]->getPosition().x << endl;
                window.draw(*sprites[j][i]);
            }
        }
    }
}

void Map::update(bool pulsado, int x, int y){
    if(pulsado == true){
        sprites[x][y]->move(-kVel, 0);
    }
}
