#ifndef OBSTACLE_MANAGER_H
#define OBSTACLE_MANAGER_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "Obstacle.h"

class ObstaclesManager {
	private:
		std::vector<Obstacle> obstacles_;
		sf::Time timer;
		
	public:
		ObstaclesManager();
		static ObstaclesManager& getInstance();
		void gestion(sf::RenderWindow &window);
		
};

#endif // !OBSTACLE_H
