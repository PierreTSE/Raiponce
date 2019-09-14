#include <iostream>
#include "ObstaclesManager.h"
#include "globalClock.hpp"
#include "Utilities.hpp"
#include "constantes.hpp"
#include "RessourceLoader.hpp"
#include "filesystem.hpp"

ObstaclesManager::ObstaclesManager() {
    const std::filesystem::path obstaclesPath("rc/sprites/obstacles");
    for (auto& p : std::filesystem::directory_iterator(obstaclesPath)) {
        obstacles_.emplace_back(strip_root(p.path()).u8string());
    }
}

ObstaclesManager& ObstaclesManager::getInstance() {
    static ObstaclesManager obs;
    return obs;
}

void ObstaclesManager::update() {
    timer += globalClock::getClock().frameTime();

    if (timer >= TIME_BETWEEN_NEW_OBSTACLES) {
        size_t n_obs = random(obstacles_.size() - 1), n_obs_copy = n_obs;
        while (!obstacles_[n_obs].isDead()) {
            n_obs = (n_obs + 1) % obstacles_.size();
            if (n_obs == n_obs_copy) {
                timer = TIME_BETWEEN_NEW_OBSTACLES - sf::seconds(0.2);
                return;
            }
        }
        obstacles_[n_obs].reset();
        timer = sf::Time::Zero;
    }
}

void ObstaclesManager::draw(sf::RenderWindow& window) {
    for (auto& o : obstacles_) {
        o.draw(window);
    }
    for (auto it = fireballs_.begin(); it != fireballs_.end();) {
        if (it->isDead()) {
            it = fireballs_.erase(it);
        } else {
            it->draw(window);
            it++;
        }
    }
}

void ObstaclesManager::addFireball(sf::Vector2f const& pos, sf::Vector2f const& origin) {
    Fireball ball(pos.x < WINDOW_SIZE_X / 2);
    ball.setPosition(pos.x + origin.x, pos.y + origin.y);
    fireballs_.push_back(ball);
}
