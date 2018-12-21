#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Mechant
{
public:
    Mechant(bool isOnLeft = true);

    void draw(sf::RenderWindow& window);

private:
    sf::Sprite sprite_;

    float vit_ = 200;
    sf::Time cooldown_ = sf::milliseconds(4000);
    bool isGoingDown = true;
};

