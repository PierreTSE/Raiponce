#include "Chevalier.hpp"
#include "RessourceLoader.hpp"
#include "globalClock.hpp"
#include "Utilities.hpp"

Chevalier::Chevalier()
{
    /*sprites_.emplace_back();
    sprites_.back().setTexture(RessourceLoader::getTexture("chevalier_haut"));
    sprites_.emplace_back();
    sprites_.back().setTexture(RessourceLoader::getTexture("chevalier_milieu"));
    sprites_.emplace_back();
    sprites_.back().setTexture(RessourceLoader::getTexture("chevalier_bas"));*/

	rect_.setSize({ 270, 270 });
	rect_.setPosition(0, 0);

	
}

void Chevalier::draw(sf::RenderWindow & window)
{
	sf::Vector2f sp = { 0,0 };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		sp.y = -1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		sp.y = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		sp.x = -1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		sp.x = 1;
	
	sp = normalize(sp);

	rect_.move(globalClock::getClock().frameTime().asSeconds() * speed * sp.x, globalClock::getClock().frameTime().asSeconds() * speed * sp.y);

	window.draw(rect_);
}
