#ifndef CHEVALIER_HPP
#define CHEVALIER_HPP
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

#include "Cheveux.h"
#include <SFML/Audio/Sound.hpp>

enum Son{SURPRISE, BOING};

class Chevalier
{
public:
    Chevalier();
	void draw(sf::RenderWindow & window, Cheveux &ch);
	void setPosition(int x, int y);
	bool isDead();
	void revive(float x, float y);

private:
    //son
    std::vector<sf::Sound> boings_;
    std::vector<sf::Sound> surprises_;
	bool isPlaying = false;

	void playSoundOnBump();

    //graphiques
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
