#include "Obstacle.h"
#include "Utilities.hpp"
#include "constantes.hpp"
#include "globalClock.hpp"
#include "RessourceLoader.hpp"

Obstacle::Obstacle(const std::string& texturePath)
{
    sprite_.setTexture(RessourceLoader::getTexture(texturePath));
    sprite_.setOrigin(sprite_.getGlobalBounds().width / 2, sprite_.getGlobalBounds().height / 2);
    sprite_.setRotation(random(0, 360));

    speed_ = random(200,700);
    rotSpeed_ = random(100, 220);
}

void Obstacle::draw(sf::RenderWindow& window)
{
    if(!(sprite_.getPosition().y - sprite_.getGlobalBounds().width / 2 > WINDOW_SIZE_Y))
    {
        sprite_.move(0, speed_ * globalClock::getClock().frameTime().asSeconds());
        sprite_.setRotation(sprite_.getRotation() + rotSpeed_ * globalClock::getClock().frameTime().asSeconds());
        window.draw(sprite_);
    }
}

void Obstacle::reset()
{
    speed_ = random(200,700);
    rotSpeed_ = random(100, 220);
	setPosition({(float)random(TOWER_X1, TOWER_X2), -sprite_.getGlobalBounds().height});
}

