#include "ObstaclesManager.h"
#include "globalClock.hpp"
#include "Utilities.hpp"
#include "constantes.hpp"
#include "RessourceLoader.hpp"
#include <filesystem>

ObstaclesManager::ObstaclesManager()
{
    const std::filesystem::path obstaclesPath("rc/sprites/obstacles");
    for(auto& p : std::filesystem::directory_iterator(obstaclesPath))
    {
        obstacles_.emplace_back(strip_root(p.path()).u8string());
    }
}

ObstaclesManager & ObstaclesManager::getInstance()
{
	static ObstaclesManager obs;
	return obs;
}

void ObstaclesManager::gestion(sf::RenderWindow & window)
{
	timer += globalClock::getClock().frameTime();

	if (timer > sf::seconds(2)) {
        int n_obs = random(obstacles_.size() - 1);
        const float h_sprite = 200;
		if(obstacles_[n_obs].getPosition().y > WINDOW_SIZE_Y + h_sprite/2){
		    obstacles_[n_obs].reset();
		    timer = sf::Time::Zero;
		}
	}
	for (auto &o : obstacles_) {
		o.draw(window);
	}
}
