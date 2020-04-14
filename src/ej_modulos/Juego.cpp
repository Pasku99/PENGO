#include "Juego.h"
#include <SFML/Graphics.hpp>
/************************** HACE TODOS LOS COMANDOS A LA VEZ *****************************************/
/* alias do="cmake -H. -Bbuild && cd build/ && make && mv GremoryHole .. && cd .. && ./GremoryHole" */
/*                           Luego simplemente pones do                                            */
/**************************************************************************************************/
Juego::Juego(sf::Vector2u resolucion){
    //Creamos una ventana
    ventana = new sf::RenderWindow(sf::VideoMode(resolucion.x,resolucion.y), "Pengo");
    this->iniciar();
    while(gameover != true){
      /*
        *crono1 = reloj1->getElapsedTime(); // Obtener tiempo transcurrido 
        if(crono1->asSeconds() > 0.08){ // comparamos si el tiempo transcurrido es 1 fps (1 frame) si es asi ejecuttamos un instante
           */
          while(ventana->pollEvent(*evento)){
              procesarEventos();
              procesarColisiones();
          }
          j1->update();
          this->dibujar();  
    }
  
}

void Juego::iniciar(){
  j1 = new Jugador();
  j1->getSprite()->setPosition(j1->getCoors().x, j1->getCoors().y);
  evento = new sf::Event();
  maposo = new Map();
}

void Juego::dibujar(){
  ventana->clear();
  j1->Draw(*ventana);
  maposo->dibujarMapa(*ventana);
  ventana->display();
}

void Juego::procesarEventos(){
    switch (evento->type)
    {
        case sf::Event::Closed:
            exit(1);
            break;
        case sf::Event::KeyPressed:
        // si se pulsa la tecla izquierda
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            j1->move(Right);
            x++;
            if(x == 2){
              x = 0;
            }
          }
          else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            j1->move(Left);
            y++;
            if(y == 2){
              y = 0;
            }
          }
          else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            j1->move(Up);
            z++;
            if(z == 2){
              z = 0;
            }
          }
          else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            j1->move(Down);
            j++;
            if(j == 2){
              j = 0;
            }
          }
          break;
        default:
          break;
    }
    j1->update();
}

void Juego::procesarColisiones(){
  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){
      if(maposo->sprites[j][i] != nullptr){
        cout << "j1: " << j1->getSprite()->getPosition().x + 16 << endl;
        cout << "pared: " << maposo->sprites[j][i]->getPosition().x << endl;
        if(j1->getSprite()->getPosition().x + 16 == maposo->sprites[j][i]->getPosition().x){
          j1->getSprite()->setPosition(j1->getCoors().x - 16, j1->getCoors().y);
        }
      }
    }
  }
}