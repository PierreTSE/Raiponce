#include <SFML/Graphics.hpp>
#include "constantes.hpp"
#include "Tour.h"
#include "Cheveux.h"
#include "RessourceLoader.hpp"
#include "globalClock.hpp"
#include "ObstaclesManager.h"
#include "Chevalier.hpp"
#include <iostream>
#include "Mechant.hpp"
#include <SFML/Audio/Music.hpp>
#include <cmath>
#include "DJ.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Raipaint 2.0");

    // CHARGEMENT ACCUEIL-------------------
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
    text3.setString("Raipaint");
    text3.setPosition(70, 240);




    // CHARGEMENT JEU--------------------

    //background
    sf::Sprite bg;
    bg.setTexture(RessourceLoader::getTexture("sprites/fond.png"));

    //sol
    sf::Sprite sol;
    sol.setTexture(RessourceLoader::getTexture("sprites/sol.png"));
    sf::RectangleShape greenRect({bg.getGlobalBounds().width, bg.getGlobalBounds().height});
    greenRect.setFillColor(sf::Color(0, 128, 64));
    sf::Sprite blood;
    blood.setTexture(RessourceLoader::getTexture("sprites/blood.png"));
    blood.setOrigin(blood.getGlobalBounds().width / 2.f, blood.getGlobalBounds().height / 2.f);

    //score
    sf::Text scoreText;
    scoreText.setFont(RessourceLoader::getFont("font/KingsCross.ttf"));
    scoreText.setCharacterSize(60);
    scoreText.setFillColor(sf::Color(255, 255, 255));
    unsigned long long score        = 0, scoreMax = 0;
    bool               canDoTheFlop = false;

    //sons
    sf::Music music;
    music.openFromFile(RessourceLoader::getPath("audio/music/ClubSeamus (version loopable).ogg"));
    music.setLoop(true);
    DJ::getInstance();

    //entités
    Tour      tour;
    Cheveux   cheveux;
    Chevalier chevalier;
    Mechant   mechantGauche;
    Mechant   mechantDroite(false);
    chevalier.setPosition(cheveux.getX(), 400);

    // preload
    RessourceLoader::getTexture("sprites/fireball.png");


    // ACCUEIL-------------------------------------------------

    bool isaccueil = true;
    window.clear();
    window.draw(accueil);
    window.draw(text1);
    window.draw(text2);
    window.draw(text3);
    window.display();
    while (isaccueil && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed)
                isaccueil = false;
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::sleep(sf::milliseconds(100));
    }

    // JEU-------------------------------------------------------------------------------------------------------------


    //lancement musique
    music.play();

    globalClock::getClock().start();

    while (window.isOpen()) {
        globalClock::getClock().restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        if (chevalier.intersects(sf::Rect(cheveux.getX(), 0.f, cheveux.getWidth(), (float) WINDOW_SIZE_Y))) {
            score    = std::round(score + globalClock::getClock().frameTime().asMilliseconds() * CLIMB_SPEED_COEFF);
            scoreMax = std::max(scoreMax, score);
            tour.update(true);
            cheveux.update(true);
            if (!canDoTheFlop && score > 2000) canDoTheFlop = true;
        } else {
            constexpr float FALL_LOST_POINTS_COEFF = 1.25;
            score = (unsigned long long) std::max(
                    score - globalClock::getClock().frameTime().asMilliseconds() * FALL_SPEED_COEFF * FALL_LOST_POINTS_COEFF, 0.f);
            if (score > 0) {
                tour.update(false);
                cheveux.update(false);
            } else if (score == 0 && canDoTheFlop && !CANNOT_DIE) {
                canDoTheFlop = false;
                chevalier.kill();
            }
        }
        scoreText.setString(std::to_string(static_cast<int>(score)) + " m");
        const double textsize = 20 * std::to_string(score).length();
        scoreText.setPosition({(WINDOW_SIZE_X - static_cast<float>(textsize)) / 2, 5.f});


        // début draw----------------------
        window.clear();

        window.draw(bg);
        tour.draw(window);
        cheveux.draw(window);

        constexpr float solThreshold = 2000;
        if (score < solThreshold) {
            sol.setPosition(0, WINDOW_SIZE_Y - (((solThreshold - (float) score) / solThreshold) * WINDOW_SIZE_Y / 3.5));
            greenRect.setPosition(0, sol.getPosition().y + sol.getGlobalBounds().height);
            window.draw(sol);
            window.draw(greenRect);
        }

        chevalier.draw(window, cheveux);

        ObstaclesManager::getInstance().update();
        ObstaclesManager::getInstance().draw(window);

        mechantDroite.draw(window);
        mechantGauche.draw(window);

        window.draw(scoreText);
        // fin draw----------------------

        //debug : position cheveux
        if (DEBUG) {
            sf::RectangleShape line({5, WINDOW_SIZE_Y});
            line.setFillColor(sf::Color::Red);
            if (chevalier.intersects(sf::Rect(cheveux.getX(), 0.f, cheveux.getWidth(), (float) WINDOW_SIZE_Y))) {
                line.setFillColor(sf::Color::Green);
            } else {
                line.setFillColor(sf::Color::Red);
            }
            line.setPosition(cheveux.getX(), 0);
            window.draw(line);
            line.setPosition(cheveux.getX() + cheveux.getWidth(), 0);
            window.draw(line);
        }


        if (chevalier.isDead()) {
            // animation de mort
            blood.setPosition(-1000, -1000);
            bool           sprotch               = false;
            sf::Time       timerBleed            = sf::Time::Zero;
            const sf::Time bloodFloodingTime     = sf::seconds(1.5);
            const auto     chevalierStartFallY   = chevalier.getHitboxPosition().y;
            const auto     chevalierDeathY       = chevalier.deathYpos;
            const auto     chevalierFallDistance = chevalierDeathY - chevalierStartFallY;
            constexpr auto solAimPosY            = WINDOW_SIZE_Y - WINDOW_SIZE_Y / 3.5f;
            const auto     solStartPosY          = std::clamp(sol.getPosition().y, solAimPosY, (float) WINDOW_SIZE_Y);
            const auto     solDistance           = solStartPosY - solAimPosY;

            bool animateDeath = true;
            while (animateDeath) {
                globalClock::getClock().restart();

                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        return EXIT_SUCCESS;
                    }
                }

                window.clear();
                window.draw(bg);

                if (chevalier.getHitboxPosition().y < chevalierDeathY) {
                    sol.setPosition(0,
                                    solAimPosY +
                                    ((chevalierFallDistance - (chevalier.getHitboxPosition().y - chevalierStartFallY)) / chevalierFallDistance) *
                                    solDistance);
                    greenRect.setPosition(0, sol.getPosition().y + sol.getGlobalBounds().height);

                    tour.update(false);
                    cheveux.update(false);
                } else {
                    if (!sprotch) {
                        DJ::getInstance().playSound("sprotch");
                        sprotch = true;
                    }

                    timerBleed += globalClock::getClock().frameTime();
                    if (timerBleed >= bloodFloodingTime)
                        animateDeath = false;
                    else {
                        blood.setPosition(chevalier.getHitboxPosition());
                        const auto scale = 1.7 * (1 - ((bloodFloodingTime - timerBleed) / bloodFloodingTime));
                        blood.setScale(scale, scale);
                    }
                }
                tour.draw(window);
                cheveux.draw(window);
                window.draw(sol);
                window.draw(greenRect);
                window.draw(blood);
                chevalier.draw(window, cheveux);

                ObstaclesManager::getInstance().draw(window);
                mechantDroite.draw(window, false);
                mechantGauche.draw(window, false);
                window.display();


                sf::sleep(sf::milliseconds(10));
            }

            // écran de fin
            sf::Texture        prevWindow;
            sf::Sprite         spr;
            sf::RectangleShape rect;
            sf::Text           text;

            text.setFont(RessourceLoader::getFont("font/KingsCross.ttf"));
            text.setFillColor(sf::Color(255, 255, 255));


            prevWindow.create(1280, 720);
            prevWindow.update(window);

            rect.setSize({1280, 720});
            rect.setFillColor({0, 0, 0, 0});

            spr.setTexture(prevWindow);

            bool displayRestartScreen = true;
            while (displayRestartScreen) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        displayRestartScreen = false;
                    }

                    if (event.type == sf::Event::KeyPressed)
                        if (event.key.code == sf::Keyboard::Key::R) {
                            //reset
                            canDoTheFlop = false;
                            score        = scoreMax = 0;
                            chevalier.revive(cheveux.getX(), 400);
                            globalClock::getClock().restart();
                            displayRestartScreen = false;
                        }

                }

                sf::Color c = rect.getFillColor();
                if (c.a < 200) {
                    c.a += 800 * globalClock::getClock().frameTime().asSeconds();
                    rect.setFillColor(c);
                } else if (c.a != 210) {
                    c.a = 210;
                    rect.setFillColor(c);
                }

                window.clear();
                window.draw(spr);
                window.draw(rect);

                scoreText.setString(std::to_string(scoreMax) + " m");
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

                sf::sleep(sf::milliseconds(10));
            }
        }

        window.display();

        sf::sleep(sf::milliseconds(10));
    }

    return 0;
}

