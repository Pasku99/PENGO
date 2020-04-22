#include "Juego.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

#define kVel 0.1

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
      if(restarteo == true){
        j1->setVidas(3);
        cout << "Num vidas: " << j1->getVidas() << endl;
        j1->warp(16, 9);
        enemigos[0]->restartSprite();
        enemigos[1]->restartSprite();
        enemigos[2]->restartSprite();
        enemigos[0]->warp(176, 160);
        enemigos[1]->warp(312, 192);
        enemigos[2]->warp(224, 208);
        restarteo = false;
      }else{
        j1->update();
      }
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
      if(empujeL == true){
        animacionEmpujarIzda();
      }
      if(empujeR == true){
        animacionEmpujarRight();
      }
      if(empujeU == true){
        animacionEmpujarUp();
      }
      if(empujeD == true){
        animacionEmpujarDown();
      }
      if(godmode == false){
        j1->restartSprite();
        procesarColisionesPengoSnoobee();
      }else{
        j1->getSprite()->setColor(Color::Yellow);
        if(pulsarG == true){
          if(contadorG == 200){
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::G)){
              cout << "Modo normal" << endl;
              godmode = false;
              pulsarG = false;
            }
            contadorG = 0;
          }
          contadorG++;
        }
      }
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
      if(eliminao == true){
        if(secondTime == false){
          nuevoEnemigo.restart();
          secondTime = true;
        }
        else{
          regenerarSnoobee();
        }
      }
      if(eliminao2 == true){
        if(secondTime == false){
          nuevoEnemigo.restart();
          secondTime = true;
        }
        else{
          regenerarSnoobee2();
        }
      }
      if(eliminao3 == true){
        if(secondTime == false){
          nuevoEnemigo.restart();
          secondTime = true;
        }
        else{
          regenerarSnoobee3();
        }
      }
      this->comprobarJuegoPasado();
      if(juegoPasado == true && dibujaisimo == false){
        cout << "Pasadisimo" << endl;
        maposo = new Map(matrixMapa2);
        enemigos[0]->restartSprite();
        enemigos[1]->restartSprite();
        enemigos[2]->restartSprite();
        enemigos[0]->warp(176, 160);
        enemigos[1]->warp(312, 192);
        enemigos[2]->warp(224, 208);
        cargaNivel = 1;
        this->inicializarTodo();
        j1->warp(16, 9);
        dibujaisimo = true;
      }else if(juegoPasado == true && dibujaisimo == true){
        if(creareloj == false){
          relojpasando.restart();
          creareloj = true;
        }
        else{
          cout << "Hace esta mierda" << endl;
          float segundero = relojpasando.getElapsedTime().asSeconds();
          cout << "Pasadisimo" << endl;
          //this->inicializarTodo();
          this->EscribirTexto();
          if(segundero >= 3){
            cout << "Acaba el juego" << endl;
            gameover = true;
          }
        }
      }
      if(muere1 == true && muere2 == true && muere3 == true){
        juegoPasado = true;
      }
    }
    else{
      if(firstTime == false){
        reiniciador.restart();
        firstTime = true;
      }
      else{
        sgsR = reiniciador.getElapsedTime().asSeconds();
        AnimacionPengoMuriendo();
        //cout << sgsR << endl;
        if(sgsR >= 1.8){
          j1->warp(16, 9);
          j1->getSprite()->setTextureRect(sf::IntRect(96, 1, 16, 15));
        }
        if(sgsR >= 2){
          reiniciador.restart();
          reventao = false;
        }
      }
    }
    if(creareloj == false){
      this->dibujar(); 
    }
  }
}

void Juego::EscribirTexto(){
  sf::Font font;
  if (!font.loadFromFile("resources/fonts/PTS55F.ttf"))
  {
    std::cerr << "Error cargando la fuente PTS55F.ttf";
  }
  sf::Text text;
  text.setFont(font);
  text.setString("HAS GANADO");
  text.setCharacterSize(40);
  text.setColor(sf::Color::Red);
  text.setStyle(sf::Text::Bold);

  text.setPosition(200, 200);
  
  ventana->draw(text);
  ventana->display();
}

void Juego::iniciar(){
  j1 = new Jugador();
  j1->getSprite()->setPosition(j1->getCoors().x, j1->getCoors().y);
  evento = new sf::Event();
  maposo = new Map(matrixMapa1);
  enemigos[0] = new Enemigo(176, 160);
  enemigos[1] = new Enemigo(312, 192);
  enemigos[2] = new Enemigo(224, 208);
}

void Juego::inicializarTodo(){
  posx = 0, posy = 0;
  right = false, left = false, up = false, down = false;
  pulsado = false, pulsadoD = false, pulsadoA = false, pulsadoDown = false;
  esGolpeado = false, esGolpeado2 = false, esGolpeado3 = false;
  entrando = false;
  x = 0, y = 0, z = 0, j = 0;
  izda = false, arriba = false, dreta = false, abajo = false;
  reventao = false, toparao = false;
  xx = 0, yy = 0, xxd = 0, yyd = 0, xxdd = 0, yydd = 0, xxx = 0, yyy = 0;
  ux = 0, uy = 0, uxx = 0, uyy = 0, dx = 0, dy = 0, dxx = 0, dyy = 0;
  avanza = 0, palante = 0;
  posAnt = 0, posDesp = 0, posAntDe = 0, posDespDe = 0, posAntUp = 0, posDespUp = 0, posAntDo = 0, posDespDo = 0;
  contIt = 0, conti = 0, contiD = 0, contiA = 0, contiAb = 0;
  nuevax = 0, nuevay = 0;
  comienza = 0;
  sgs = 0, sgs2 = 0, sgs3 = 0, sgsR = 0;
  sgsEnemy = 0;
  eliminao = false, eliminao2 = false, eliminao3 = false;
  dibujado = false, chocado = false, chocadoD = false, chocadoA = false, chocadoDo = false, espacio = false;
  firstTime = false, secondTime = false;
  contMuertos = 0;
  juegoPasado = false, muere1 = false, muere2 = false, muere3 = false;
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

void Juego::animacionAndarDerecha(){
  sgsAnd = andador.getElapsedTime().asSeconds();
  if(sgsAnd >= 0.1){
    andandico++;
    this->spriteAndarDerecha(andandico);
    if(andandico == 2){
        andandico = -1;
        contaorR++;
    }
    andador.restart();
  }
}

void Juego::spriteAndarDerecha(int x){
  if(x == 0){
    j1->getSprite()->setTextureRect(sf::IntRect(96, 1, 16, 15));
  }
  else if(x == 1){
    j1->getSprite()->setTextureRect(sf::IntRect(113, 0, 16, 15));
  }
}


void Juego::procesarEventos(){
    switch (evento->type)
    {
        case sf::Event::Closed:
            exit(1);
            break;
        case sf::Event::KeyPressed:
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            ventana->close();
            break;
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            walkR = true;
            dreta = true;
            izda = false;
            arriba = false;
            abajo = false;
            procesarColisiones();
            if(right == true){
              j1->getSprite()->setTextureRect(sf::IntRect(96, 1, 16, 15));
              j1->move(Stay);
              right = false;
            }
            else{
              //antepos = j1->getSprite()->getPosition().x;
              j1->move(Right);
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
            procesarColisiones();
            if(left == true){
              j1->getSprite()->setTextureRect(sf::IntRect(32, 1, 16, 15));
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
            procesarColisiones();
            if(up == true){
              j1->getSprite()->setTextureRect(sf::IntRect(64, 0, 16, 16));
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
            procesarColisiones();
            if(down == true){
              j1->getSprite()->setTextureRect(sf::IntRect(0, 0, 16, 16));
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
              empujeL = true;
              xxx = xx;
              yyy = yy;
              pulsado = true;
            }
            if(right == true && dreta == true){
              empujeR = true;
              xxdd = xxd;
              yydd = yyd;
              pulsadoD = true;
            }
            if(up == true && arriba == true){
              empujeU = true;
              uxx = ux;
              uyy = uy;
              pulsadoA = true;
            }
            if(down == true && abajo == true){
              empujeD = true;
              dxx = dx;
              dyy = dy;
              pulsadoDown = true;
            }
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
            restarteo = true;
            cout << "Reiniciando nivel" << endl; 
            if(cargaNivel == 0){
              cout << "Carga mapa 1" << endl;
              maposo = new Map(matrixMapa1);
            }else{
              cout << "Carga mapa 2" << endl;
              maposo = new Map(matrixMapa2);
            }
            inicializarTodo();
          }
          if(pulsarG == false){
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::G)){
              cout << "Modo DIOS" << endl;
              godmode = true;
              pulsarG = true;
            }
          }
          if(cargaNivel == 0){
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
              cargaNivel = 1;
              cout << "Next Level" << endl;
              maposo = new Map(matrixMapa2);
              this->inicializarTodo();
              j1->warp(16, 9);
              dibujaisimo = true;
            }
          }
        
          break;
        default:
          break;
    }
}

void Juego::comprobarJuegoPasado(){
  for(int i = 0; i < 3 && juegoPasado == false; i++){
    if(enemigos[i] != nullptr){
      if(enemigos[i]->getSprite()->getPosition().x == 0){
        if(i == 0 && muere1 == false){
          //cout << enemigos[i]->getSprite()->getPosition().x << endl;
          //cout << "Entra " << i << endl;
          muere1 = true;
        }
        if(i == 1 && muere2 == false){
          //cout << "Entra " << i << endl;
          muere2 = true;
        }
        if(i == 2 && muere3 == false){
          //cout << "Entra " << i << endl;
          muere3 = true;
        }
      }
    }else{
      if(i == 0){
        muere1 = false;
      }
      else if(i == 1){
        muere2 = false;
      }
      else if(i == 2){
        muere3 = false;
      }
    }
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

void Juego::regenerarSnoobee(){
  sgsEnemy = nuevoEnemigo.getElapsedTime().asSeconds();
  if(sgsEnemy >= 20){
    //cout << "Entra al reloj" << endl;
    enemigos[0]->restartSprite();
    enemigos[0]->warp(176, 160);
    eliminao = false;
    muere1 = false;
    esGolpeado = false;
    secondTime = false;
    //contMuertos--;
    nuevoEnemigo.restart();
  }
}

void Juego::regenerarSnoobee2(){
  sgsEnemy = nuevoEnemigo.getElapsedTime().asSeconds();
  if(sgsEnemy >= 20){
    //cout << "Entra al reloj" << endl;
    enemigos[1]->restartSprite();
    enemigos[1]->warp(312, 192);
    eliminao2 = false;
    muere2 = false;
    esGolpeado2 = false;
    secondTime = false;
    //contMuertos--;
    nuevoEnemigo.restart();
  }
}

void Juego::regenerarSnoobee3(){
  sgsEnemy = nuevoEnemigo.getElapsedTime().asSeconds();
  if(sgsEnemy >= 20){
    //cout << "Entra al reloj" << endl;
    enemigos[2]->restartSprite();
    enemigos[2]->warp(224, 208);
    eliminao3 = false;
    muere3 = false;
    esGolpeado3 = false;
    secondTime = false;
    //contMuertos--;
    nuevoEnemigo.restart();
  }
}

void Juego::animacionEmpujarIzda(){
  animaEmpuja = relojEmpujador.getElapsedTime().asSeconds();
  if(animaEmpuja >= 0.1){
    cambiarEmpujeIzda(empujar);
    empujar++;
    if(empujar == 4){
      empujar = 0;
      empujeL = false;
    }
    relojEmpujador.restart();
  }
}

void Juego::cambiarEmpujeIzda(int x){
  if(x == 0){
    j1->getSprite()->setTextureRect(sf::IntRect(48, 16, 16, 16));
  }
  if(x == 1){
    j1->getSprite()->setTextureRect(sf::IntRect(32, 16, 16, 16));
  }
  if(x == 2){
    j1->getSprite()->setTextureRect(sf::IntRect(48, 16, 16, 16));
  }
  if(x == 3){
    j1->getSprite()->setTextureRect(sf::IntRect(48, 1, 16, 15));
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
      if(matrixMapa1[xxx][yyy] != 2 && matrixMapa1[xxx][yyy] != 3 && matrixMapa1[xxx][yyy] != 4 && matrixMapa1[xxx][yyy] != 5){
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
      }
    }
  }
}

void Juego::animacionEmpujarRight(){
  animaEmpuja = relojEmpujador.getElapsedTime().asSeconds();
  if(animaEmpuja >= 0.15){
    cambiarEmpujeRight(empujar);
    empujar++;
    if(empujar == 4){
      empujar = 0;
      empujeR = false;
    }
    relojEmpujador.restart();
  }
}

void Juego::cambiarEmpujeRight(int x){
  if(x == 0){
    j1->getSprite()->setTextureRect(sf::IntRect(112, 16, 16, 16));
  }
  if(x == 1){
    j1->getSprite()->setTextureRect(sf::IntRect(96, 16, 16, 16));
  }
  if(x == 2){
    j1->getSprite()->setTextureRect(sf::IntRect(112, 16, 16, 16));
  }
  if(x == 3){
    j1->getSprite()->setTextureRect(sf::IntRect(96, 1, 16, 15));
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
      if(matrixMapa1[xxdd][yydd] != 2 && matrixMapa1[xxdd][yydd] != 3 && matrixMapa1[xxdd][yydd] != 4 && matrixMapa1[xxdd][yydd] != 5){
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
      }
    }
  }
}

void Juego::animacionEmpujarUp(){
  animaEmpuja = relojEmpujador.getElapsedTime().asSeconds();
  if(animaEmpuja >= 0.15){
    cambiarEmpujeUp(empujar);
    empujar++;
    if(empujar == 4){
      empujar = 0;
      empujeU = false;
    }
    relojEmpujador.restart();
  }
}

void Juego::cambiarEmpujeUp(int x){
  if(x == 0){
    j1->getSprite()->setTextureRect(sf::IntRect(80, 16, 16, 16));
  }
  if(x == 1){
    j1->getSprite()->setTextureRect(sf::IntRect(64, 16, 16, 16));
  }
  if(x == 2){
    j1->getSprite()->setTextureRect(sf::IntRect(80, 16, 16, 16));
  }
  if(x == 3){
    j1->getSprite()->setTextureRect(sf::IntRect(64, 0, 16, 16));
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
      if(matrixMapa1[uxx][uyy] != 2 && matrixMapa1[uxx][uyy] != 3 && matrixMapa1[uxx][uyy] != 4 && matrixMapa1[uxx][uyy] != 5){
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
      }
    }
  }
}

void Juego::animacionEmpujarDown(){
  animaEmpuja = relojEmpujador.getElapsedTime().asSeconds();
  if(animaEmpuja >= 0.15){
    cambiarEmpujeDown(empujar);
    empujar++;
    if(empujar == 4){
      empujar = 0;
      empujeD = false;
    }
    relojEmpujador.restart();
  }
}

void Juego::cambiarEmpujeDown(int x){
  if(x == 0){
    j1->getSprite()->setTextureRect(sf::IntRect(16, 16, 16, 16));
  }
  if(x == 1){
    j1->getSprite()->setTextureRect(sf::IntRect(0, 16, 16, 16));
  }
  if(x == 2){
    j1->getSprite()->setTextureRect(sf::IntRect(16, 16, 16, 16));
  }
  if(x == 3){
    j1->getSprite()->setTextureRect(sf::IntRect(0, 0, 16, 16));
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
        if(matrixMapa1[dxx][dyy] != 2 && matrixMapa1[dxx][dyy] != 3 && matrixMapa1[dxx][dyy] != 4 && matrixMapa1[dxx][dyy] != 5)
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

void Juego::cambiaAnimacionIz(int x){
  sgsA = relojAnimator.getElapsedTime().asSeconds();
  if(sgsA >= 0.2){
      //cout << "Entra en 2" << endl;
    if(esGolpeado3 == true){
        if(x == 0){
          //cout << "Cambia textura" << endl;
          enemigos[2]->getSprite()->setTextureRect(sf::IntRect(224, 190, 16, 16));
          animaAvanza++;
        }
        if(x == 1){
          //cout << "Cambia textura 2" << endl;
          enemigos[2]->getSprite()->setTextureRect(sf::IntRect(240, 190, 16, 16));
        }
    }
    if(esGolpeado2 == true){
      //cout << "Entra en 1" << endl;
      if(x == 0){
        //cout << "Cambia textura" << endl;
        enemigos[1]->getSprite()->setTextureRect(sf::IntRect(224, 190, 16, 16));
        animaAvanza++;
      }
      if(x == 1){
        //cout << "Cambia textura 2" << endl;
        enemigos[1]->getSprite()->setTextureRect(sf::IntRect(240, 190, 16, 16));
      }
    }
    if(esGolpeado == true){
      //cout << "Entra en 0" << endl;
      if(x == 0){
        enemigos[0]->getSprite()->setTextureRect(sf::IntRect(224, 190, 16, 16));
        animaAvanza++;
      }
      if(x == 1){
        enemigos[0]->getSprite()->setTextureRect(sf::IntRect(240, 190, 16, 16));
      }
    }
    relojAnimator.restart();
  }
}

void Juego::choqueBloquePengoIz(){
  if(posAnt != posDesp){
    if(maposo->sprites[xxx][yyy] != nullptr){
      if(enemigos[0] != nullptr){
        if(maposo->sprites[xxx][yyy]->getGlobalBounds().intersects(enemigos[0]->getSprite()->getGlobalBounds())){
          //cout << "Golpea a este" << endl;
          esGolpeado = true;
          enemigos[0]->getSprite()->setPosition(maposo->sprites[xxx][yyy]->getPosition().x- 16, maposo->sprites[xxx][yyy]->getPosition().y);
        }
      }
      if(maposo->sprites[xxx][yyy]->getGlobalBounds().intersects(enemigos[1]->getSprite()->getGlobalBounds())){
        //cout << "Golpea a este" << endl;
        esGolpeado2 = true;
        enemigos[1]->getSprite()->setPosition(maposo->sprites[xxx][yyy]->getPosition().x- 16, maposo->sprites[xxx][yyy]->getPosition().y);
      }
      if(maposo->sprites[xxx][yyy]->getGlobalBounds().intersects(enemigos[2]->getSprite()->getGlobalBounds())){
        //cout << "Golpea a este" << endl;
        esGolpeado3 = true;
        enemigos[2]->getSprite()->setPosition(maposo->sprites[xxx][yyy]->getPosition().x- 16, maposo->sprites[xxx][yyy]->getPosition().y);
        //animaAvanza++;
      }
      this->cambiaAnimacionIz(animaAvanza);
      cout << animaAvanza << endl;
    }
    if(pulsado == false){
      //cout << "Confirmamos choque" << endl;
      chocado = true;
      guardado = maposo->sprites[xxx][yyy];
      if(esGolpeado == true){
        animaAvanza = 0;
        enemigos[0]->getSprite()->setPosition(0, 0);
        enemigos[0]->hacerTransparente();
        eliminao = true;
      }
      if(esGolpeado2 == true){
        animaAvanza = 0;
        enemigos[1]->getSprite()->setPosition(0, 0);
        enemigos[1]->hacerTransparente();
        eliminao2 = true;
      } 
      if(esGolpeado3 == true){
        animaAvanza = 0;
        enemigos[2]->getSprite()->setPosition(0, 0);
        enemigos[2]->hacerTransparente();
        eliminao3 = true;
      }
    }
  }
}

void Juego::cambiaAnimacionDe(int x){
  sgsA = relojAnimator.getElapsedTime().asSeconds();
  if(sgsA >= 0.3){
      //cout << "Entra en 2" << endl;
    if(esGolpeado3 == true){
        if(x == 0){
          //cout << "Cambia textura" << endl;
          enemigos[2]->getSprite()->setTextureRect(sf::IntRect(160, 192, 16, 16));
          animaAvanza++;
        }
        if(x == 1){
          //cout << "Cambia textura 2" << endl;
          enemigos[2]->getSprite()->setTextureRect(sf::IntRect(176, 192, 16, 16));
        }
    }
    if(esGolpeado2 == true){
      cout << "Entra en 1" << endl;
      if(x == 0){
        //cout << "Cambia textura" << endl;
        enemigos[1]->getSprite()->setTextureRect(sf::IntRect(160, 192, 16, 16));
        animaAvanza++;
      }
      if(x == 1){
        //cout << "Cambia textura 2" << endl;
        enemigos[1]->getSprite()->setTextureRect(sf::IntRect(176, 192, 16, 16));
      }
    }
    if(esGolpeado == true){
      cout << "Entra en 0" << endl;
      if(x == 0){
        enemigos[0]->getSprite()->setTextureRect(sf::IntRect(160, 192, 16, 16));
        animaAvanza++;
      }
      if(x == 1){
        enemigos[0]->getSprite()->setTextureRect(sf::IntRect(176, 192, 16, 16));
      }
    }
    relojAnimator.restart();
  }
}

void Juego::choqueBloquePengoDe(){
  if(posAntDe != posDespDe){
    if(maposo->sprites[xxdd][yydd] != nullptr){
      if(enemigos[0] != nullptr){
        if(maposo->sprites[xxdd][yydd]->getGlobalBounds().intersects(enemigos[0]->getSprite()->getGlobalBounds())){
          esGolpeado = true;
          enemigos[0]->getSprite()->setPosition(maposo->sprites[xxdd][yydd]->getPosition().x+ 16, maposo->sprites[xxdd][yydd]->getPosition().y);
        }
      }
      if(maposo->sprites[xxdd][yydd]->getGlobalBounds().intersects(enemigos[1]->getSprite()->getGlobalBounds())){
        esGolpeado2 = true;
        enemigos[1]->getSprite()->setPosition(maposo->sprites[xxdd][yydd]->getPosition().x+ 16, maposo->sprites[xxdd][yydd]->getPosition().y);
      }
      if(maposo->sprites[xxdd][yydd]->getGlobalBounds().intersects(enemigos[2]->getSprite()->getGlobalBounds())){
        //cout << "Esta intersectando" << endl;
        esGolpeado3 = true;
        enemigos[2]->getSprite()->setPosition(maposo->sprites[xxdd][yydd]->getPosition().x+ 16, maposo->sprites[xxdd][yydd]->getPosition().y);
      }
      this->cambiaAnimacionDe(animaAvanza);
      //cout << animaAvanza << endl;
    }
    if(pulsadoD == false){
      //cout << "Confirmamos choque" << endl;
      chocadoD = true;
      guardadoD = maposo->sprites[xxdd][yydd];
      if(esGolpeado == true){
        animaAvanza = 0;
        enemigos[0]->getSprite()->setPosition(0, 0);
        enemigos[0]->hacerTransparente();
        eliminao = true;
      }
      if(esGolpeado2 == true){
        animaAvanza = 0;
        enemigos[1]->getSprite()->setPosition(0, 0);
        enemigos[1]->hacerTransparente();
        eliminao2 = true;
      } 
      if(esGolpeado3 == true){
        animaAvanza = 0;
        enemigos[2]->getSprite()->setPosition(0, 0);
        enemigos[2]->hacerTransparente();
        eliminao3 = true;
      }
    }
  }
}

void Juego::cambiaAnimacionUp(int x){
  sgsA = relojAnimator.getElapsedTime().asSeconds();
  if(sgsA >= 0.3){
      cout << "Entra en 2" << endl;
    if(esGolpeado3 == true){
        if(x == 0){
          //cout << "Cambia textura" << endl;
          enemigos[2]->getSprite()->setTextureRect(sf::IntRect(128, 192, 16, 16));
          animaAvanza++;
        }
        if(x == 1){
          //cout << "Cambia textura 2" << endl;
          enemigos[2]->getSprite()->setTextureRect(sf::IntRect(144, 192, 16, 16));
        }
    }
    if(esGolpeado2 == true){
      cout << "Entra en 1" << endl;
      if(x == 0){
        //cout << "Cambia textura" << endl;
        enemigos[1]->getSprite()->setTextureRect(sf::IntRect(128, 192, 16, 16));
        animaAvanza++;
      }
      if(x == 1){
        //cout << "Cambia textura 2" << endl;
        enemigos[1]->getSprite()->setTextureRect(sf::IntRect(144, 192, 16, 16));
      }
    }
    if(esGolpeado == true){
      cout << "Entra en 0" << endl;
      if(x == 0){
        enemigos[0]->getSprite()->setTextureRect(sf::IntRect(128, 192, 16, 16));
        animaAvanza++;
      }
      if(x == 1){
        enemigos[0]->getSprite()->setTextureRect(sf::IntRect(144, 192, 16, 16));
      }
    }
    relojAnimator.restart();
  }
}

void Juego::choqueBloquePengoUp(){
  if(posAntUp != posDespUp){
    if(maposo->sprites[uxx][uyy] != nullptr){
      if(enemigos[0] != nullptr){
        if(maposo->sprites[uxx][uyy]->getGlobalBounds().intersects(enemigos[0]->getSprite()->getGlobalBounds())){
          esGolpeado = true;
          enemigos[0]->getSprite()->setPosition(maposo->sprites[uxx][uyy]->getPosition().x, maposo->sprites[uxx][uyy]->getPosition().y - 16);
        }
      }
      if(maposo->sprites[uxx][uyy]->getGlobalBounds().intersects(enemigos[1]->getSprite()->getGlobalBounds())){
        esGolpeado2 = true;
        enemigos[1]->getSprite()->setPosition(maposo->sprites[uxx][uyy]->getPosition().x, maposo->sprites[uxx][uyy]->getPosition().y - 16);
      }
      if(maposo->sprites[uxx][uyy]->getGlobalBounds().intersects(enemigos[2]->getSprite()->getGlobalBounds())){
        esGolpeado3 = true;
        enemigos[2]->getSprite()->setPosition(maposo->sprites[uxx][uyy]->getPosition().x, maposo->sprites[uxx][uyy]->getPosition().y - 16);
      }
      this->cambiaAnimacionUp(animaAvanza);
    }
    if(pulsadoA == false){
      //cout << "Confirmamos choque" << endl;
      chocadoA = true;
      guardadoA = maposo->sprites[uxx][uyy];
      if(esGolpeado == true){
        animaAvanza = 0;
        enemigos[0]->getSprite()->setPosition(0, 0);
        enemigos[0]->hacerTransparente();
        eliminao = true;
      }
      if(esGolpeado2 == true){
        animaAvanza = 0;
        enemigos[1]->getSprite()->setPosition(0, 0);
        enemigos[1]->hacerTransparente();
        eliminao2 = true;
      } 
      if(esGolpeado3 == true){
        animaAvanza = 0;
        enemigos[2]->getSprite()->setPosition(0, 0);
        enemigos[2]->hacerTransparente();
        eliminao3 = true;
      }
    }
  }
}

void Juego::cambiaAnimacionDown(int x){
  sgsA = relojAnimator.getElapsedTime().asSeconds();
  if(sgsA >= 0.3){
      cout << "Entra en 2" << endl;
    if(esGolpeado3 == true){
        if(x == 0){
          enemigos[2]->getSprite()->setTextureRect(sf::IntRect(128, 192, 16, 16));
          animaAvanza++;
        }
        if(x == 1){
          enemigos[2]->getSprite()->setTextureRect(sf::IntRect(144, 192, 16, 16));
        }
    }
    if(esGolpeado2 == true){
      cout << "Entra en 1" << endl;
      if(x == 0){
        //cout << "Cambia textura" << endl;
        enemigos[1]->getSprite()->setTextureRect(sf::IntRect(128, 192, 16, 16));
        animaAvanza++;
      }
      if(x == 1){
        //cout << "Cambia textura 2" << endl;
        enemigos[1]->getSprite()->setTextureRect(sf::IntRect(144, 192, 16, 16));
      }
    }
    if(esGolpeado == true){
      cout << "Entra en 0" << endl;
      if(x == 0){
        enemigos[0]->getSprite()->setTextureRect(sf::IntRect(128, 192, 16, 16));
        animaAvanza++;
      }
      if(x == 1){
        enemigos[0]->getSprite()->setTextureRect(sf::IntRect(144, 192, 16, 16));
      }
    }
    relojAnimator.restart();
  }
}

void Juego::choqueBloquePengoDown(){
  if(posAntDo != posDespDo){
    if(maposo->sprites[dxx][dyy] != nullptr){
      if(enemigos[0] != nullptr){
        if(maposo->sprites[dxx][dyy]->getGlobalBounds().intersects(enemigos[0]->getSprite()->getGlobalBounds())){
          esGolpeado = true;
          enemigos[0]->getSprite()->setPosition(maposo->sprites[dxx][dyy]->getPosition().x, maposo->sprites[dxx][dyy]->getPosition().y + 16);
        }
      }
      if(maposo->sprites[dxx][dyy]->getGlobalBounds().intersects(enemigos[1]->getSprite()->getGlobalBounds())){
        esGolpeado2 = true;
        enemigos[1]->getSprite()->setPosition(maposo->sprites[dxx][dyy]->getPosition().x, maposo->sprites[dxx][dyy]->getPosition().y + 16);
      }
      if(maposo->sprites[dxx][dyy]->getGlobalBounds().intersects(enemigos[2]->getSprite()->getGlobalBounds())){
        esGolpeado3 = true;
        enemigos[2]->getSprite()->setPosition(maposo->sprites[dxx][dyy]->getPosition().x, maposo->sprites[dxx][dyy]->getPosition().y + 16);
      }
      this->cambiaAnimacionDown(animaAvanza);
    }
    if(pulsadoDown == false){
      //cout << "Confirmamos choque" << endl;
      chocadoDo = true;
      guardadoDo = maposo->sprites[dxx][dyy];
      if(esGolpeado == true){
        animaAvanza = 0;
        enemigos[0]->getSprite()->setPosition(0, 0);
        enemigos[0]->hacerTransparente();
        eliminao = true;
      }
      if(esGolpeado2 == true){
        animaAvanza = 0;
        enemigos[1]->getSprite()->setPosition(0, 0);
        enemigos[1]->hacerTransparente();
        eliminao2 = true;
      } 
      if(esGolpeado3 == true){
        animaAvanza = 0;
        enemigos[2]->getSprite()->setPosition(0, 0);
        enemigos[2]->hacerTransparente();
        eliminao3 = true;
      }
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
  if(j1->getSprite()->getGlobalBounds().intersects(spriteRectR)){
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
      guardado->setTextureRect(sf::IntRect(708 + 160, 48, 16, 16));
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
      guardadoD->setTextureRect(sf::IntRect(708 + 160, 48, 16, 16));
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
      guardadoA->setTextureRect(sf::IntRect(708 + 160, 48, 16, 16));
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
      guardadoDo->setTextureRect(sf::IntRect(708 + 160, 48, 16, 16));
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
  if(sgs3 >= 0.05){
    palante++;
    this->SpriteMuerto(palante);
    if(palante == 2){
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