#include "Mechant.hpp"
#include "RessourceLoader.hpp"
#include "constantes.hpp"
#include "globalClock.hpp"
#include "Utilities.hpp"
#include <iostream>


Mechant::Mechant(bool isOnLeft)
{
    sprite_.setTexture(RessourceLoader::getTexture("mechant.png"));
    
    if(!isOnLeft)
    {
        sprite_.setPosition({WINDOW_SIZE_X - sprite_.getGlobalBounds().width, static_cast<float>(random(WINDOW_SIZE_Y))});
    }
	else
	{
	    sprite_.scale(-1,1);
        sprite_.move(sprite_.getGlobalBounds().width,0);
	}

    //sprite_.setOrigin(sprite_.getGlobalBounds().width/2, sprite_.getGlobalBounds().height/2);
}

void Mechant::draw(sf::RenderWindow & window)
{
    sprite_.move(0, vit_ * globalClock::getClock().frameTime().asSeconds() * (isGoingDown?1:-1));
    if(sprite_.getPosition().y + sprite_.getGlobalBounds().height > WINDOW_SIZE_Y)
	{
	    const float diff = sprite_.getPosition().y + sprite_.getGlobalBounds().height - WINDOW_SIZE_Y;
        sprite_.move(0, -2 * diff);
        isGoingDown = false;
	}
    else if(sprite_.getPosition().y < 0)
	{	   
        sprite_.move(0, -2 * sprite_.getPosition().y);
        isGoingDown = true;
	}

    std::cout<< sprite_.getPosition().y<<std::endl;

    window.draw(sprite_);
}
