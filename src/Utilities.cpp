#include "Utilities.hpp"
#include "constantes.hpp"
#include <random>


int Utilities::random(int min, int max)
{
    std::random_device rd;
    static std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distrib(min, max);
    return distrib(eng);
}

int Utilities::random(int max)
{
    return random(0, max);
}

void fit(sf::Sprite & s)
{
    const double ratio = std::max(s.getTexture()->getSize().x / static_cast<double>(WINDOW_SIZE_X), s.getTexture()->getSize().y / static_cast<double>(WINDOW_SIZE_Y));
    s.setScale(1.0/ratio, 1.0/ratio);
}


std::filesystem::path strip_root(const std::filesystem::path& p)
{
    const std::filesystem::path& parent_path = p.parent_path();
    if(parent_path.empty() || parent_path.string() == "/")
        return std::filesystem::path();
    else
        return strip_root(parent_path) / p.filename();
}