#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

#define kVel 20

#include "Enemigo.h"  
  
    Enemigo::Enemigo(int posx, int posy){
        vidas = 3;
        this->warp(posx, posy);
        velocidad = 0.5f;
        tex = new Texture();
        if (!tex->loadFromFile("resources/pengo.png")) {
            std::cerr << "Error cargando la imagen pengo.png";
            exit(0);
        } 
        enemy = new Sprite(*tex);
        //Le pongo el centroide donde corresponde
        enemy->setOrigin(8, 8);
        //Cojo el sprite que me interesa por defecto del sheet
        enemy->setTextureRect(sf::IntRect(128, 144, 16, 16));
        enemy->setPosition(xxx, yyy);
    }

    Enemigo::~Enemigo(){
        
    }

    bool Enemigo::isMoving(){
        return !(xxx == gridX * 8 && yyy == gridY * 8);
    }

    void Enemigo::warp(int newGridX, int newGridY){
        gridX = newGridX;
        gridY = newGridY;

        xxx = newGridX * 8;
        yyy = newGridY * 8;
    }

    void Enemigo::move(DirE dir){

        if (isMoving())
            return;

        if (dir == DirE::Arriba)
            gridY -= 1;
        else if (dir == DirE::Abajo)
            gridY += 1;
        if (dir == DirE::Izquierda)
            gridX -= 1;
        else if (dir == DirE::Derecha)
            gridX += 1;
        if(dir == DirE::Quedate){
            gridX += 0;
            gridY -= 0;
        }
    }

    void Enemigo::cambiarSpriteR(int x){
        if(x == 0){
            enemy->setTextureRect(sf::IntRect(224, 144, 16, 16));
        }
        else{
            enemy->setTextureRect(sf::IntRect(240, 144, 16, 16));
        }
    }

    void Enemigo::cambiarSpriteD(int x){
        if(x == 0){
            enemy->setTextureRect(sf::IntRect(128, 144, 16, 16));
        }
        else{
            enemy->setTextureRect(sf::IntRect(144, 144, 16, 16));
        }
    }

    void Enemigo::cambiarSpriteU(int x){
        if(x == 0){
            enemy->setTextureRect(sf::IntRect(192, 144, 16, 16));
        }
        else{
            enemy->setTextureRect(sf::IntRect(208, 144, 16, 16));
        }
    }

    void Enemigo::cambiarSpriteL(int x){
        if(x == 0){
            enemy->setTextureRect(sf::IntRect(160, 144, 16, 16));
        }
        else{
            enemy->setTextureRect(sf::IntRect(176, 144, 16, 16));
        }
    }

    void Enemigo::update(Map *maposo, bool esGolpeado){
        if(esGolpeado == false){  
            enemy->setPosition(xxx, yyy);

            if (xxx < gridX * 8) //moving right
                xxx = min(xxx + velocidad, float(gridX * 8));
            else if (xxx > gridX * 8) //moving left
                xxx = max(xxx - velocidad, float(gridX * 8));

            if (yyy < gridY * 8) //moving down
                yyy = min(yyy + velocidad, float(gridY * 8));
            else if (yyy > gridY * 8) //moving up
                yyy = max(yyy - velocidad, float(gridY * 8));
      
            procesarColisionesEnemigo(maposo);
            int random = rand()%4;
            float sgs2 = relojero.getElapsedTime().asSeconds();
            if(sgs2 >= 0.3){
                //cout << random << endl;
                if(right == false && down == false && up == false && left == false){
                    left = false;
                    right = false;
                    up = false;
                    down = false;
                    if(random == 0){
                        this->move(Derecha);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteR(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }else if(random == 1){
                        this->move(Abajo);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteD(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }else if(random == 2){
                        this->move(Izquierda);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteL(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }else{
                        this->move(Arriba);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteU(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }
                }
                if(right == true && down == true && up == true && left == false){
                    left = false;
                    right = false;
                    up = false;
                    down = false;
                    if(random == 0 || random == 1 || random == 2 || random == 3){
                        this->move(Izquierda);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteL(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }
                }
                if(right == true && down == true && up == false && left == true){
                    left = false;
                    right = false;
                    up = false;
                    down = false;
                    if(random == 0 || random == 1 || random == 2 || random == 3){
                        this->move(Arriba);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteU(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }
                }
                if(right == true && down == false && up == true && left == true){
                    left = false;
                    right = false;
                    up = false;
                    down = false;
                    if(random == 0 || random == 1){
                        this->move(Abajo);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteD(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }else if(random == 2 || random == 3){
                        this->move(Derecha);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteD(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }
                }
                if(right == false && down == true && up == true && left == true){
                    left = false;
                    right = false;
                    up = false;
                    down = false;
                    if(random == 0 || random == 1 || random == 2 || random == 3){
                        this->move(Derecha);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteR(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }
                }
                if(right == false && down == false && up == true && left == true){
                    left = false;
                    right = false;
                    up = false;
                    down = false;
                    if(random == 0 || random == 1 || random == 2 || random == 3){
                        this->move(Derecha);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteR(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }/*else if(random == 2 || random == 3){
                        this->move(Abajo);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteD(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }
                    */
                }
                if(right == false && down == true && up == false && left == true){
                    left = false;
                    right = false;
                    up = false;
                    down = false;
                    if(random == 0 || random == 1){
                        this->move(Derecha);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteR(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }else if(random == 2 || random == 3){
                        this->move(Arriba);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteU(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }
                }
                if(right == false && down == true && up == true && left == false){
                    left = false;
                    right = false;
                    up = false;
                    down = false;
                    if(random == 0 || random == 1){
                        this->move(Derecha);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteR(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }else if(random == 2 || random == 3){
                        this->move(Izquierda);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteL(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }
                }
                if(right == true && down == false && up == false && left == true){
                    left = false;
                    right = false;
                    up = false;
                    down = false;
                    if(random == 0 || random == 1){
                        this->move(Abajo);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteD(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }else if(random == 2 || random == 3){
                        this->move(Arriba);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteU(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }
                }
                if(right == true && down == false && up == true && left == false){
                    left = false;
                    right = false;
                    up = false;
                    down = false;
                    if(random == 0 || random == 1){
                        this->move(Abajo);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteD(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }else if(random == 2 || random == 3){
                        this->move(Izquierda);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteL(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }
                }
                if(right == true && down == true && up == false && left == false){
                    left = false;
                    right = false;
                    up = false;
                    down = false;
                    if(random == 0 || random == 1){
                        this->move(Arriba);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteU(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }else if(random == 2 || random == 3){
                        this->move(Izquierda);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteL(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }
                }
                if(right == true){
                    //cout << "Toca derecha" << endl;
                    left = false;
                    right = false;
                    up = false;
                    down = false;
                    if(random == 0){
                        this->move(Abajo);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteD(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }else if(random == 1){
                        this->move(Abajo);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteD(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }else if(random == 2){
                        this->move(Izquierda);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteL(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }else{
                        this->move(Arriba);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteU(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }
                }
                if(down == true){
                    //cout << "Toca abajo" << endl;
                    left = false;
                    right = false;
                    up = false;
                    down = false;
                    if(random == 0){
                        this->move(Derecha);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteR(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }else if(random == 1){
                        this->move(Arriba);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteD(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }else if(random == 2){
                        this->move(Izquierda);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteL(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }else{
                        this->move(Arriba);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteU(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }
                }
                if(up == true){
                    //cout << "Toca arriba" << endl;
                    left = false;
                    right = false;
                    up = false;
                    down = false;
                    if(random == 0){
                        this->move(Derecha);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteR(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }else if(random == 1){
                        this->move(Abajo);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteD(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }else if(random == 2){
                        this->move(Izquierda);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteL(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }else{
                        this->move(Abajo);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteD(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }
                }
                if(left == true){
                    //cout << "Toca izquierda" << endl;
                    left = false;
                    right = false;
                    up = false;
                    down = false;
                    if(random == 0){
                        this->move(Derecha);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteR(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }else if(random == 1){
                        this->move(Abajo);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteD(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }else if(random == 2){
                        this->move(Derecha);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteR(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }else{
                        this->move(Arriba);
                        sgs = relojaso.getElapsedTime().asSeconds();
                        if(sgs >= 0.2){
                            avanza++;
                            this->cambiarSpriteU(avanza);
                            if(avanza == 2){
                                // yasta = true;
                                avanza = -1;
                            }
                            relojaso.restart();
                        }
                    }
                }
                relojero.restart();
            }
        }
    }

    void Enemigo::procesarColisionesEnemigo(Map *maposo){
        for(int i = 0; i < 16; i++){
            for(int j = 0; j < 16; j++){
                if(maposo->matrixMapa[j][i] != 0){
                    FloatRect spriteRectR(maposo->sprites[j][i]->getPosition().x - 8, maposo->sprites[j][i]->getPosition().y, 16, 16);
                    FloatRect spriteRectD(maposo->sprites[j][i]->getPosition().x, maposo->sprites[j][i]->getPosition().y - 8, 16, 16);
                    FloatRect spriteRectL(maposo->sprites[j][i]->getPosition().x + 8, maposo->sprites[j][i]->getPosition().y, 16, 16);
                    FloatRect spriteRectU(maposo->sprites[j][i]->getPosition().x, maposo->sprites[j][i]->getPosition().y + 8, 16, 16);
                    FloatRect jugadorRect(enemy->getPosition().x, enemy->getPosition().y, 16, 16);
                    // colision a la derecha
                    if(jugadorRect.intersects(spriteRectR)){
                    //cout << "Tocando derecha" << endl;
                    right = true;
                    }
                    // colision a la izquierda
                    if(jugadorRect.intersects(spriteRectL)){
                    //cout << "Tocando izquierda" << endl;
                    left = true;
                    }
                    // colision arriba
                    if(jugadorRect.intersects(spriteRectU)){
                    //cout << "Tocando arriba" << endl;
                    up = true;
                    }
                    // colision abajo
                    if(jugadorRect.intersects(spriteRectD)){
                    //cout << "Tocando abajo" << endl;
                    down = true;
                    }
                    /*
                    FloatRect spriteRectR(maposo->sprites[j][i]->getPosition().x, maposo->sprites[j][i]->getPosition().y, 16, 16);
                    posicion = enemy->getPosition().x;
                    if(enemy->getGlobalBounds().intersects(maposo->sprites[j][i]->getGlobalBounds())){
                        if((posicion + 16) >= maposo->sprites[j][i]->getPosition().x){
                            cout << "Toca derecha" << endl;
                            right = true;
                        }
                        if((posicion - 16) <= maposo->sprites[j][i]->getPosition().x){
                            cout << "Toca izquierda" << endl;
                            left = true;
                        }
                        if((posicion + 16) >= maposo->sprites[j][i]->getPosition().y){
                            cout << "Toca abajo" << endl;
                            down = true;
                        }
                        if((posicion - 16) <= maposo->sprites[j][i]->getPosition().y){
                            cout << "Toca arriba" << endl;
                            up = true;
                        }
                    }
                    */
                }
            }
        }
    }

    Vector2f Enemigo::getCoors() {
        return Vector2f(xxx,yyy); 
    }

    void Enemigo::Draw(RenderWindow &window){
        window.draw(*enemy);
    }

    void Enemigo::restartSprite(){
        enemy->setColor(Color(255,255,255));
    }

    void Enemigo::hacerTransparente(){
        enemy->setColor(Color::Transparent);
    }

    Sprite *Enemigo::getSprite(){
        return enemy;
    }

    int Enemigo::getVidas(){
        return vidas;
    }