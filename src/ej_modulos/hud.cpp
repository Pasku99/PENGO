#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

#include "hud.h" 

    hud::hud(){
        texti = new Texture();
        if (!texti->loadFromFile("resources/indice2.jpeg")) {
            std::cerr << "Error cargando la imagen indice2.jpeg";
            exit(0);
        }

        pengui[0] = new Sprite(*texti);
        pengui[1] = new Sprite(*texti);
        pengui[2] = new Sprite(*texti);

        texti2 = new Texture();
        if (!texti2->loadFromFile("resources/indice2xx.png")) {
            std::cerr << "Error cargando la imagen indice2xx.png";
            exit(0);
        }

        titulo = new Sprite(*texti2);
        //Le pongo el centroide donde corresponde
        pengui[0]->setOrigin(8, 8);
        pengui[1]->setOrigin(8, 8);
        pengui[2]->setOrigin(8, 8);

        titulo->setOrigin(72, 32);
        //Cojo el sprite que me interesa por defecto del sheet
        pengui[0]->setTextureRect(sf::IntRect(18, 150, 16, 16));
        pengui[1]->setTextureRect(sf::IntRect(18, 150, 16, 16));
        pengui[2]->setTextureRect(sf::IntRect(18, 150, 16, 16));

        titulo->setTextureRect(sf::IntRect(0, 8, 144, 64));

        pengui[0]->setPosition(32, 288);
        pengui[1]->setPosition(48, 288);
        pengui[2]->setPosition(64, 288);

        titulo->setScale(0.5, 0.5);
        titulo->setPosition(144, 294);
    }

    hud::~hud(){

    }

    void hud::Draw1(RenderWindow &window){
        window.draw(*pengui[0]);
    }

    void hud::Draw2(RenderWindow &window){
        window.draw(*pengui[1]);
    }

    void hud::Draw3(RenderWindow &window){
        window.draw(*pengui[2]);
    }

    void hud::DrawTitulo(RenderWindow &window){
        window.draw(*titulo);
    }