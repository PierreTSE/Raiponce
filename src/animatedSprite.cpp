#include "animatedSprite.hpp"
#include "globalClock.hpp"
#include <cmath>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>


AnimatedSprite::AnimatedSprite(int nFrame, sf::Time time, const sf::Texture& tex) :
    frameSize(0, 0, tex.getSize().x/nFrame, tex.getSize().y),
    numFrame{nFrame},
    n{0},
    timeBetween{time},
    origin{frameSize.left, frameSize.top},
    animationProgress{sf::Time::Zero}
{
    setTexture(tex);
}

AnimatedSprite::AnimatedSprite(int nFrame, sf::Time time, const sf::Texture& tex, sf::IntRect textRect) :
    frameSize{textRect},
    numFrame{nFrame},
    n{0},
    timeBetween{time},
    origin{frameSize.left, frameSize.top},
    animationProgress{sf::Time::Zero}
{
    setTexture(tex);
}

void AnimatedSprite::update()
{
    animationProgress += globalClock::getClock().frameTime();
    animationProgress %= timeBetween*(float)numFrame;
    int step = floor(animationProgress / timeBetween);
    frameSize.left = origin.x + step * frameSize.width;
    setTextureRect(frameSize);
}

int AnimatedSprite::getNbFrame()
{
	return numFrame;
}

void AnimatedSprite::reset()
{
    animationProgress = sf::Time::Zero;
}
