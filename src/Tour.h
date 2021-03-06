#ifndef TOUR_H
#define TOUR_H

#include <SFML/Graphics.hpp>

class Tour {
private:
    sf::Sprite tour1, tour2, tour3;
    float      currentPosition = 0;
public:
    Tour();

    void update(bool climbing);
    void draw(sf::RenderWindow& window);

};


#endif