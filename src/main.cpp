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
#include <SFML/Audio/Music.hpp>


int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Rape paint");

	// ACCUEIL-------------------
    sf::Sprite accueil;
    accueil.setTexture(RessourceLoader::getTexture("sprites/accueil.png"));

    sf::Text text1;
    text1.setFont(RessourceLoader::getFont("font/Precious.ttf"));
    text1.setCharacterSize(48);
    text1.setString("Sauvez la");
    text1.setPosition(70, 100);

    sf::Text text2;
    text2.setFont(RessourceLoader::getFont("font/Precious.ttf"));
    text2.setCharacterSize(48);
    text2.setString("Princesse");
    text2.setPosition(120, 160);

    sf::Text text3;
    text3.setFont(RessourceLoader::getFont("font/Precious.ttf"));
    text3.setCharacterSize(90);
    text3.setString("RapePaint");
    text3.setPosition(70, 240);
    
    
   


    // JEU--------------------

    //background
	sf::Sprite bg;
	bg.setTexture(RessourceLoader::getTexture("sprites/fond.png"));

    //score
    sf::Text scoreText;
    scoreText.setFont(RessourceLoader::getFont("font/KingsCross.ttf"));
    scoreText.setCharacterSize(60);
    scoreText.setFillColor(sf::Color(255, 255 , 255));
    double score = 0;

    //sons
    sf::Music music;
    music.openFromFile(RessourceLoader::getPath("audio/music/ClubSeamus.ogg"));
    music.setLoop(true);
    

    //entités
	Tour tour;
	Cheveux cheveux;
	Chevalier chevalier;
    Mechant mechantGauche;
    Mechant mechantDroite(false);
	chevalier.setPosition(cheveux.getX(), 400);





    //ACCUEIL

    bool isaccueil = true;
    while(isaccueil)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
                isaccueil = false;
        }

        window.clear();
        window.draw(accueil);
        window.draw(text1); 
        window.draw(text2);
        window.draw(text3);
        window.display();
    }

    //JEU


    //lancement musique
    music.play();

    globalClock::getClock().restart();

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
        scoreText.setString(std::to_string(static_cast<int>(score)) + " m");
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


		if (chevalier.isDead())
		{
			sf::Texture prevWindow;
			sf::Sprite spr;
			sf::RectangleShape rect;
			sf::Text text;

			text.setFont(RessourceLoader::getFont("font/KingsCross.ttf"));
			text.setFillColor(sf::Color(255, 255, 255));

			prevWindow.create(1280, 720);
			prevWindow.update(window);

			rect.setSize({ 1280, 720 });
			rect.setFillColor({ 0,0,0,0 });

			spr.setTexture(prevWindow);

			bool continuer = true;

			while (continuer)
			{
				sf::Event event;
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
					{
						window.close();
						continuer = false;
					}

					if (event.type == sf::Event::KeyPressed)
						if (event.key.code == sf::Keyboard::Key::R)
						{
							score = 0;
							continuer = false;
							chevalier.revive(cheveux.getX(), 400);
							globalClock::getClock().restart();
						}

				}

				sf::Color c = rect.getFillColor();
				if (c.a < 200)
				{
					c.a += 1000 * globalClock::getClock().frameTime().asSeconds();
					rect.setFillColor(c);
				}
				else if (c.a != 210)
				{
					c.a = 210;
					rect.setFillColor(c);
				}

				window.clear();
				window.draw(spr);
				window.draw(rect);

				window.draw(scoreText);

				text.setCharacterSize(160);
				text.setString("Game Over");
				text.setPosition((WINDOW_SIZE_X - text.getGlobalBounds().width) / 2, 200);
				window.draw(text);

				text.setCharacterSize(80);
				text.setString("Appuyez sur R pour recommencer");
				text.setPosition((WINDOW_SIZE_X - text.getGlobalBounds().width) / 2, 600);
				window.draw(text);

				window.display();
			}
		}

        window.display();
    }

    return 0;
}
