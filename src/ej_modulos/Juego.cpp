#include "Juego.h"
#include <SFML/Graphics.hpp>
/************************** HACE TODOS LOS COMANDOS A LA VEZ *****************************************/
/* alias do="cmake -H. -Bbuild && cd build/ && make && mv GremoryHole .. && cd .. && ./GremoryHole" */
/*                           Luego simplemente pones do                                            */
/**************************************************************************************************/
Juego::Juego(sf::Vector2u resolucion){
    //Creamos una ventana
    ventana = new sf::RenderWindow(sf::VideoMode(resolucion.x,resolucion.y), "Gremory Hole");
    this->iniciar();
    while(gameover != true){
      /*
        *crono1 = reloj1->getElapsedTime(); // Obtener tiempo transcurrido 
        if(crono1->asSeconds() > 0.08){ // comparamos si el tiempo transcurrido es 1 fps (1 frame) si es asi ejecuttamos un instante
           */
            while(ventana->pollEvent(*evento)){
                procesarEventos();
            }
            
          j1->Update(*ventana);
          this->dibujar();  
    }
  
}

void Juego::iniciar(){
  j1 = new Jugador();
  evento = new sf::Event();
}

void Juego::dibujar(){
  ventana->clear();
  j1->Draw(*ventana);
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
            j1->movimiento(x);
            x++;
            if(x == 2){
              x = 0;
            }
          }
          break;
        default:
          break;
    }
}