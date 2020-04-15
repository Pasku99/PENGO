#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

#define kVel 0.02

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
        return !(xxx == gridX * 16 && yyy == gridY * 16);
    }

    void Enemigo::warp(int newGridX, int newGridY)
    {
        gridX = newGridX;
        gridY = newGridY;

        xxx = newGridX * 16;
        yyy = newGridY * 16;
    }
    /*
    void Enemigo::movement(DirE dir)
    {

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
    */

    void Enemigo::cambiarSpriteR(int x){
        if(x == 0){
            enemy->setTextureRect(sf::IntRect(224, 144, 16, 16));
            //enemy->move(kVel, 0);
        }
        else{
            enemy->setTextureRect(sf::IntRect(240, 144, 16, 16));
            //enemy->move(kVel, 0);
        }
    }

    void Enemigo::cambiarSpriteD(int x){
        if(x == 0){
            enemy->setTextureRect(sf::IntRect(128, 144, 16, 16));
            //enemy->move(0, -kVel);
        }
        else{
            enemy->setTextureRect(sf::IntRect(144, 144, 16, 16));
            //enemy->move(0, -kVel);
        }
    }

    void Enemigo::update(Map *maposo){
        procesarColisionesEnemigo(maposo);
        if(right == false){
            down = false;
            right = false;
            enemy->move(kVel, 0);
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
        else if(right == true && down == false){
            right = false;
            down = false;
            enemy->move(0, kVel);
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
        else if(right == false && down == true){
            right = false;
            down = false;
            enemy->move(kVel, 0);
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

    void Enemigo::procesarColisionesEnemigo(Map *maposo){
        for(int i = 0; i < 16; i++){
            for(int j = 0; j < 16; j++){
            if(maposo->sprites[j][i] != nullptr){
                FloatRect spriteRectR(maposo->sprites[j][i]->getPosition().x - 1, maposo->sprites[j][i]->getPosition().y, 16, 16);
                FloatRect spriteRectD(maposo->sprites[j][i]->getPosition().x, maposo->sprites[j][i]->getPosition().y - 1, 16, 16);
                FloatRect spriteRectL(maposo->sprites[j][i]->getPosition().x + 16, maposo->sprites[j][i]->getPosition().y, 16, 16);
                FloatRect spriteRectU(maposo->sprites[j][i]->getPosition().x, maposo->sprites[j][i]->getPosition().y + 16, 16, 16);
                FloatRect enemyRect(enemy->getPosition().x, enemy->getPosition().y, 15, 15);
                cout << "Enemigo: " << enemy->getPosition().x << ", " << enemy->getPosition().y << endl;
                if(enemyRect.intersects(spriteRectR)){
                    cout << "Enemigo tocando derecha" << endl;
                    right = true;
                }
                if(enemyRect.intersects(spriteRectD)){
                    cout << "Enemigo tocando abajo" << endl;
                    down = true;
                }
                /*
                if(enemyRect.intersects(spriteRectL)){
                    cout << "Enemigo tocando derecha" << endl;
                    right = true;
                }
                if(enemyRect.intersects(spriteRectU)){
                    cout << "Enemigo tocando derecha" << endl;
                    right = true;
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