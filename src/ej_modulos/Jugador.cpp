#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

#define kVel 10

#include "Jugador.h"  
  
    Jugador::Jugador(){
        vidas = 3;
        this->warp(10, 10);
        velocidad = 0.5f;
        tex = new Texture();
        if (!tex->loadFromFile("resources/pengo.png")) {
            std::cerr << "Error cargando la imagen pengo.png";
            exit(0);
        } 
        jugador = new Sprite(*tex);
        //Le pongo el centroide donde corresponde
        jugador->setOrigin(8, 8);
        //Cojo el sprite que me interesa por defecto del sheet
        jugador->setTextureRect(sf::IntRect(96, 1, 16, 16));
    }

    Jugador::~Jugador(){
        
    }

    bool Jugador::isMoving(){
        return !(xxx == gridX * 16 && yyy == gridY * 16);
    }

    void Jugador::warp(int newGridX, int newGridY)
    {
        gridX = newGridX;
        gridY = newGridY;

        xxx = newGridX * 16;
        yyy = newGridY * 16;
    }


    void Jugador::move(Dir dir)
    {

        if (isMoving())
            return;

        if (dir == Dir::Up)
            gridY -= 1;
        else if (dir == Dir::Down)
            gridY += 1;
        if (dir == Dir::Left)
            gridX -= 1;
        else if (dir == Dir::Right)
            gridX += 1;
        if(dir == Dir::Stay){
            gridX += 0;
            gridY -= 0;
        }

    }

    void Jugador::update(){   
        jugador->setPosition(xxx, yyy);

        if (xxx < gridX * 16) //moving right
            xxx = min(xxx + velocidad, float(gridX * 16));
        else if (xxx > gridX * 16) //moving left
            xxx = max(xxx - velocidad, float(gridX * 16));

        if (yyy < gridY * 16) //moving down
            yyy = min(yyy + velocidad, float(gridY * 16));
        else if (yyy > gridY * 16) //moving up
            yyy = max(yyy - velocidad, float(gridY * 16));
    }

    Vector2f Jugador::getCoors() {
        return Vector2f(xxx,yyy); 
    }

    bool Jugador::perderVida(bool gameover){
        if(!gameover){
            vidas--;
            //cout << "Le quedan " << vidas << " vidas" << endl;
            if(vidas <= 0){
                gameover = true;
            }
        }
        return gameover;
    }

    void Jugador::Draw(RenderWindow &window){
        window.draw(*jugador);
    }

    void Jugador::restartSprite(){
        jugador->setColor(Color(255,255,255));
    }

    void Jugador::hacerTransparente(){
        jugador->setColor(Color::Transparent);
    }

    Sprite *Jugador::getSprite(){
        return jugador;
    }

    int Jugador::getVidas(){
        return vidas;
    }