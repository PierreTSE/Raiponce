#include "Utilities.hpp"
#include "constantes.hpp"
#include <random>

sf::Vector2f normalize(const sf::Vector2f& source) {
    const float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
        return sf::Vector2f(source.x / length, source.y / length);
    else
        return source;
}

int random(int min, int max) {
#if defined(WIN32) && (defined(__GNUC__) || defined(__GNUG__))
    static std::default_random_engine eng(std::time(nullptr));
#else
    static std::default_random_engine eng(std::random_device{}());
#endif
    std::uniform_int_distribution<int> distrib(min, max);
    return distrib(eng);
}

int random(int max) {
    return random(0, max);
}

void fit(sf::Sprite& s) {
    const double ratio = std::max(s.getTexture()->getSize().x / static_cast<double>(WINDOW_SIZE_X),
                                  s.getTexture()->getSize().y / static_cast<double>(WINDOW_SIZE_Y));
    s.setScale(1.0 / ratio, 1.0 / ratio);
}

std::filesystem::path strip_root(const std::filesystem::path& p) {
    const std::filesystem::path& parent_path = p.parent_path();
    if (parent_path.empty() || parent_path.string() == "/")
        return std::filesystem::path();
    else
        return strip_root(parent_path) / p.filename();
}