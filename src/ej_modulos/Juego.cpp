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
    if(reventao == false){
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
      if(chocado == true){
        romperBloque();
      }
      if(chocadoD == true){
        romperBloqueD();
      }
      if(chocadoA == true){
        romperBloqueUp();
      }
      if(chocadoDo == true){
        romperBloqueDown();
      }
    }
    else{
      sgsR = reiniciador.getElapsedTime().asSeconds();
      AnimacionPengoMuriendo();
      cout << sgsR << endl;
      if(sgsR >= 5.5){
        j1->warp(16, 9);
        j1->getSprite()->setTextureRect(sf::IntRect(96, 1, 16, 15));
      }
      if(sgsR >= 6){
        reiniciador.restart();
        reventao = false;
      }
    }
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
  enemigos[2] = new Enemigo(42, 30);
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
          //cout << "Tocando derecha" << endl;
          right = true;
        }
        // colision a la izquierda
        if(jugadorRect.intersects(spriteRectL)){
          xx = j;
          yy = i;
          //cout << "Tocando izquierda" << endl;
          left = true;
        }
        // colision arriba
        if(jugadorRect.intersects(spriteRectU)){
          ux = j;
          uy = i;
          //cout << "Tocando arriba" << endl;
          up = true;
        }
        // colision abajo
        if(jugadorRect.intersects(spriteRectD)){
          dx = j;
          dy = i;
          //cout << "Tocando abajo" << endl;
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
          reventao = true;
          relojaso.restart();
      }
    }
  }
}

void Juego::choqueBloqueIz(){
  if(maposo->sprites[xxx][yyy] != nullptr){
    if(conti == 25){
      posAnt = maposo->sprites[xxx][yyy]->getPosition().x;
      //cout << "Anterior: " << posAnt << endl;
    }
    if(conti >= 50){
      posDesp = maposo->sprites[xxx][yyy]->getPosition().x;
      //cout << "Posterior: " << posDesp << endl;
      conti = 0;
    }
    maposo->sprites[xxx][yyy]->move(0, 0);
    if(pulsado == true){
      //if(izda == true){
        maposo->sprites[xxx][yyy]->move(-kVel, 0);
        for(int i = 0; i < 16; i++){
          for(int j = 0; j < 16; j++){
            if(maposo->sprites[j][i] != nullptr){
              if(maposo->sprites[j][i] != maposo->sprites[xxx][yyy]){
                if(maposo->sprites[j][i]->getGlobalBounds().intersects(maposo->sprites[xxx][yyy]->getGlobalBounds())){
                  //cout << "Entrando al if izquierrda" << endl;
                  pulsado = false;
                  //izda = false;
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
    if(contiD == 25){
      posAntDe = maposo->sprites[xxdd][yydd]->getPosition().x;
      //cout << "Anterior: " << posAntDe << endl;
    }
    if(contiD >= 50){
      posDespDe = maposo->sprites[xxdd][yydd]->getPosition().x;
      //cout << "Posterior: " << posDespDe << endl;
      contiD = 0;
    }
    maposo->sprites[xxdd][yydd]->move(0, 0);
    if(pulsadoD == true){
      //if(dreta == true){
        maposo->sprites[xxdd][yydd]->move(kVel, 0);
        for(int i = 0; i < 16; i++){
          for(int j = 0; j < 16; j++){
            if(maposo->sprites[j][i] != nullptr){
              if(maposo->sprites[j][i] != maposo->sprites[xxdd][yydd]){
                if(maposo->sprites[j][i]->getGlobalBounds().intersects(maposo->sprites[xxdd][yydd]->getGlobalBounds())){
                  //cout << "Entrando al if derecha" << endl;
                  pulsadoD = false;
                  //dreta = false;
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
    if(contiA == 25){
      posAntUp = maposo->sprites[uxx][uyy]->getPosition().y;
      //cout << "Anterior: " << posAntUp << endl;
    }
    if(contiA >= 50){
      posDespUp = maposo->sprites[uxx][uyy]->getPosition().y;
      //cout << "Posterior: " << posDespUp << endl;
      contiA = 0;
    }
    maposo->sprites[uxx][uyy]->move(0, 0);
    if(pulsadoA == true){
      //if(arriba == true){
        maposo->sprites[uxx][uyy]->move(0, -kVel);
        for(int i = 0; i < 16; i++){
          for(int j = 0; j < 16; j++){
            if(maposo->sprites[j][i] != nullptr){
              if(maposo->sprites[j][i] != maposo->sprites[uxx][uyy]){
                if(maposo->sprites[j][i]->getGlobalBounds().intersects(maposo->sprites[uxx][uyy]->getGlobalBounds())){
                  //cout << "Entrando al if arriba" << endl;
                  pulsadoA = false;
                  //arriba = false;
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
    if(contiAb == 25){
      posAntDo = maposo->sprites[dxx][dyy]->getPosition().y;
      //cout << "Anterior: " << posAntDo << endl;
    }
    if(contiAb >= 50){
      posDespDo = maposo->sprites[dxx][dyy]->getPosition().y;
      //cout << "Posterior: " << posDespDo << endl;
      contiAb = 0;
    }
    maposo->sprites[dxx][dyy]->move(0, 0);
    if(pulsadoDown == true){
      //if(abajo == true){
        maposo->sprites[dxx][dyy]->move(0, kVel);
        for(int i = 0; i < 16; i++){
          for(int j = 0; j < 16; j++){
            if(maposo->sprites[j][i] != nullptr){
              if(maposo->sprites[j][i] != maposo->sprites[dxx][dyy]){
                if(maposo->sprites[j][i]->getGlobalBounds().intersects(maposo->sprites[dxx][dyy]->getGlobalBounds())){
                  //cout << "Entrando al if abajo" << endl;
                  pulsadoDown = false;
                  //abajo = false;
                }
              }
            }
          }
        }
      //}
    }
  }
}

void Juego::choqueBloquePengoIz(){
  if(posAnt != posDesp){
    if(maposo->sprites[xxx][yyy] != nullptr){
      if(maposo->sprites[xxx][yyy]->getGlobalBounds().intersects(enemigos[0]->getSprite()->getGlobalBounds())){
        esGolpeado = true;
        enemigos[0]->getSprite()->setPosition(maposo->sprites[xxx][yyy]->getPosition().x-16, maposo->sprites[xxx][yyy]->getPosition().y);
      }
      if(maposo->sprites[xxx][yyy]->getGlobalBounds().intersects(enemigos[1]->getSprite()->getGlobalBounds())){
        esGolpeado2 = true;
        enemigos[1]->getSprite()->setPosition(maposo->sprites[xxx][yyy]->getPosition().x-16, maposo->sprites[xxx][yyy]->getPosition().y);
      }
      if(maposo->sprites[xxx][yyy]->getGlobalBounds().intersects(enemigos[2]->getSprite()->getGlobalBounds())){
        esGolpeado3 = true;
        enemigos[2]->getSprite()->setPosition(maposo->sprites[xxx][yyy]->getPosition().x-16, maposo->sprites[xxx][yyy]->getPosition().y);
      }
    }
    if(pulsado == false){
      //cout << "Confirmamos choque" << endl;
      chocado = true;
      guardado = maposo->sprites[xxx][yyy];
    }
  }
}

void Juego::choqueBloquePengoDe(){
  if(posAntDe != posDespDe){
    if(maposo->sprites[xxdd][yydd] != nullptr){
      if(maposo->sprites[xxdd][yydd]->getGlobalBounds().intersects(enemigos[0]->getSprite()->getGlobalBounds())){
        esGolpeado = true;
        enemigos[0]->getSprite()->setPosition(maposo->sprites[xxdd][yydd]->getPosition().x+16, maposo->sprites[xxdd][yydd]->getPosition().y);
      }
      if(maposo->sprites[xxdd][yydd]->getGlobalBounds().intersects(enemigos[1]->getSprite()->getGlobalBounds())){
        esGolpeado2 = true;
        enemigos[1]->getSprite()->setPosition(maposo->sprites[xxdd][yydd]->getPosition().x+16, maposo->sprites[xxdd][yydd]->getPosition().y);
      }
      if(maposo->sprites[xxdd][yydd]->getGlobalBounds().intersects(enemigos[2]->getSprite()->getGlobalBounds())){
        //cout << "Esta intersectando" << endl;
        esGolpeado3 = true;
        enemigos[2]->getSprite()->setPosition(maposo->sprites[xxdd][yydd]->getPosition().x+16, maposo->sprites[xxdd][yydd]->getPosition().y);
      }
    }
    if(pulsadoD == false){
        //cout << "Confirmamos choque" << endl;
        chocadoD = true;
        guardadoD = maposo->sprites[xxdd][yydd];
    }
  }
}

void Juego::choqueBloquePengoUp(){
  if(posAntUp != posDespUp){
    if(maposo->sprites[uxx][uyy] != nullptr){
      if(maposo->sprites[uxx][uyy]->getGlobalBounds().intersects(enemigos[0]->getSprite()->getGlobalBounds())){
        esGolpeado = true;
        enemigos[0]->getSprite()->setPosition(maposo->sprites[uxx][uyy]->getPosition().x, maposo->sprites[uxx][uyy]->getPosition().y - 16);
      }
      if(maposo->sprites[uxx][uyy]->getGlobalBounds().intersects(enemigos[1]->getSprite()->getGlobalBounds())){
        esGolpeado2 = true;
        enemigos[1]->getSprite()->setPosition(maposo->sprites[uxx][uyy]->getPosition().x, maposo->sprites[uxx][uyy]->getPosition().y - 16);
      }
      if(maposo->sprites[uxx][uyy]->getGlobalBounds().intersects(enemigos[2]->getSprite()->getGlobalBounds())){
        esGolpeado3 = true;
        enemigos[2]->getSprite()->setPosition(maposo->sprites[uxx][uyy]->getPosition().x, maposo->sprites[uxx][uyy]->getPosition().y - 16);
      }
    }
    if(pulsadoA == false){
      //cout << "Confirmamos choque" << endl;
      chocadoA = true;
      guardadoA = maposo->sprites[uxx][uyy];
    }
  }
}

void Juego::choqueBloquePengoDown(){
  if(posAntDo != posDespDo){
    if(maposo->sprites[dxx][dyy] != nullptr){
      if(maposo->sprites[dxx][dyy]->getGlobalBounds().intersects(enemigos[0]->getSprite()->getGlobalBounds())){
        esGolpeado = true;
        enemigos[0]->getSprite()->setPosition(maposo->sprites[dxx][dyy]->getPosition().x, maposo->sprites[dxx][dyy]->getPosition().y + 16);
      }
      if(maposo->sprites[dxx][dyy]->getGlobalBounds().intersects(enemigos[1]->getSprite()->getGlobalBounds())){
        esGolpeado2 = true;
        enemigos[1]->getSprite()->setPosition(maposo->sprites[dxx][dyy]->getPosition().x, maposo->sprites[dxx][dyy]->getPosition().y + 16);
      }
      if(maposo->sprites[dxx][dyy]->getGlobalBounds().intersects(enemigos[2]->getSprite()->getGlobalBounds())){
        esGolpeado3 = true;
        enemigos[2]->getSprite()->setPosition(maposo->sprites[dxx][dyy]->getPosition().x, maposo->sprites[dxx][dyy]->getPosition().y + 16);
      }
    }
    if(pulsadoDown == false){
      //cout << "Confirmamos choque" << endl;
      chocadoDo = true;
      guardadoDo = maposo->sprites[dxx][dyy];
    }
  }
}

void Juego::romperBloque(){
  FloatRect spriteRectL(guardado->getPosition().x, guardado->getPosition().y, 16, 16);
  if(j1->getSprite()->getGlobalBounds().intersects(spriteRectL)){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
      espacio = true;
    }
    if(espacio == true){
      sgs2 = relojero.getElapsedTime().asSeconds();
      if(sgs2 >= 0.03){
        cambiarSprite(comienza, guardado);
        comienza++;
        if(comienza == 9){
          comienza = 0;
          //entrando = true;
          chocado = false;
          guardado->setPosition(0, 0);
          espacio = false;
        }
        relojero.restart();
      }
    }
  }
}

void Juego::romperBloqueD(){
  FloatRect spriteRectR(guardadoD->getPosition().x - 16, guardadoD->getPosition().y, 16, 16);
  //cout << guardadoD->getPosition().x << " , " << guardadoD->getPosition().y << " : " << j1->getSprite()->getPosition().x << " , " << j1->getSprite()->getPosition().y << endl;
  if(j1->getSprite()->getGlobalBounds().intersects(spriteRectR)){
    //cout << "Tocando" << endl;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
      espacio = true;
    }
    if(espacio == true){
      sgs2 = relojero.getElapsedTime().asSeconds();
      if(sgs2 >= 0.03){
        cambiarSpriteR(comienza, guardadoD);
        comienza++;
        if(comienza == 9){
          comienza = 0;
          //entrando = true;
          chocadoD = false;
          guardadoD->setPosition(0, 0);
          espacio = false;
        }
        relojero.restart();
      }
    }
  }
}

void Juego::romperBloqueUp(){
  FloatRect spriteRectR(guardadoA->getPosition().x, guardadoA->getPosition().y + 16, 16, 16);
  //cout << guardadoD->getPosition().x << " , " << guardadoD->getPosition().y << " : " << j1->getSprite()->getPosition().x << " , " << j1->getSprite()->getPosition().y << endl;
  if(j1->getSprite()->getGlobalBounds().intersects(spriteRectR)){
    //cout << "Tocando" << endl;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
      espacio = true;
    }
    if(espacio == true){
      sgs2 = relojero.getElapsedTime().asSeconds();
      if(sgs2 >= 0.03){
        cambiarSpriteUp(comienza, guardadoA);
        comienza++;
        if(comienza == 9){
          comienza = 0;
          //entrando = true;
          chocadoA = false;
          guardadoA->setPosition(0, 0);
          espacio = false;
        }
        relojero.restart();
      }
    }
  }
}

void Juego::romperBloqueDown(){
  FloatRect spriteRectR(guardadoDo->getPosition().x, guardadoDo->getPosition().y - 16, 16, 16);
  //cout << guardadoD->getPosition().x << " , " << guardadoD->getPosition().y << " : " << j1->getSprite()->getPosition().x << " , " << j1->getSprite()->getPosition().y << endl;
  if(j1->getSprite()->getGlobalBounds().intersects(spriteRectR)){
    //cout << "Tocando" << endl;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
      espacio = true;
    }
    if(espacio == true){
      sgs2 = relojero.getElapsedTime().asSeconds();
      if(sgs2 >= 0.03){
        cambiarSpriteDown(comienza, guardadoDo);
        comienza++;
        if(comienza == 9){
          comienza = 0;
          //entrando = true;
          chocadoDo = false;
          guardadoDo->setPosition(0, 0);
          espacio = false;
        }
        relojero.restart();
      }
    }
  }
}

void Juego::cambiarSprite(int x, Sprite*){
  if(x == 0){
      guardado->setTextureRect(sf::IntRect(708, 48, 16, 16));
  }
  if(x == 1){
      guardado->setTextureRect(sf::IntRect(708 + 16, 48, 16, 16));
  }
  if(x == 2){
      guardado->setTextureRect(sf::IntRect(708 + 32, 48, 16, 16));
  }
  if(x == 3){
      guardado->setTextureRect(sf::IntRect(708 + 48, 48, 16, 16));
  }
  if(x == 4){
      guardado->setTextureRect(sf::IntRect(708 + 64, 48, 16, 16));
  }
  if(x == 5){
      guardado->setTextureRect(sf::IntRect(708 + 80, 48, 16, 16));
  }
  if(x == 6){
      guardado->setTextureRect(sf::IntRect(708 + 96, 48, 16, 16));
  }
  if(x == 7){
      guardado->setTextureRect(sf::IntRect(708 + 112, 48, 16, 16));
  }
  if(x == 8){
      guardado->setTextureRect(sf::IntRect(708 + 128, 48, 16, 16));
  }
}

void Juego::cambiarSpriteR(int x, Sprite*){
  if(x == 0){
      guardadoD->setTextureRect(sf::IntRect(708, 48, 16, 16));
  }
  if(x == 1){
      guardadoD->setTextureRect(sf::IntRect(708 + 16, 48, 16, 16));
  }
  if(x == 2){
      guardadoD->setTextureRect(sf::IntRect(708 + 32, 48, 16, 16));
  }
  if(x == 3){
      guardadoD->setTextureRect(sf::IntRect(708 + 48, 48, 16, 16));
  }
  if(x == 4){
      guardadoD->setTextureRect(sf::IntRect(708 + 64, 48, 16, 16));
  }
  if(x == 5){
      guardadoD->setTextureRect(sf::IntRect(708 + 80, 48, 16, 16));
  }
  if(x == 6){
      guardadoD->setTextureRect(sf::IntRect(708 + 96, 48, 16, 16));
  }
  if(x == 7){
      guardadoD->setTextureRect(sf::IntRect(708 + 112, 48, 16, 16));
  }
  if(x == 8){
      guardadoD->setTextureRect(sf::IntRect(708 + 128, 48, 16, 16));
  }
}

void Juego::cambiarSpriteUp(int x, Sprite*){
  if(x == 0){
      guardadoA->setTextureRect(sf::IntRect(708, 48, 16, 16));
  }
  if(x == 1){
      guardadoA->setTextureRect(sf::IntRect(708 + 16, 48, 16, 16));
  }
  if(x == 2){
      guardadoA->setTextureRect(sf::IntRect(708 + 32, 48, 16, 16));
  }
  if(x == 3){
      guardadoA->setTextureRect(sf::IntRect(708 + 48, 48, 16, 16));
  }
  if(x == 4){
      guardadoA->setTextureRect(sf::IntRect(708 + 64, 48, 16, 16));
  }
  if(x == 5){
      guardadoA->setTextureRect(sf::IntRect(708 + 80, 48, 16, 16));
  }
  if(x == 6){
      guardadoA->setTextureRect(sf::IntRect(708 + 96, 48, 16, 16));
  }
  if(x == 7){
      guardadoA->setTextureRect(sf::IntRect(708 + 112, 48, 16, 16));
  }
  if(x == 8){
      guardadoA->setTextureRect(sf::IntRect(708 + 128, 48, 16, 16));
  }
}

void Juego::cambiarSpriteDown(int x, Sprite*){
  if(x == 0){
      guardadoDo->setTextureRect(sf::IntRect(708, 48, 16, 16));
  }
  if(x == 1){
      guardadoDo->setTextureRect(sf::IntRect(708 + 16, 48, 16, 16));
  }
  if(x == 2){
      guardadoDo->setTextureRect(sf::IntRect(708 + 32, 48, 16, 16));
  }
  if(x == 3){
      guardadoDo->setTextureRect(sf::IntRect(708 + 48, 48, 16, 16));
  }
  if(x == 4){
      guardadoDo->setTextureRect(sf::IntRect(708 + 64, 48, 16, 16));
  }
  if(x == 5){
      guardadoDo->setTextureRect(sf::IntRect(708 + 80, 48, 16, 16));
  }
  if(x == 6){
      guardadoDo->setTextureRect(sf::IntRect(708 + 96, 48, 16, 16));
  }
  if(x == 7){
      guardadoDo->setTextureRect(sf::IntRect(708 + 112, 48, 16, 16));
  }
  if(x == 8){
      guardadoDo->setTextureRect(sf::IntRect(708 + 128, 48, 16, 16));
  }
}

void Juego::AnimacionPengoMuriendo(){
  sgs3 = reloja.getElapsedTime().asSeconds();
  if(sgs3 >= 0.1){
    palante++;
    this->SpriteMuerto(palante);
    if(palante == 2){
        // yasta = true;
        palante = -1;
    }
    reloja.restart();
  }
}

void Juego::SpriteMuerto(int x){
  if(x == 0){
    j1->getSprite()->setTextureRect(sf::IntRect(0, 32, 16, 16));
  }
  else if(x == 1){
    j1->getSprite()->setTextureRect(sf::IntRect(16, 32, 16, 16));
  }
}