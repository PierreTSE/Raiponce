#include "Chevalier.hpp"
#include "RessourceLoader.hpp"
#include "globalClock.hpp"
#include "Utilities.hpp"
#include "ObstaclesManager.h"
#include "constantes.hpp"
#include "DJ.hpp"

#include <iostream>

Chevalier::Chevalier() {
    sprites_.emplace_back();
    sprites_.back().setTexture(RessourceLoader::getTexture("sprites/chevalier_haut.png"));
    sprites_.emplace_back();
    sprites_.back().setTexture(RessourceLoader::getTexture("sprites/chevalier_milieu.png"));
    sprites_.emplace_back();
    sprites_.back().setTexture(RessourceLoader::getTexture("sprites/chevalier_bas.png"));

    const float hitboxWidth = 90, hitboxHeight = 180;
    hitbox_.setSize({hitboxWidth, hitboxHeight});
    hitbox_.setOrigin(hitboxWidth / 2.f, hitboxHeight / 2.f);

    deathYpos = WINDOW_SIZE_Y - 120;

    for (auto& s : sprites_)
        s.setOrigin({s.getGlobalBounds().width / 2.f, s.getGlobalBounds().height / 2.f});

    //son
    boings_.emplace_back();
    boings_.back().setBuffer(RessourceLoader::getSoundBuffer("audio/bump/1.wav"));
    boings_.emplace_back();
    boings_.back().setBuffer(RessourceLoader::getSoundBuffer("audio/bump/2.wav"));
    boings_.emplace_back();
    boings_.back().setBuffer(RessourceLoader::getSoundBuffer("audio/bump/3.wav"));
    boings_.emplace_back();
    boings_.back().setBuffer(RessourceLoader::getSoundBuffer("audio/bump/4.wav"));

    surprises_.emplace_back();
    surprises_.back().setBuffer(RessourceLoader::getSoundBuffer("audio/surprise/1.wav"));
    surprises_.emplace_back();
    surprises_.back().setBuffer(RessourceLoader::getSoundBuffer("audio/surprise/2.wav"));
    surprises_.emplace_back();
    surprises_.back().setBuffer(RessourceLoader::getSoundBuffer("audio/victoire/victoire1.wav"));
    surprises_.emplace_back();
    surprises_.back().setBuffer(RessourceLoader::getSoundBuffer("audio/victoire/victoire2.wav"));
    surprises_.emplace_back();
    surprises_.back().setBuffer(RessourceLoader::getSoundBuffer("audio/victoire/victoire3.wav"));
    surprises_.emplace_back();
    surprises_.back().setBuffer(RessourceLoader::getSoundBuffer("audio/victoire/victoire4.wav"));

    ouchSound.setBuffer(RessourceLoader::getSoundBuffer("audio/surprise/ouch.wav"));
}

void Chevalier::draw(sf::RenderWindow& window, Cheveux& ch) {
    sf::Vector2f sp = {0, 0};

    // computes movement
    if (dead) {
        if (hitbox_.getPosition().y <= deathYpos) {
            DJ::getInstance().playSound("cri");
            sp.y = 1;
            for (auto& s : sprites_)
                s.rotate(globalClock::getClock().frameTime().asSeconds() * 180);
        }
    } else {
        animationTime_ += globalClock::getClock().frameTime();
        tempsImmune_ += globalClock::getClock().frameTime();


        if (tempsImmune_ > TEMPS_IMMUNE_MAX) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                sp.y = -1;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                sp.y = 1;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                sp.x = -1;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                sp.x = 1;

            for (auto& s : sprites_)
                s.setRotation(0);
        } else {
            for (auto& s : sprites_)
                s.rotate(globalClock::getClock().frameTime().asSeconds() * 1000);

            sp = vit_;

            if (vit_.x > 0) {
                vit_.x -= globalClock::getClock().frameTime().asSeconds() * 1.5;
                if (vit_.x < 0) {
                    tempsImmune_ = sf::seconds(100);
                    vit_.x = 0;
                }

            }
            if (vit_.x < 0) {
                vit_.x += globalClock::getClock().frameTime().asSeconds() * 1.5;
                if (vit_.x > 0) {
                    tempsImmune_ = sf::seconds(100);
                    vit_.x = 0;
                }
            }

            if (vit_.y > 0) {
                vit_.y -= globalClock::getClock().frameTime().asSeconds() * 1.5;
                if (vit_.y < 0) {
                    tempsImmune_ = sf::seconds(100);
                    vit_.y = 0;
                }
            }
            if (vit_.y < 0) {
                vit_.y += globalClock::getClock().frameTime().asSeconds() * 1.5;
                if (vit_.y > 0) {
                    tempsImmune_ = sf::seconds(100);
                    vit_.y = 0;
                }
            }
        }

        if (sprites_.front().getPosition().x + sprites_.front().getGlobalBounds().width / 2 < ch.getX() ||
            sprites_.front().getPosition().x - sprites_.front().getGlobalBounds().width / 2 > ch.getX() + ch.getWidth()) {
            tempsVide_ += globalClock::getClock().frameTime();

            if (tempsVide_ > TEMPS_MAX_DANS_VIDE && !CANNOT_DIE)
                dead = true;
        } else {
            if (tempsImmune_ > sf::seconds(0.5f) && tempsVide_ != sf::Time::Zero)
                tempsImmune_ = sf::seconds(100);

            tempsVide_ = sf::Time::Zero;

            if (animationTime_ > TIME_BETWEEN_FRAMES) {
                animationTime_ = sf::Time::Zero;
                currentFrame_++;
                if (currentFrame_ >= sprites_.size())
                    currentFrame_ = 0;
            }
        }


        if (tempsImmune_ > sf::seconds(1)) {
            for (auto const& o : ObstaclesManager::getInstance().getObstacles()) {
                constexpr float modifier = 50;
                sf::Rect        hitboxObst(o.getBox().left + modifier, o.getBox().top + modifier, o.getBox().width - modifier * 2,
                                           o.getBox().height - modifier * 2);
                if (DEBUG) {
                    sf::RectangleShape r({hitboxObst.width, hitboxObst.height});
                    // r.setOrigin(r.getGlobalBounds().width / 2., r.getGlobalBounds().height / 2.);
                    r.setPosition(hitboxObst.left, hitboxObst.top);
                    window.draw(r);
                }

                if (hitbox_.getGlobalBounds().intersects(hitboxObst)) {
                    tempsImmune_ = sf::Time::Zero;
                    vit_         = sprites_.back().getPosition() - o.getPosition();
                    vit_         = normalize(vit_);
                    playSoundOnBump();
                }
            }
            for (auto const& f : ObstaclesManager::getInstance().getFireballs()) {
                if (hitbox_.getGlobalBounds().intersects(f.getBox())) {
                    tempsImmune_ = sf::Time::Zero;
                    vit_         = sprites_.back().getPosition() - f.getPosition();
                    vit_         = normalize(vit_);
                    playSoundOnBurn();
                }
            }
        }
        if (sprites_.back().getPosition().x - sprites_.back().getGlobalBounds().width / 2 < 0) {
            tempsImmune_ = sf::Time::Zero;
            vit_.x = 2;
            playSoundOnBump();
        }
        if (sprites_.back().getPosition().x + sprites_.back().getGlobalBounds().width / 2 > WINDOW_SIZE_X) {
            tempsImmune_ = sf::Time::Zero;
            vit_.x = -2;
            playSoundOnBump();
        }
        if (sprites_.back().getPosition().y - sprites_.back().getGlobalBounds().height / 2 < 0) {
            tempsImmune_ = sf::Time::Zero;
            vit_.y = 0.5;
            playSoundOnBump();
        }
        if (sprites_.back().getPosition().y + sprites_.back().getGlobalBounds().height / 2 > WINDOW_SIZE_Y) {
            tempsImmune_ = sf::Time::Zero;
            vit_.y = -0.5;
            playSoundOnBump();
        }
    }

    // moves
    if (sp != sf::Vector2f{0, 0}) {
        sp = normalize(sp);

        sf::Vector2f delta;
        delta.x = globalClock::getClock().frameTime().asSeconds() * speed * sp.x;
        delta.y = globalClock::getClock().frameTime().asSeconds() * speed * sp.y;

        for (auto& s : sprites_)
            s.move(delta);

        hitbox_.move(delta);
    }

    window.draw(sprites_[currentFrame_]);

    if (DEBUG)
        window.draw(hitbox_);
}

void Chevalier::setPosition(int x, int y) {
    for (auto& s : sprites_)
        s.setPosition(x, y);
    hitbox_.setPosition(x, y);
}

bool Chevalier::isDead() {
    return dead;
}

void Chevalier::revive(float x, float y) {
    setPosition(x, y);
    dead = false;

    tempsVide_   = sf::Time::Zero;
    tempsImmune_ = sf::seconds(1000);

    vit_ = {0, 0};

    for (auto& s : sprites_)
        s.setRotation(0);
}

void Chevalier::playSoundOnBump() {
    bool isBoingPlaying = false;
    for (auto& sound : boings_)
        if (sound.getStatus() == sf::Sound::Status::Playing) {
            isBoingPlaying = true;
            break;
        }

    bool isSurprisePlaying = false;
    for (auto& sound : surprises_)
        if (sound.getStatus() == sf::Sound::Status::Playing) {
            isSurprisePlaying = true;
            break;
        }


    if (!isBoingPlaying) {
        const int n_boing = random(boings_.size() - 1);
        boings_[n_boing].play();
    }

    if (!isSurprisePlaying) {
        const int probaSurprise = 60;
        if (random(1, 100) <= probaSurprise) {
            const int n_surp = random(surprises_.size() - 1);
            surprises_[n_surp].play();
        }
    }
}

void Chevalier::playSoundOnBurn() {
    if (ouchSound.getStatus() != sf::Sound::Status::Playing)
        ouchSound.play();
}

void Chevalier::kill() {
    dead = true;
}
