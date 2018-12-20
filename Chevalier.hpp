#ifndef CHEVALIER_HPP
#define CHEVALIER_HPP
#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

class Chevalier
{
public:
    Chevalier();

private:
    std::vector<sf::Sprite> sprites_;

    sf::Time animationTime_;
    sf::Clock clock_;


};
#endif // CHEVALIER_HPP
