#include <SFML/Graphics.hpp>
#include "constantes.hpp"
#include "Tour.h"
#include "RessourceLoader.hpp"
#include "globalClock.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
	sf::Sprite bg;

	bg.setTexture(RessourceLoader::getTexture("fond.png"));

	Tour tour;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		globalClock::getClock().restart();

        window.clear();
        //window.draw(shape);
		//window.draw(bg);
		//tour.draw(window);
        window.display();
    }

    return 0;
}