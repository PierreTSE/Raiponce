#ifndef CHEVEUX_H
#define CHEVEUX_H

#include <SFML/Graphics.hpp>

class Cheveux {
	private:
		sf::Sprite cheveux1, cheveux2;
		float currentPosition = 0, x = 0;
		int sens = 1;
		float width;
		sf::Time timer, nextShift;
	public:
		Cheveux();
		float getWidth() {return width;};
		float getX() { return x; }
		void draw(sf::RenderWindow &window);

};


#endif // !CHEVEUX_H
