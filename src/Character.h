#ifndef CHARACTER_H
#define CHARACTER_H


#include <SFML/Graphics.hpp>
#include "globalClock.hpp"
#include "DJ.hpp"
#include "AnimatedEntity.hpp"

enum class Orientation
{
	LEFT = 0,
	UP = 1,
	RIGHT = 2,
	DOWN = 3
};

enum class Animation
{
	IDLE = 0,
	WALKING = 1,
	RINGING = 2
};

class Player
{
public:
	Player();

	bool collision(std::vector<std::vector<bool>> const& map, sf::Vector2f                                  pos);
	void movement(const sf::Time&                        elapsedTime, std::vector<std::vector<bool>> const& map);
	void draw(sf::RenderTarget&                          target);

	void setCanMove(bool b);

	template<typename CB>
	void ring(CB&& callback); // Test

	void setInitialPosition(sf::Vector2f);

	void setOrientation(Orientation o);
	void setAnimation(Animation     a);

	sf::Vector2f getPosition();

	sf::FloatRect getHitbox() const;

	void setFullLife();

private:
	enum States
	{
		IDLE_LEFT = 0,
		IDLE_UP = 1,
		IDLE_RIGHT = 2,
		IDLE_DOWN = 3,
		WALKING_LEFT = 4,
		WALKING_UP = 5,
		WALKING_RIGHT = 6,
		WALKING_DOWN = 7,
		RINGING_LEFT = 8,
		RINGING_UP = 9,
		RINGING_RIGHT = 10,
		RINGING_DOWN = 11
	};

	static States combineStates(Orientation ori, Animation ani);

	int speed_ = 300;


	sf::Vector2f position_ = { 0, 0 };

	AnimatedEntity<States> sprite;
	Orientation            orientation;
	Animation              animation;
	sf::FloatRect          hitbox_;

	bool canMove = true;
	bool canRing = true;

	sf::Time wallDetectionCooldown = sf::Time::Zero;
};

template<typename CB>
void Player::ring(CB&& callback)
{
	if (!canRing)
		return;

	DJ::getInstance().playSound("cloche.wav", true);
	
	setAnimation(Animation::RINGING);
	setCanMove(false);



	canRing = false;

	globalClock::getClock().executeIn(sf::seconds(0.74),
		[&]()
	{
		setAnimation(Animation::IDLE);
		setCanMove(true);
	});

	globalClock::getClock().executeIn(sf::seconds(1), [&]() { canRing = true; });

	std::forward<CB>(callback)();
}


#endif // !CHARACTER_H