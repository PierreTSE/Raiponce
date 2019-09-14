#ifndef OBSTACLE_MANAGER_H
#define OBSTACLE_MANAGER_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "Obstacle.h"
#include "Fireball.hpp"
#include <list>

class ObstaclesManager {
public:
    ObstaclesManager();
    static ObstaclesManager& getInstance();
    void update();
    void draw(sf::RenderWindow& window);

    std::vector<Obstacle> const& getObstacles() { return obstacles_; };

    std::list<Fireball> const& getFireballs() const { return fireballs_; }

    void addFireball(sf::Vector2f const& pos, sf::Vector2f const& origin);

private:
    std::vector<Obstacle> obstacles_;
    std::list<Fireball>   fireballs_;

    const sf::Time TIME_BETWEEN_NEW_OBSTACLES = sf::seconds((60. / 112) * 2); // 1 obstacle every two beats of the 112bpm song

    sf::Time timer = TIME_BETWEEN_NEW_OBSTACLES;
};

#endif // !OBSTACLE_H
