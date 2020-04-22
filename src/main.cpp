#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/config.h"
#include "ej_modulos/Juego.h"

#define kVel 5

int main() {
  Juego *juego = new Juego(sf::Vector2u(500,500));
  return 0;
}