#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>

class Obstacle {
	private:
		sf::RectangleShape spr_;
		bool dead = false;
	public:
		Obstacle(float x, float y);
		void draw(sf::RenderWindow &window);
		bool isDead();

};


#endif // !OBSTACLE_H
