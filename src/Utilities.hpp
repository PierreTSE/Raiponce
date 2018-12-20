#ifndef UTILITIES_H
#define UTILITIES_H

#include <SFML/Graphics.hpp>
#include <filesystem>

sf::Color static makeHSV(int hue, float sat, float val, float alpha);

// hue: 0-360°; sat: 0.f-1.f; val: 0.f-1.f
sf::Color makeHSV(int hue, float sat, float val, float alpha);

template<typename T>
void centerOrigin(T& t) {
    t.setOrigin(t.getLocalBounds().width/2.0, t.getLocalBounds().height/2.0);
}

void fit(sf::Sprite& s);

std::filesystem::path strip_root(const std::filesystem::path& p);

#endif // !UTILITIES_H