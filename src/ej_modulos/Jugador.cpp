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
        jugador->setOrigin(131, 25);
        //Cojo el sprite que me interesa por defecto del sheet
        jugador->setTextureRect(sf::IntRect(96, 1, 16, 15));
        
        // Lo dispongo a la derecha de la pantalla
        //spriteb->setPosition(xx, yy);
        jugador->setPosition(400, 300);
    }

    void Jugador::movimiento(int x){
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

    void Jugador::Update(RenderWindow &window){
        /*
        while (window.isOpen()) {
            //Bucle de obtención de eventos
            sf::Event event;
            while (window.pollEvent(event)) {

                switch (event.type) {

                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window.close();
                    break;

                //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:

                    //Verifico si se pulsa alguna tecla de movimiento
                    switch (event.key.code) {

                        //Mapeo del cursor
                        case sf::Keyboard::Right:
                            this->movimiento(x);
                            x++;
                            if(x == 2){
                                x = 0;
                            }
                        break;

                        case sf::Keyboard::Left:

                        break;

                        case sf::Keyboard::Up:

                        break;

                        case sf::Keyboard::Down:

                        break;

                        //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                        window.close();
                        break;

                        //Cualquier tecla desconocida se imprime por pantalla su código
                        default:
                        std::cout << event.key.code << std::endl;
                        break;           
                    }  
                }
            }
        }
        */
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