#include "Tour.h"
#include "RessourceLoader.hpp"
#include "globalClock.hpp"
#include "constantes.hpp"

Tour::Tour() {
    tour1.setTexture(RessourceLoader::getTexture("sprites/tour.png"));
    tour2.setTexture(RessourceLoader::getTexture("sprites/tour.png"));
    tour3.setTexture(RessourceLoader::getTexture("sprites/tour.png"));
}

void Tour::update(bool climbing) {
    currentPosition += globalClock::getClock().frameTime().asSeconds() * 1000 * (climbing ? CLIMB_SPEED_COEFF : -FALL_SPEED_COEFF);

    tour1.setPosition(0, currentPosition - WINDOW_SIZE_Y);
    tour2.setPosition(0, currentPosition);
    tour3.setPosition(0, currentPosition + WINDOW_SIZE_Y);

    if (currentPosition > WINDOW_SIZE_Y)
        currentPosition = 0;
    else if (currentPosition < 0)
        currentPosition = WINDOW_SIZE_Y;
}

void Tour::draw(sf::RenderWindow& window) {
    window.draw(tour1);
    window.draw(tour2);
    window.draw(tour3);
}


