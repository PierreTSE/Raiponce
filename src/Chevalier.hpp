#ifndef CHEVALIER_HPP
#define CHEVALIER_HPP
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

#include "Cheveux.h"

class Chevalier
{
public:
    Chevalier();
	void draw(sf::RenderWindow & window, Cheveux &ch);
	void setPosition(int x, int y);

private:
    std::vector<sf::Sprite> sprites_;
	sf::RectangleShape hitbox_;

	sf::Time animationTime_, tempsVide_, tempsImune_;;
    sf::Clock clock_;
	sf::Vector2f vit_;

	float speed = 700;
	int currentFrame_ = 0;
	bool dead = false;
};
#endif // CHEVALIER_HPP
