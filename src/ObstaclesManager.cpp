#include "ObstaclesManager.h"
#include "globalClock.hpp"
#include "Utilities.hpp"
#include "constantes.hpp"

ObstaclesManager::ObstaclesManager()
{
}

ObstaclesManager & ObstaclesManager::getInstance()
{
	static ObstaclesManager obs;
	return obs;
}

void ObstaclesManager::gestion(sf::RenderWindow & window)
{
	timer += globalClock::getClock().frameTime();

	if (timer > sf::seconds(5)) {
		obstacles_.emplace_back(random(TOWER_X1, TOWER_X2), 0);
		timer = sf::Time::Zero;
	}
	for (auto &o : obstacles_) {
		o.draw(window);
	}

	obstacles_.erase(std::remove_if(obstacles_.begin(),
		obstacles_.end(),
		[](auto& elem) { return elem.isDead(); }),
		obstacles_.end());
}
