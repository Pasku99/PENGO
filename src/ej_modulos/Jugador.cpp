#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

#define kVel 20

#include "Jugador.h"  
  
    Jugador::Jugador(){
        tex = new Texture();
        if (!tex->loadFromFile("resources/pengo.png")) {
            std::cerr << "Error cargando la imagen pengo.png";
            exit(0);
        } 
        jugador = new Sprite(*tex);
        //Le pongo el centroide donde corresponde
        jugador->setOrigin(131, 25);
        //Cojo el sprite que me interesa por defecto del sheet
        jugador->setTextureRect(sf::IntRect(96, 1, 16, 15));
        
        // Lo dispongo a la derecha de la pantalla
        //spriteb->setPosition(xx, yy);
        jugador->setPosition(400, 300);
    }

    void Jugador::movimiento(){
        jugador->setTextureRect(sf::IntRect(120, 18, 22, 14));
        jugador->move(-kVel, 0);
        jugador->setScale(1, 1);
    }

    void Jugador::hacerTransparente(){
        jugador->setColor(Color::Transparent);
    }

    void Jugador::Draw(RenderWindow &window){
        window.draw(*jugador);
    }

    void Jugador::restartSprite(){
        jugador->setColor(Color(255,255,255));
    }


    Sprite *Jugador::getSprite(){
        return jugador;
    }