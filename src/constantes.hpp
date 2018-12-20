#ifndef CONSTANTES_HPP
#define CONSTANTES_HPP

#include <cstddef>

//Taille max de la fenetre de rendu en x
static constexpr unsigned int WINDOW_SIZE_X = 1200;

//Taille max de la fenetre de rendu en y
static constexpr unsigned int WINDOW_SIZE_Y = 720;

constexpr size_t PIXEL_SIZE = 20;

constexpr unsigned int INITIAL_SPRITE_HEIGHT = 600;
constexpr unsigned int INITIAL_SPRITE_WIDTH = 340;

constexpr unsigned int TARGET_SPRITE_WIDTH = 4*PIXEL_SIZE;

constexpr unsigned int TOWER_X1 = 245;
constexpr unsigned int TOWER_X2 = 990;

constexpr double SPRITE_RATIO = (double)TARGET_SPRITE_WIDTH / INITIAL_SPRITE_WIDTH;
constexpr double TARGET_SPRITE_HEIGHT = SPRITE_RATIO * INITIAL_SPRITE_HEIGHT;

#endif // CONSTANTES_HPP