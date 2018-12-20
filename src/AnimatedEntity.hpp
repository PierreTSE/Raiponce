#ifndef ANIMATEDENTITY_HPP
#define ANIMATEDENTITY_HPP

#include "animatedSprite.hpp"
#include <type_traits>
#include <SFML/Graphics/RenderTarget.hpp>
#include <vector>


template<typename StateType>
    class AnimatedEntity : public sf::Transformable
{
    static_assert(std::is_enum_v<StateType>, "AnimatedEntity is expecting an enum type to describe its possible states");
    
    public:
        AnimatedEntity(StateType defaultState, AnimatedSprite const& sprite);
        void setup(StateType state, AnimatedSprite const& sprite);
        void setState(StateType state);
		sf::Vector2f getSize();
		void setColor(sf::Color c);
        void draw(sf::RenderTarget&);
        void updateTransformation();
    
    private:
        AnimatedSprite* currentSprite();
    
        StateType current;
        std::vector<StateType> states;
        std::vector<AnimatedSprite> sprites;
		sf::Color multColor;
};


template<typename StateType>
void AnimatedEntity<StateType>::setState(StateType state)
{
    if(current == state)
        return;
    ptrdiff_t index = std::find(states.begin(), states.end(), current) - states.begin();
    if(index < states.size())
        sprites[index].reset();
    current = state;
}

template<typename StateType>
inline sf::Vector2f AnimatedEntity<StateType>::getSize()
{    
    updateTransformation();
	sf::Vector2f res;
	res.x = currentSprite()->getFrameSize().width * getScale().x;
	res.y = currentSprite()->getFrameSize().height * getScale().y;
	return res;
}

template<typename StateType>
inline void AnimatedEntity<StateType>::setColor(sf::Color c)
{
	multColor = c;
}

template<typename StateType>
void AnimatedEntity<StateType>::setup(StateType state, AnimatedSprite const& sprite)
{
    states.push_back(state);
    sprites.push_back(sprite);
}

template<typename StateType>
AnimatedEntity<StateType>::AnimatedEntity(StateType defaultState, AnimatedSprite const& sprite)
{
	multColor = sf::Color(255, 255, 255);
    setup(defaultState, sprite);
    current = defaultState;
}

template<typename StateType>
void AnimatedEntity<StateType>::draw(sf::RenderTarget& target)
{
    auto c = currentSprite();
    if(!c)
        return;
    AnimatedSprite& curSprite = *c;
    updateTransformation();
    curSprite.update();
	curSprite.setColor(multColor);

    target.draw(curSprite);
}

template<typename StateType>
AnimatedSprite* AnimatedEntity<StateType>::currentSprite()
{
    ptrdiff_t index = std::find(states.begin(), states.end(), current) - states.begin();
    return index < states.size() ? &sprites[index] : nullptr;
}

template<typename StateType>
void AnimatedEntity<StateType>::updateTransformation()
{
    auto p = getPosition();
    auto c = currentSprite();
    if(!c)
        return;
    AnimatedSprite& curSprite = *c;
    curSprite.setOrigin(getOrigin());
    curSprite.setPosition(getPosition());
    curSprite.setRotation(getRotation());
    curSprite.setScale(getScale());
}

#endif // ANIMATEDENTITY_HPP