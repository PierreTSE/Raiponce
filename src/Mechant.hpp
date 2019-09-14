#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Utilities.hpp"

class Mechant {
public:
    explicit Mechant(bool isOnLeft = true);

    void draw(sf::RenderWindow& window, bool canFireBalls = true);

private:
    sf::Sprite sprite_;

    float vit_ = 200;

    const int COOLDOWN_BOTTOM = 2000, COOLDOWN_TOP = 6000;
    sf::Time  COOLDOWN        = sf::milliseconds(random(COOLDOWN_BOTTOM, COOLDOWN_TOP));
    sf::Time  cooldown_       = sf::Time::Zero;

    bool isGoingDown = true;
};

