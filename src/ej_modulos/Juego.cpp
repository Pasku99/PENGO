#include "Juego.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

#define kVel 1

Juego::Juego(sf::Vector2u resolucion){
    //Creamos una ventana
    ventana = new RenderWindow(sf::VideoMode(resolucion.x,resolucion.y), "Pengo");
    // Inicializamos todo
    this->iniciar();
    srand(time(NULL));
    while(gameover == false){
      while(ventana->pollEvent(*evento)){
        procesarEventos();
      }
      j1->update();
      enemy1->update(maposo);
      enemy2->update(maposo);
      enemy3->update(maposo);
      maposo->update(pulsado, xx, yy);
      procesarColisionesPengoSnoobee();
      this->dibujar();  
    }
  
}

void Juego::iniciar(){
  j1 = new Jugador();
  j1->getSprite()->setPosition(j1->getCoors().x, j1->getCoors().y);
  evento = new sf::Event();
  maposo = new Map();
  enemy1 = new Enemigo(10, 10);
  enemy2 = new Enemigo(10, 20);
  enemy3 = new Enemigo(20, 15);
}

void Juego::dibujar(){
  ventana->clear();
  j1->Draw(*ventana);
  enemy1->Draw(*ventana);
  enemy2->Draw(*ventana);
  enemy3->Draw(*ventana);
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
        // si se pulsa la tecla derecha
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            ventana->close();
            break;
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            pulsado = false;
            procesarColisiones();
            if(right == true){
              j1->move(Stay);
              right = false;
            }
            else{
              if(x == 0){
                j1->getSprite()->setTextureRect(sf::IntRect(96, 1, 16, 15));
                j1->move(Right);
              }
              else{
                j1->getSprite()->setTextureRect(sf::IntRect(113, 0, 16, 15));
                j1->move(Right);
              }
            }
            x++;
            if(x == 2){
              x = 0;
            }
          }
          // si se pulsa la tecla izquierda
          else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            pulsado = false;
            j1->getSprite()->setTextureRect(sf::IntRect(32, 1, 16, 15));
            procesarColisiones();
            if(left == true){
              j1->move(Stay);
              left = false;
            }
            else{
              if(y == 0){
                j1->getSprite()->setTextureRect(sf::IntRect(32, 1, 16, 15));
                j1->move(Left);
              }
              else{
                j1->getSprite()->setTextureRect(sf::IntRect(48, 0, 15, 16));
                j1->move(Left);
              }
            }
            y++;
            if(y == 2){
              y = 0;
            }
          }
          // si se pulsa la tecla arriba
          else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            pulsado = false;
            procesarColisiones();
            if(up == true){
              j1->move(Stay);
              up = false;
            }
            else{
              if(z == 0){
                j1->getSprite()->setTextureRect(sf::IntRect(64, 0, 16, 16));
                j1->move(Up);
              }
              else{
                j1->getSprite()->setTextureRect(sf::IntRect(80, 0, 16, 16));
                j1->move(Up);
              }
            }
            z++;
            if(z == 2){
              z = 0;
            }
          }
          // si se pulsa la tecla abajo
          else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            pulsado = false;
            procesarColisiones();
            if(down == true){
              j1->move(Stay);
              down = false;
            }
            else{
              if(j == 0){
                j1->getSprite()->setTextureRect(sf::IntRect(0, 0, 16, 16));
                j1->move(Down);
              }
              else{
                j1->getSprite()->setTextureRect(sf::IntRect(16, 0, 16, 16));
                j1->move(Down);
              }
            }
            j++;
            if(j == 2){
              j = 0;
            }
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            procesarColisiones();
            if(left == true){
              pulsado = true;
            }
          }
          break;
        default:
          break;
    }
    //j1->update();
}

void Juego::procesarColisiones(){
  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){
      if(maposo->sprites[j][i] != nullptr){
        FloatRect spriteRectR(maposo->sprites[j][i]->getPosition().x - 16, maposo->sprites[j][i]->getPosition().y, 16, 16);
        FloatRect spriteRectD(maposo->sprites[j][i]->getPosition().x, maposo->sprites[j][i]->getPosition().y - 16, 16, 16);
        FloatRect spriteRectL(maposo->sprites[j][i]->getPosition().x + 16, maposo->sprites[j][i]->getPosition().y, 16, 16);
        FloatRect spriteRectU(maposo->sprites[j][i]->getPosition().x, maposo->sprites[j][i]->getPosition().y + 16, 16, 16);
        FloatRect jugadorRect(j1->getSprite()->getPosition().x, j1->getSprite()->getPosition().y, 16, 16);
        // colision a la derecha
        if(jugadorRect.intersects(spriteRectR)){
          cout << "Tocando derecha" << endl;
          right = true;
        }
        // colision a la izquierda
        if(jugadorRect.intersects(spriteRectL)){
          xx = j;
          yy = i;
          cout << "Tocando izquierda" << endl;
          left = true;
        }
        // colision arriba
        if(jugadorRect.intersects(spriteRectU)){
          cout << "Tocando arriba" << endl;
          up = true;
        }
        // colision abajo
        if(jugadorRect.intersects(spriteRectD)){
          cout << "Tocando abajo" << endl;
          down = true;
        }
      }
    }
  }
}

void Juego::procesarColisionesPengoSnoobee(){
  sgs = relojaso.getElapsedTime().asSeconds();
  if(sgs >= 3){
    if(this->j1->getSprite()->getGlobalBounds().intersects(enemy1->getSprite()->getGlobalBounds())){
        gameover = this->j1->perderVida(gameover);
        cout << gameover << endl;
        relojaso.restart();
    }
    if(this->j1->getSprite()->getGlobalBounds().intersects(enemy2->getSprite()->getGlobalBounds())){
        gameover = this->j1->perderVida(gameover);
        cout << gameover << endl;
        relojaso.restart();
    }
    if(this->j1->getSprite()->getGlobalBounds().intersects(enemy3->getSprite()->getGlobalBounds())){
        gameover = this->j1->perderVida(gameover);
        cout << gameover << endl;
        relojaso.restart();
    }
  }
}