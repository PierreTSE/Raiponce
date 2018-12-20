#ifndef CHEVEUX_H
#define CHEVEUX_H

#include <SFML/Graphics.hpp>

class Cheveux {
	private:
		sf::Sprite cheveux1, cheveux2;
		float currentPosition = 0, x = 0;
		int sens = 1;
		sf::Time timer, nextShift;
	public:
		Cheveux();
		void draw(sf::RenderWindow &window);

};


#endif // !CHEVEUX_H
