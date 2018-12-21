#include "Chevalier.hpp"
#include "RessourceLoader.hpp"
#include "globalClock.hpp"
#include "Utilities.hpp"
#include "ObstaclesManager.h"
#include "constantes.hpp"

#include <iostream>

Chevalier::Chevalier()
{
    sprites_.emplace_back();
    sprites_.back().setTexture(RessourceLoader::getTexture("sprites/chevalier_haut.png"));
    sprites_.emplace_back();
    sprites_.back().setTexture(RessourceLoader::getTexture("sprites/chevalier_milieu.png"));
    sprites_.emplace_back();
    sprites_.back().setTexture(RessourceLoader::getTexture("sprites/chevalier_bas.png"));

	hitbox_.setSize({ 100,200 });
	hitbox_.setOrigin(-85 + sprites_.back().getGlobalBounds().width / 2.f, -40 + sprites_.back().getGlobalBounds().width / 2.f);

	for (auto &s : sprites_)
		s.setOrigin({ s.getGlobalBounds().width / 2.f, s.getGlobalBounds().height / 2.f });

	tempsVide_ = sf::Time::Zero;
	tempsImune_ = sf::seconds(1000);

	vit_ = { 0,0 };

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
}

void Chevalier::draw(sf::RenderWindow & window, Cheveux &ch)
{
	sf::Vector2f sp = { 0,0 };

	if (dead)
	{
		sp.y = 1;
		for (auto &s : sprites_)
			s.rotate(globalClock::getClock().frameTime().asSeconds() * 180);
	}
	else
	{
		animationTime_ += globalClock::getClock().frameTime();
		tempsImune_ += globalClock::getClock().frameTime();

		if (animationTime_ > sf::milliseconds(50))
		{
			animationTime_ = sf::Time::Zero;
			currentFrame_++;
			if (currentFrame_ >= sprites_.size())
				currentFrame_ = 0;
		}

		if (tempsImune_ > sf::seconds(1))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				sp.y = -1;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				sp.y = 1;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				sp.x = -1;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				sp.x = 1;

			for (auto &s : sprites_)
				s.setRotation(0);
		}
		else
		{
			for (auto &s : sprites_)
				s.rotate(globalClock::getClock().frameTime().asSeconds() * 1000);

			sp = vit_;

			if (vit_.x > 0)
			{
				vit_.x -= globalClock::getClock().frameTime().asSeconds() * 1.5;
				if (vit_.x < 0)
				{
					tempsImune_ = sf::seconds(100);
					vit_.x = 0;
				}
					
			}
			if (vit_.x < 0)
			{
				vit_.x += globalClock::getClock().frameTime().asSeconds() * 1.5;
				if (vit_.x > 0)
				{
					tempsImune_ = sf::seconds(100);
					vit_.x = 0;
				}
			}
				
			if (vit_.y > 0)
			{
				vit_.y -= globalClock::getClock().frameTime().asSeconds() * 1.5;
				if (vit_.y < 0)
				{
					tempsImune_ = sf::seconds(100);
					vit_.y = 0;
				}
			}
			if (vit_.y < 0)
			{
				vit_.y += globalClock::getClock().frameTime().asSeconds() * 1.5;
				if (vit_.y > 0)
				{
					tempsImune_ = sf::seconds(100);
					vit_.y = 0;
				}
			}
		}

		if (sprites_.front().getPosition().x + sprites_.front().getGlobalBounds().width/2 < ch.getX() || sprites_.front().getPosition().x - sprites_.front().getGlobalBounds().width / 2 > ch.getX() + ch.getWidth())
		{
			tempsVide_ += globalClock::getClock().frameTime();

			if (tempsVide_ > sf::seconds(1.5))
				dead = true;
		}
		else
		{
			if (tempsImune_ > sf::seconds(0.5f) && tempsVide_ != sf::Time::Zero)
				tempsImune_ = sf::seconds(100);

			tempsVide_ = sf::Time::Zero;
		}
			

		if (tempsImune_ > sf::seconds(1))
		{
			for (auto o : ObstaclesManager::getInstance().getVector())
			{
				if (hitbox_.getGlobalBounds().intersects(o.getBox()))
				{
					tempsImune_ = sf::Time::Zero;
					vit_ = sprites_.back().getPosition() - (o.getPosition() + sf::Vector2f(o.getSize().x / 2, o.getSize().y / 2));
					vit_ = normalize(vit_);

                    const int n_boing = random(boings_.size()-1);
                    if(boings_[n_boing].getStatus() != sf::Sound::Status::Playing)
                        boings_[n_boing].play();
                    if(random(1, 100) <= 60)
                    {
                        const int n_surp = random(surprises_.size()-1);
                        if(surprises_[n_surp].getStatus() != sf::Sound::Status::Playing)
                            surprises_[n_surp].play();
                    }
				}
			}

		}


		if (sprites_.back().getPosition().x - sprites_.back().getGlobalBounds().width/2 < 0) 
		{
			tempsImune_ = sf::Time::Zero;
			vit_.x = 2;

            const int n_boing = random(boings_.size()-1);
                if(boings_[n_boing].getStatus() != sf::Sound::Status::Playing)
                    boings_[n_boing].play();          
            if(random(1, 100) <= 40)
			{
                const int n_surp = random(surprises_.size()-1);
                if(surprises_[n_surp].getStatus() != sf::Sound::Status::Playing)
                    surprises_[n_surp].play();
			}           
		}
		if (sprites_.back().getPosition().x + sprites_.back().getGlobalBounds().width/2 > WINDOW_SIZE_X)
		{
			tempsImune_ = sf::Time::Zero;
			vit_.x = -2;

            const int n_boing = random(boings_.size()-1);
                if(boings_[n_boing].getStatus() != sf::Sound::Status::Playing)
                    boings_[n_boing].play();                   
            if(random(1, 100) <= 40)
            {
                const int n_surp = random(surprises_.size()-1);
                if(surprises_[n_surp].getStatus() != sf::Sound::Status::Playing)
                    surprises_[n_surp].play();
            }
		}
		if (sprites_.back().getPosition().y - sprites_.back().getGlobalBounds().height/2 < 0)
		{
			tempsImune_ = sf::Time::Zero;
			vit_.y = 0.5;
            
            const int n_boing = random(boings_.size()-1);
                if(boings_[n_boing].getStatus() != sf::Sound::Status::Playing)
                    boings_[n_boing].play();                   
            if(random(1, 100) <= 40)
			{
                const int n_surp = random(surprises_.size()-1);
                if(surprises_[n_surp].getStatus() != sf::Sound::Status::Playing)
                    surprises_[n_surp].play();
			}
		}
		if (sprites_.back().getPosition().y + sprites_.back().getGlobalBounds().height/2 > WINDOW_SIZE_Y)
		{
			tempsImune_ = sf::Time::Zero;
			vit_.y = -0.5;
            
            const int n_boing = random(boings_.size()-1);
                if(boings_[n_boing].getStatus() != sf::Sound::Status::Playing)
                    boings_[n_boing].play();                   
            if(random(1, 100) <= 40)
			{
                const int n_surp = random(surprises_.size()-1);
                if(surprises_[n_surp].getStatus() != sf::Sound::Status::Playing)
                    surprises_[n_surp].play();
			}
		}

		
	}
	

	sp = normalize(sp);

	sf::Vector2f dep;
	dep.x = globalClock::getClock().frameTime().asSeconds() * speed * sp.x;
	dep.y = globalClock::getClock().frameTime().asSeconds() * speed * sp.y;

	for(auto &s : sprites_)
		s.move(dep);

	hitbox_.move(dep);

	window.draw(sprites_[currentFrame_]);
	//window.draw(hitbox_);
}

void Chevalier::setPosition(int x, int y)
{
	for (auto &s : sprites_)
		s.setPosition(x, y);
	hitbox_.setPosition(x, y);
}

bool Chevalier::isDead()
{
	return dead && hitbox_.getPosition().y > WINDOW_SIZE_Y;
}

void Chevalier::revive(float x, float y)
{
	setPosition(x, y);
	dead = false;

	tempsVide_ = sf::Time::Zero;
	tempsImune_ = sf::seconds(1000);

	vit_ = { 0,0 };

	for (auto &s : sprites_)
		s.setRotation(0);
}
