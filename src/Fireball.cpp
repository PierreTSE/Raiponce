#include "constantes.hpp"
#include "Fireball.hpp"
#include "RessourceLoader.hpp"
#include "globalClock.hpp"

Fireball::Fireball(bool comeFromLeft) : comeFromLeft_{comeFromLeft} {
    sprite_.setTexture(RessourceLoader::getTexture("sprites/fireball.png"));
    sprite_.setOrigin(sprite_.getGlobalBounds().width / 2, sprite_.getGlobalBounds().height / 2);
    if (comeFromLeft) {
        sprite_.scale(-1, 1);
    }
}

void Fireball::draw(sf::RenderWindow& window) {
    if (dead_) return;
    if (comeFromLeft_) {
        if (sprite_.getPosition().x + sprite_.getGlobalBounds().width / 2 < WINDOW_SIZE_X) {
            sprite_.move(speed_ * globalClock::getClock().frameTime().asSeconds(), 0);
        } else {
            dead_ = true;
        }
    } else if (!comeFromLeft_) {
        if (sprite_.getPosition().x - sprite_.getGlobalBounds().width / 2 > 0) {
            sprite_.move(-speed_ * globalClock::getClock().frameTime().asSeconds(), 0);
        } else {
            dead_ = true;
        }
    }
    window.draw(sprite_);
}

bool Fireball::isDead() const {
    return dead_;
}
