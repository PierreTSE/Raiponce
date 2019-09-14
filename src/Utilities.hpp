#ifndef UTILITIES_H
#define UTILITIES_H

#include <SFML/Graphics.hpp>
#include "filesystem.hpp"

sf::Vector2f normalize(const sf::Vector2f& source);

int random(int min, int max);
int random(int max);

template<typename T>
void centerOrigin(T& t) {
    t.setOrigin(t.getLocalBounds().width / 2.0, t.getLocalBounds().height / 2.0);
}

void fit(sf::Sprite& s);

std::filesystem::path strip_root(const std::filesystem::path& p);

#endif // !UTILITIES_H