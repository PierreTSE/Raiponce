#include "Chevalier.hpp"
#include "RessourceLoader.hpp"
#include "globalClock.hpp"
#include "Utilities.hpp"



Chevalier::Chevalier()
{
    sprites_.emplace_back();
    sprites_.back().setTexture(RessourceLoader::getTexture("chevalier_haut.png"));
    sprites_.emplace_back();
    sprites_.back().setTexture(RessourceLoader::getTexture("chevalier_milieu.png"));
    sprites_.emplace_back();
    sprites_.back().setTexture(RessourceLoader::getTexture("chevalier_bas.png"));

	hitbox_.setSize({ 100,200 });
	hitbox_.setOrigin(-85 + sprites_.back().getGlobalBounds().width / 2.f, -40 + sprites_.back().getGlobalBounds().width / 2.f);

	for (auto &s : sprites_)
		s.setOrigin({ s.getGlobalBounds().width / 2.f, s.getGlobalBounds().height / 2.f });

	tempsVide_ = sf::Time::Zero;
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

		if (animationTime_ > sf::milliseconds(50))
		{
			animationTime_ = sf::Time::Zero;
			currentFrame_++;
			if (currentFrame_ >= sprites_.size())
				currentFrame_ = 0;
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			sp.y = -1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			sp.y = 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			sp.x = -1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			sp.x = 1;

		if (sprites_.front().getPosition().x + sprites_.front().getGlobalBounds().width/2 < ch.getX() || sprites_.front().getPosition().x - sprites_.front().getGlobalBounds().width / 2 > ch.getX() + ch.getWidth())
		{
			tempsVide_ += globalClock::getClock().frameTime();

			if (tempsVide_ > sf::seconds(1.5))
				dead = true;
		}
		else
			tempsVide_ = sf::Time::Zero;
	}
	

	sp = normalize(sp);

	sf::Vector2f dep;
	dep.x = globalClock::getClock().frameTime().asSeconds() * speed * sp.x;
	dep.y = globalClock::getClock().frameTime().asSeconds() * speed * sp.y;

	for(auto &s : sprites_)
		s.move(dep);

	hitbox_.move(dep);

	window.draw(sprites_[currentFrame_]);
	window.draw(hitbox_);
}

void Chevalier::setPosition(int x, int y)
{
	for (auto &s : sprites_)
		s.setPosition(x, y);
	hitbox_.setPosition(x, y);
}
