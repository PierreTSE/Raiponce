#include <SFML/Graphics.hpp>
#include "constantes.hpp"
#include "Tour.h"
#include "Cheveux.h"
#include "RessourceLoader.hpp"
#include "globalClock.hpp"
#include "ObstaclesManager.h"
#include "Chevalier.hpp"
#include <iostream>
#include <filesystem>
#include "Mechant.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
	sf::Sprite bg;

	bg.setTexture(RessourceLoader::getTexture("fond.png"));

	Tour tour;
	Cheveux cheveux;
	Chevalier chevalier;
    Mechant mechantGauche;
    Mechant mechantDroite(false);

    while (window.isOpen())
    {
        globalClock::getClock().restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		

        window.clear();
        //window.draw(shape);
		window.draw(bg);
		tour.draw(window);
		cheveux.draw(window);
        chevalier.draw(window);
        mechantDroite.draw(window);
        mechantGauche.draw(window);
		ObstaclesManager::getInstance().gestion(window);		
        window.display();
    }

    return 0;
}
