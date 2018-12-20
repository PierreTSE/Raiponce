#ifndef ANIMATEDSPRITE_HPP
#define ANIMATEDSPRITE_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>


class AnimatedSprite : public sf::Sprite
{
    public:
        AnimatedSprite(int nFrame, sf::Time time, const sf::Texture& tex);
        AnimatedSprite(int nFrame, sf::Time time, const sf::Texture& tex, sf::IntRect textRect);
        void reset();
        
        void update();

		int getNbFrame();
		
		sf::IntRect const& getFrameSize() const { return frameSize; }
    
    private:
        sf::IntRect frameSize;
        int numFrame;
        int n;
        sf::Time timeBetween;
        sf::Vector2i origin;
        sf::Time animationProgress;
};


#endif // ANIMATEDSPRITE_HPP