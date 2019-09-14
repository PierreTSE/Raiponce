#ifndef CHEVALIER_HPP
#define CHEVALIER_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

#include "constantes.hpp"
#include "Cheveux.h"
#include <SFML/Audio/Sound.hpp>

enum Son {
    SURPRISE, BOING
};

class Chevalier {
public:
    Chevalier();
    void draw(sf::RenderWindow& window, Cheveux& ch);
    void setPosition(int x, int y);
    bool isDead();
    void kill();
    void revive(float x, float y);

    sf::Vector2f getHitboxPosition() const { return hitbox_.getPosition(); }

    template<typename T>
    bool intersects(sf::Rect<T> const& r) const {
        const sf::Rect hitboxChevalier = sf::Rect(hitbox_.getPosition() - hitbox_.getOrigin(), hitbox_.getSize());
        return hitboxChevalier.intersects(r);
    }

    float deathYpos;

private:
    //son
    std::vector<sf::Sound> boings_;
    std::vector<sf::Sound> surprises_;
    sf::Sound              ouchSound;
    bool                   isPlaying = false;

    void playSoundOnBump();
    void playSoundOnBurn();

    //graphiques
    std::vector<sf::Sprite> sprites_;
    sf::RectangleShape      hitbox_;


    const sf::Time TEMPS_MAX_DANS_VIDE = sf::seconds(3),
                   TEMPS_IMMUNE_MAX    = sf::seconds(1),
                   TIME_BETWEEN_FRAMES = sf::milliseconds(50);

    sf::Time animationTime_,
             tempsVide_                = sf::Time::Zero,
             tempsImmune_              = sf::seconds(10000);

    sf::Clock    clock_;
    sf::Vector2f vit_                  = {0, 0};

    float  speed         = 700;
    size_t currentFrame_ = 0;
    bool   dead          = false;
};

#endif // CHEVALIER_HPP
