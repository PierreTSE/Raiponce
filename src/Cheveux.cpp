#include "Cheveux.h"
#include "RessourceLoader.hpp"
#include "globalClock.hpp"
#include "constantes.hpp"
#include "Utilities.hpp"

Cheveux::Cheveux()
{
	cheveux1.setTexture(RessourceLoader::getTexture("sprites/hair.png"));
	cheveux2.setTexture(RessourceLoader::getTexture("sprites/hair.png"));

	nextShift = sf::seconds(random(3, 10));
	sens = random(-1, 1);

	x = (TOWER_X1 + TOWER_X2) / 2.f;

	width = cheveux1.getGlobalBounds().width;
}

void Cheveux::draw(sf::RenderWindow & window)
{
	currentPosition += globalClock::getClock().frameTime().asSeconds() * 1200;
	x += sens * globalClock::getClock().frameTime().asSeconds() * 200;
	timer += globalClock::getClock().frameTime();

	if (timer > nextShift) {
		nextShift = sf::seconds(random(1, 3));
		sens = random(-1, 1);
		timer = sf::Time::Zero;
	}

	if (x < TOWER_X1)
		x = TOWER_X1;
	else if (x > TOWER_X2 - cheveux1.getGlobalBounds().width)
		x = TOWER_X2 - cheveux1.getGlobalBounds().width;

	cheveux1.setPosition(x, currentPosition - 2*WINDOW_SIZE_Y);
	cheveux2.setPosition(x, currentPosition);

	window.draw(cheveux1);
	window.draw(cheveux2);

	if (currentPosition > 2*WINDOW_SIZE_Y)
		currentPosition = 0;
}
