#include "Juego.h"
#include <SFML/Graphics.hpp>
/************************** HACE TODOS LOS COMANDOS A LA VEZ *****************************************/
/* alias do="cmake -H. -Bbuild && cd build/ && make && mv GremoryHole .. && cd .. && ./GremoryHole" */
/*                           Luego simplemente pones do                                            */
/**************************************************************************************************/
Juego::Juego(sf::Vector2u resolucion){
    //Creamos una ventana
    ventana = new sf::RenderWindow(sf::VideoMode(resolucion.x,resolucion.y), "Gremory Hole");
    Jugador *j1 = new Jugador();
    while (ventana->isOpen()) {
    //Bucle de obtención de eventos
    sf::Event event;
    while (ventana->pollEvent(event)) {

      switch (event.type) {

      //Si se recibe el evento de cerrar la ventana la cierro
      case sf::Event::Closed:
        ventana->close();
        break;

      //Se pulsó una tecla, imprimo su codigo
      case sf::Event::KeyPressed:

        //Verifico si se pulsa alguna tecla de movimiento
        switch (event.key.code) {


        //Tecla ESC para salir
        case sf::Keyboard::Escape:
          ventana->close();
          break;

        //Cualquier tecla desconocida se imprime por pantalla su código
        default:
          std::cout << event.key.code << std::endl;
          break;
        }
      }
    }
    ventana->clear();
    j1->Draw(*ventana);
    ventana->display();
  }
}