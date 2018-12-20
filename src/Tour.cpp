#include "Tour.h"
#include "RessourceLoader.hpp"
#include "globalClock.hpp"
#include "constantes.hpp"

Tour::Tour()
{
	tour1.setTexture(RessourceLoader::getTexture("tour.png"));
	tour2.setTexture(RessourceLoader::getTexture("tour.png"));
}

void Tour::draw(sf::RenderWindow & window)
{
	currentPosition += globalClock::getClock().frameTime().asSeconds() * 1000;

	tour1.setPosition(0, currentPosition - WINDOW_SIZE_Y);
	tour2.setPosition(0, currentPosition);

	window.draw(tour1);
	window.draw(tour2);

	if (currentPosition > WINDOW_SIZE_Y)
		currentPosition = 0;
}
