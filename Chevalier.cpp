#include "Chevalier.hpp"
#include "src/RessourceLoader.hpp"

Chevalier::Chevalier()
{
    sprites_.emplace_back();
    sprites_.back().setTexture(RessourceLoader::getTexture("chevalier_haut"));
    sprites_.emplace_back();
    sprites_.back().setTexture(RessourceLoader::getTexture("chevalier_milieu"));
    sprites_.emplace_back();
    sprites_.back().setTexture(RessourceLoader::getTexture("chevalier_bas"));
}
