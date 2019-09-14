#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>

class Obstacle {
public:
    explicit Obstacle(const std::string& texturePath);

    void draw(sf::RenderWindow& window);

    bool isDead() const { return dead; }

    void setPosition(sf::Vector2f pos) { sprite_.setPosition(pos); }

    sf::Vector2f getPosition() const { return sprite_.getPosition(); }

    sf::Vector2f getSize() const { return {sprite_.getGlobalBounds().width, sprite_.getGlobalBounds().height}; }

    sf::FloatRect getBox() const { return sprite_.getGlobalBounds(); }

    void reset();

private:
    sf::Sprite sprite_;
    bool       dead = true;

    float speed_;
    float rotSpeed_;
};


#endif // !OBSTACLE_H
