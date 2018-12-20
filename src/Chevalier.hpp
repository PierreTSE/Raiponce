#ifndef CHEVALIER_HPP
#define CHEVALIER_HPP
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

class Chevalier
{
public:
    Chevalier();
	void draw(sf::RenderWindow & window);

private:
    std::vector<sf::Sprite> sprites_;
	sf::RectangleShape rect_;

    sf::Time animationTime_;
    sf::Clock clock_;

	float speed = 700;
};
#endif // CHEVALIER_HPP
