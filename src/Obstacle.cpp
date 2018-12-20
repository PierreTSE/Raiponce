#include "Obstacle.h"
#include "Utilities.hpp"
#include "constantes.hpp"
#include "globalClock.hpp"

Obstacle::Obstacle(float x, float y)
{
	spr_.setSize({ 50, 50 });
	spr_.setOrigin(25, 25);
	spr_.setPosition(x, y);
	spr_.setRotation(random(0, 360));
}

void Obstacle::draw(sf::RenderWindow & window)
{
	spr_.move(0, 500 * globalClock::getClock().frameTime().asSeconds());
	spr_.setRotation(spr_.getRotation() + 120 * globalClock::getClock().frameTime().asSeconds());

	if (spr_.getPosition().y - spr_.getGlobalBounds().width / 2 > WINDOW_SIZE_Y)
		dead = true;

	window.draw(spr_);
}

bool Obstacle::isDead()
{
	return dead;
}
