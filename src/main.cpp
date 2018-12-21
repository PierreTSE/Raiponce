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
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Rape paint");
    
	sf::Sprite bg;
	bg.setTexture(RessourceLoader::getTexture("fond.png"));

    sf::Text scoreText;
    scoreText.setFont(RessourceLoader::getFont("font/KingsCross.ttf"));
    scoreText.setCharacterSize(60);
    scoreText.setFillColor(sf::Color(255, 255 , 255));

    double score = 0;

	Tour tour;
	Cheveux cheveux;
	Chevalier chevalier;
    Mechant mechantGauche;
    Mechant mechantDroite(false);

	chevalier.setPosition(cheveux.getX(), 400);

    while (window.isOpen())
    {
        globalClock::getClock().restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        score += globalClock::getClock().frameTime().asMilliseconds() * 7;
        scoreText.setString(std::to_string(static_cast<int>(score)));
        const double textsize = 20 * std::to_string(score).length();
        scoreText.setPosition({(WINDOW_SIZE_X - static_cast<float>(textsize))/2, 5.f});

        window.clear();
		window.draw(bg);
		tour.draw(window);
		cheveux.draw(window);
        chevalier.draw(window, cheveux);
        mechantDroite.draw(window);
        mechantGauche.draw(window);
		ObstaclesManager::getInstance().gestion(window);

        window.draw(scoreText);
        window.display();
    }

    return 0;
}
