#include "Juego.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

#define kVel 0.04

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
    enemigos[0]->update(maposo, esGolpeado);
    enemigos[1]->update(maposo, esGolpeado2);
    enemigos[2]->update(maposo, esGolpeado3);
    this->choqueBloqueIz();
    this->choqueBloqueDe();
    this->choqueBloqueUp();
    this->choqueBloqueDown();
    conti++;
    contiD++;
    contiA++;
    contiAb++;
    this->choqueBloquePengoIz();
    this->choqueBloquePengoDe();
    this->choqueBloquePengoDown();
    this->choqueBloquePengoUp();
    //this->choqueBloquePengoDe();
    procesarColisionesPengoSnoobee();
    this->dibujar(); 
  }
}

void Juego::iniciar(){
  j1 = new Jugador();
  j1->getSprite()->setPosition(j1->getCoors().x, j1->getCoors().y);
  evento = new sf::Event();
  maposo = new Map();
  enemigos[0] = new Enemigo(20, 20);
  enemigos[1] = new Enemigo(20, 40);
  enemigos[2] = new Enemigo(43, 30);
}

void Juego::dibujar(){
  ventana->clear();
  j1->Draw(*ventana);
  enemigos[0]->Draw(*ventana);
  enemigos[1]->Draw(*ventana);
  enemigos[2]->Draw(*ventana);
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
            dreta = true;
            izda = false;
            arriba = false;
            abajo = false;
            j1->getSprite()->setTextureRect(sf::IntRect(96, 1, 16, 15));
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
            dreta = false;
            izda = true;
            arriba = false;
            abajo = false;
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
            arriba = true;
            dreta = false;
            izda = false;
            abajo = false;
            j1->getSprite()->setTextureRect(sf::IntRect(64, 0, 16, 16));
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
            dreta = false;
            izda = false;
            arriba = false;
            abajo = true;
            j1->getSprite()->setTextureRect(sf::IntRect(0, 0, 16, 16));
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
            if(left == true && izda == true){
              xxx = xx;
              yyy = yy;
              pulsado = true;
            }
            if(right == true && dreta == true){
              xxdd = xxd;
              yydd = yyd;
              pulsadoD = true;
            }
            if(up == true && arriba == true){
              uxx = ux;
              uyy = uy;
              pulsadoA = true;
            }
            if(down == true && abajo == true){
              dxx = dx;
              dyy = dy;
              pulsadoDown = true;
            }
          }
          break;
        default:
          break;
    }
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
          xxd = j;
          yyd = i;
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
          ux = j;
          uy = i;
          cout << "Tocando arriba" << endl;
          up = true;
        }
        // colision abajo
        if(jugadorRect.intersects(spriteRectD)){
          dx = j;
          dy = i;
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
    for(int i = 0; i < 3; i++){
      if(this->j1->getSprite()->getGlobalBounds().intersects(enemigos[i]->getSprite()->getGlobalBounds())){
          gameover = this->j1->perderVida(gameover);
          cout << "Pierde 1 vida" << endl;
          relojaso.restart();
      }
    }
  }
}

void Juego::choqueBloqueIz(){
  if(maposo->sprites[xxx][yyy] != nullptr){
    if(conti >= 25){
      posAnt = maposo->sprites[xxx][yyy]->getPosition().x;
      //cout << "Anterior: " << posAnt << endl;
    }
    maposo->sprites[xxx][yyy]->move(0, 0);
    if(pulsado == true){
      //if(izda == true){
        maposo->sprites[xxx][yyy]->move(-kVel, 0);
        if(conti >= 25){
          posDesp = maposo->sprites[xxx][yyy]->getPosition().x;
          //cout << "Posterior: " << posDesp << endl;
          conti = 0;
        }
        for(int i = 0; i < 16; i++){
          for(int j = 0; j < 16; j++){
            if(maposo->sprites[j][i] != nullptr){
              if(maposo->sprites[j][i] != maposo->sprites[xxx][yyy]){
                if(maposo->sprites[j][i]->getGlobalBounds().intersects(maposo->sprites[xxx][yyy]->getGlobalBounds())){
                  cout << "Entrando al if izquierrda" << endl;
                  pulsado = false;
                  izda = false;
                }
              }
            }
          }
        }
      //}
    }
  }
}

void Juego::choqueBloqueDe(){
  if(maposo->sprites[xxdd][yydd] != nullptr){
    if(contiD >= 25){
      posAntDe = maposo->sprites[xxdd][yydd]->getPosition().x;
      //cout << "Anterior: " << posAnt << endl;
    }
    maposo->sprites[xxdd][yydd]->move(0, 0);
    if(pulsadoD == true){
      //if(dreta == true){
        maposo->sprites[xxdd][yydd]->move(kVel, 0);
        if(contiD >= 25){
          posDespDe = maposo->sprites[xxdd][yydd]->getPosition().x;
          //cout << "Posterior: " << posDesp << endl;
          contiD = 0;
        }
        for(int i = 0; i < 16; i++){
          for(int j = 0; j < 16; j++){
            if(maposo->sprites[j][i] != nullptr){
              if(maposo->sprites[j][i] != maposo->sprites[xxdd][yydd]){
                if(maposo->sprites[j][i]->getGlobalBounds().intersects(maposo->sprites[xxdd][yydd]->getGlobalBounds())){
                  cout << "Entrando al if derecha" << endl;
                  pulsadoD = false;
                  dreta = false;
                }
              }
            }
          }
        }
      //}
    }
  }
}

void Juego::choqueBloqueUp(){
  if(maposo->sprites[uxx][uyy] != nullptr){
    if(contiA >= 25){
      posAntUp = maposo->sprites[uxx][uyy]->getPosition().y;
      //cout << "Anterior: " << posAnt << endl;
    }
    maposo->sprites[uxx][uyy]->move(0, 0);
    if(pulsadoA == true){
      //if(arriba == true){
        maposo->sprites[uxx][uyy]->move(0, -kVel);
        if(contiA >= 25){
          posDespUp = maposo->sprites[uxx][uyy]->getPosition().y;
          //cout << "Posterior: " << posDesp << endl;
          contiA = 0;
        }
        for(int i = 0; i < 16; i++){
          for(int j = 0; j < 16; j++){
            if(maposo->sprites[j][i] != nullptr){
              if(maposo->sprites[j][i] != maposo->sprites[uxx][uyy]){
                if(maposo->sprites[j][i]->getGlobalBounds().intersects(maposo->sprites[uxx][uyy]->getGlobalBounds())){
                  cout << "Entrando al if arriba" << endl;
                  pulsadoA = false;
                  arriba = false;
                }
              }
            }
          }
        }
      //}
    }
  }
}

void Juego::choqueBloqueDown(){
  if(maposo->sprites[dxx][dyy] != nullptr){
    if(contiAb >= 25){
      posAntDo = maposo->sprites[dxx][dyy]->getPosition().y;
      //cout << "Anterior: " << posAnt << endl;
    }
    maposo->sprites[dxx][dyy]->move(0, 0);
    //if(pulsadoDown == true){
      if(abajo == true){
        maposo->sprites[dxx][dyy]->move(0, kVel);
        if(contiAb >= 25){
          posDespDo = maposo->sprites[dxx][dyy]->getPosition().y;
          //cout << "Posterior: " << posDesp << endl;
          contiAb = 0;
        }
        for(int i = 0; i < 16; i++){
          for(int j = 0; j < 16; j++){
            if(maposo->sprites[j][i] != nullptr){
              if(maposo->sprites[j][i] != maposo->sprites[dxx][dyy]){
                if(maposo->sprites[j][i]->getGlobalBounds().intersects(maposo->sprites[dxx][dyy]->getGlobalBounds())){
                  cout << "Entrando al if abajo" << endl;
                  pulsadoDown = false;
                  abajo = false;
                }
              }
            }
          }
        }
      }
    //}
  }
}

void Juego::choqueBloquePengoIz(){
  if(posAnt != posDesp){
    if(maposo->sprites[xxx][yyy] != nullptr){
      if(maposo->sprites[xxx][yyy]->getGlobalBounds().intersects(enemigos[0]->getSprite()->getGlobalBounds())){
        esGolpeado = true;
        enemigos[0]->getSprite()->move(-kVel, 0);
      }
      if(maposo->sprites[xxx][yyy]->getGlobalBounds().intersects(enemigos[1]->getSprite()->getGlobalBounds())){
        esGolpeado2 = true;
        enemigos[1]->getSprite()->move(-kVel, 0);
      }
      if(maposo->sprites[xxx][yyy]->getGlobalBounds().intersects(enemigos[2]->getSprite()->getGlobalBounds())){
        esGolpeado3 = true;
        enemigos[2]->getSprite()->move(-kVel, 0);
      }
    }
  }
}

void Juego::choqueBloquePengoDe(){
  if(posAntDe != posDespDe){
    if(maposo->sprites[xxdd][yydd] != nullptr){
      if(maposo->sprites[xxdd][yydd]->getGlobalBounds().intersects(enemigos[0]->getSprite()->getGlobalBounds())){
        esGolpeado = true;
        enemigos[0]->getSprite()->move(kVel, 0);
      }
      if(maposo->sprites[xxdd][yydd]->getGlobalBounds().intersects(enemigos[1]->getSprite()->getGlobalBounds())){
        esGolpeado2 = true;
        enemigos[1]->getSprite()->move(kVel, 0);
      }
      if(maposo->sprites[xxdd][yydd]->getGlobalBounds().intersects(enemigos[2]->getSprite()->getGlobalBounds())){
        esGolpeado3 = true;
        enemigos[2]->getSprite()->move(kVel, 0);
      }
    }
  }
}

void Juego::choqueBloquePengoUp(){
  if(posAntUp != posDespUp){
    if(maposo->sprites[uxx][uyy] != nullptr){
      if(maposo->sprites[uxx][uyy]->getGlobalBounds().intersects(enemigos[0]->getSprite()->getGlobalBounds())){
        esGolpeado = true;
        enemigos[0]->getSprite()->move(0, -kVel);
      }
      if(maposo->sprites[uxx][uyy]->getGlobalBounds().intersects(enemigos[1]->getSprite()->getGlobalBounds())){
        esGolpeado2 = true;
        enemigos[1]->getSprite()->move(0, -kVel);
      }
      if(maposo->sprites[uxx][uyy]->getGlobalBounds().intersects(enemigos[2]->getSprite()->getGlobalBounds())){
        esGolpeado3 = true;
        enemigos[2]->getSprite()->move(0, -kVel);
      }
    }
  }
}

void Juego::choqueBloquePengoDown(){
  if(posAntDo != posDespDo){
    if(maposo->sprites[dxx][dyy] != nullptr){
      if(maposo->sprites[dxx][dyy]->getGlobalBounds().intersects(enemigos[0]->getSprite()->getGlobalBounds())){
        esGolpeado = true;
        enemigos[0]->getSprite()->move(0, kVel);
      }
      if(maposo->sprites[dxx][dyy]->getGlobalBounds().intersects(enemigos[1]->getSprite()->getGlobalBounds())){
        esGolpeado2 = true;
        enemigos[1]->getSprite()->move(0, kVel);
      }
      if(maposo->sprites[dxx][dyy]->getGlobalBounds().intersects(enemigos[2]->getSprite()->getGlobalBounds())){
        esGolpeado3 = true;
        enemigos[2]->getSprite()->move(0, kVel);
      }
    }
  }
}