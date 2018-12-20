#include "Character.h"
#include<iostream>
#include <cmath>
#include "constantes.hpp"
#include "RessourceLoader.hpp"
#include "globalClock.hpp"


Player::Player() :
    sprite(IDLE_DOWN,
           AnimatedSprite(1,
                          sf::milliseconds(250),
                          RessourceLoader::getTexture("sprites/walking_down.png"),
                          sf::IntRect{340, 0, 340, 600}))
{
    sprite.setup(IDLE_UP,
                 AnimatedSprite(1,
                                sf::milliseconds(250),
                                RessourceLoader::getTexture("sprites/walking_up.png"),
                                sf::IntRect{340, 0, 340, 600}));
    sprite.setup(IDLE_LEFT,
                 AnimatedSprite(1,
                                sf::milliseconds(250),
                                RessourceLoader::getTexture("sprites/walking_left.png"),
                                sf::IntRect{340, 0, 340, 600}));
    sprite.setup(IDLE_RIGHT,
                 AnimatedSprite(1,
                                sf::milliseconds(250),
                                RessourceLoader::getTexture("sprites/walking_right.png"),
                                sf::IntRect{340, 0, 340, 600}));

    sprite.setup(WALKING_DOWN,
                 AnimatedSprite(4,
                                sf::milliseconds(250),
                                RessourceLoader::getTexture("sprites/walking_down.png"),
                                sf::IntRect{0, 0, 340, 600}));
    sprite.setup(WALKING_UP,
                 AnimatedSprite(4,
                                sf::milliseconds(250),
                                RessourceLoader::getTexture("sprites/walking_up.png"),
                                sf::IntRect{0, 0, 340, 600}));
    sprite.setup(WALKING_LEFT,
                 AnimatedSprite(4,
                                sf::milliseconds(250),
                                RessourceLoader::getTexture("sprites/walking_left.png"),
                                sf::IntRect{0, 0, 340, 600}));
    sprite.setup(WALKING_RIGHT,
                 AnimatedSprite(4,
                                sf::milliseconds(250),
                                RessourceLoader::getTexture("sprites/walking_right.png"),
                                sf::IntRect{0, 0, 340, 600}));


    sprite.setup(RINGING_DOWN,
                 AnimatedSprite(2,
                                sf::milliseconds(250),
                                RessourceLoader::getTexture("sprites/ringing_down.png"),
                                sf::IntRect{0, 0, 340, 600}));
    sprite.setup(RINGING_UP,
                 AnimatedSprite(2,
                                sf::milliseconds(250),
                                RessourceLoader::getTexture("sprites/ringing_up.png"),
                                sf::IntRect{0, 0, 340, 600}));
    sprite.setup(RINGING_LEFT,
                 AnimatedSprite(2,
                                sf::milliseconds(250),
                                RessourceLoader::getTexture("sprites/ringing_left.png"),
                                sf::IntRect{0, 0, 340, 600}));
    sprite.setup(RINGING_RIGHT,
                 AnimatedSprite(2,
                                sf::milliseconds(250),
                                RessourceLoader::getTexture("sprites/ringing_right.png"),
                                sf::IntRect{0, 0, 340, 600}));


    sprite.setScale(SPRITE_RATIO, SPRITE_RATIO);

    hitbox_.width  = 3 * PIXEL_SIZE;
    hitbox_.height = 2.5 * PIXEL_SIZE;
    hitbox_.left   = (TARGET_SPRITE_WIDTH - hitbox_.width) / 2;
    hitbox_.top    = TARGET_SPRITE_HEIGHT - hitbox_.height;

    orientation = Orientation::DOWN;
    animation   = Animation::IDLE;
}

void Player::movement(const sf::Time& elapsedTime, std::vector<std::vector<bool>> const& map)
{
    if(!canMove)
        return;

    sf::Vector2f nextPos = position_;

    Animation prev = animation;


    float px = sf::Joystick::isConnected(0) && sf::Joystick::hasAxis(0, sf::Joystick::Axis::X) ?
                   sf::Joystick::getAxisPosition(0, sf::Joystick::X) :
                   0;
    float py = sf::Joystick::isConnected(0) && sf::Joystick::hasAxis(0, sf::Joystick::Axis::Y) ?
                   sf::Joystick::getAxisPosition(0, sf::Joystick::Y) :
                   0;


    if(sf::Keyboard::isKeyPressed(
                                  sf::Keyboard::Right) || px > 50)
    {
        setOrientation(Orientation::RIGHT);
        setAnimation(Animation::WALKING);
        nextPos.x += speed_ * elapsedTime.asSeconds();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || px < -50)
    {
        setOrientation(Orientation::LEFT);
        setAnimation(Animation::WALKING);
        nextPos.x -= speed_ * elapsedTime.asSeconds();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || py < -50)
    {
        setOrientation(Orientation::UP);
        setAnimation(Animation::WALKING);
        nextPos.y -= speed_ * elapsedTime.asSeconds();
    }
    else if(sf::Keyboard::isKeyPressed(
                                       sf::Keyboard::Down) || py > 50)
    {
        setOrientation(Orientation::DOWN);
        setAnimation(Animation::WALKING);
        nextPos.y += speed_ * elapsedTime.asSeconds();
    }
    else { setAnimation(Animation::IDLE); }

    wallDetectionCooldown += elapsedTime;


    sprite.setPosition(position_);
}


bool Player::collision(std::vector<std::vector<bool>> const& map, sf::Vector2f pos)
{
    double       factor = PIXEL_SIZE;
    sf::Vector2f min    = sf::Vector2f{hitbox_.left, hitbox_.top} + pos;
    sf::Vector2f max    = min + sf::Vector2f{hitbox_.width, hitbox_.height};

    for(int i = floor(min.x / factor) ; i <= floor(max.x / factor) ; i++)
    {
        for(int j = floor(min.y / factor) ; j <= floor(max.y / factor) ; j++)
        {
            if(j < 0 || j >= map.size() || i < 0 || i >= map[j].size())
                return false;
            if(map[j][i])
                return false;
        }
    }

    return true;
}

Player::States Player::combineStates(Orientation ori, Animation ani)
{
    return static_cast<States>(static_cast<int>(ori) + 4 * static_cast<int>(ani));
}

void Player::draw(sf::RenderTarget& target) { sprite.draw(target); }

void Player::setOrientation(Orientation o)
{
    orientation = o;
    sprite.setState(combineStates(orientation, animation));
}

void Player::setAnimation(Animation a)
{
    animation = a;
    sprite.setState(combineStates(orientation, animation));
}

sf::Vector2f Player::getPosition()
{
    auto s = sprite.getSize() / 2.f;
    return position_ + s;
}

sf::FloatRect Player::getHitbox() const
{
    sf::FloatRect res(hitbox_);
    res.left += position_.x;
    res.top += position_.y;
    return res;
}


void Player::setCanMove(bool b) { canMove = b; }

void Player::setInitialPosition(sf::Vector2f pos)
{
    pos.x -= hitbox_.left + hitbox_.width / 2.0;
    pos.y -= hitbox_.top + hitbox_.height / 2.0;
    position_ = pos;
    sprite.setPosition(position_);
}
