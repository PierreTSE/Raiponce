#ifndef RAIPAINT_V2_FIREBALL_HPP
#define RAIPAINT_V2_FIREBALL_HPP

#include <SFML/Graphics.hpp>
#include "Utilities.hpp"

class ObstacleManager;

class Fireball {
public:
    explicit Fireball(bool comeFromLeft = true);

    void draw(sf::RenderWindow& window);

    void setPosition(float x, float y) { sprite_.setPosition(x, y); }

    sf::FloatRect getBox() const { return sprite_.getGlobalBounds(); }

    sf::Vector2f getPosition() const { return sprite_.getPosition(); }

    sf::Vector2f getSize() const { return {sprite_.getGlobalBounds().width, sprite_.getGlobalBounds().height}; }

    bool isDead() const;

private:
    sf::Sprite sprite_;

    bool dead_ = false;

    bool comeFromLeft_;

    const float speed_ = random(200, 500);
};


#endif //RAIPAINT_V2_FIREBALL_HPP
