#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>

class Obstacle
{
public:
    Obstacle(const std::string& texturePath);

    void draw(sf::RenderWindow& window);

    bool         isDead() const { return dead; }
    void         setPosition(sf::Vector2f pos) { sprite_.setPosition(pos); }
    sf::Vector2f getPosition() const { return sprite_.getPosition(); }

    void reset();

private:
    sf::Sprite sprite_;
    bool       dead = false;

    float speed_;
    float rotSpeed_;
};


#endif // !OBSTACLE_H
