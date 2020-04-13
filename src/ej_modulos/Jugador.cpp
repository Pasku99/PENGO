#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

#define kVel 10

#include "Jugador.h"  
  
    Jugador::Jugador(){
        tex = new Texture();
        if (!tex->loadFromFile("resources/pengo.png")) {
            std::cerr << "Error cargando la imagen pengo.png";
            exit(0);
        } 
        jugador = new Sprite(*tex);
        //Le pongo el centroide donde corresponde
        jugador->setOrigin(104, 8.5);
        //Cojo el sprite que me interesa por defecto del sheet
        jugador->setTextureRect(sf::IntRect(96, 1, 16, 15));
        
        // Lo dispongo a la derecha de la pantalla
        //spriteb->setPosition(xx, yy);
        jugador->setPosition(400, 300);
    }

    void Jugador::movimientoR(int x){
        if(x == 0){
            jugador->setTextureRect(sf::IntRect(96, 1, 16, 15));
            jugador->move(kVel, 0);
            jugador->setScale(1, 1);
        }
        else if(x == 1){
            jugador->setTextureRect(sf::IntRect(113, 0, 16, 15));
            jugador->move(kVel, 0);
            jugador->setScale(1, 1);
        }
    }

    void Jugador::movimientoL(int x){
        if(x == 0){
            jugador->setTextureRect(sf::IntRect(32, 1, 16, 15));
            jugador->move(-kVel, 0);
            jugador->setScale(1, 1);
        }
        else if(x == 1){
            jugador->setTextureRect(sf::IntRect(48, 0, 15, 16));
            jugador->move(-kVel, 0);
            jugador->setScale(1, 1);
        }
    }

    void Jugador::movimientoUp(int x){
        if(x == 0){
            jugador->setTextureRect(sf::IntRect(64, 0, 16, 16));
            jugador->move(0, -kVel);
            jugador->setScale(1, 1);
        }
        else if(x == 1){
            jugador->setTextureRect(sf::IntRect(80, 0, 16, 16));
            jugador->move(0, -kVel);
            jugador->setScale(1, 1);
        }
    }

    void Jugador::movimientoDown(int x){
        if(x == 0){
            jugador->setTextureRect(sf::IntRect(0, 0, 16, 16));
            jugador->move(0, kVel);
            jugador->setScale(1, 1);
        }
        else if(x == 1){
            jugador->setTextureRect(sf::IntRect(16, 0, 16, 16));
            jugador->move(0, kVel);
            jugador->setScale(1, 1);
        }
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