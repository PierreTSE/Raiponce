#include "Utilities.hpp"
#include "constantes.hpp"
#include <random>

sf::Vector2f normalize(const sf::Vector2f& source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));
	if (length != 0)
		return sf::Vector2f(source.x / length, source.y / length);
	else
		return source;
}

int random(int min, int max)
{
    std::random_device rd;
    static std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distrib(min, max);
    return distrib(eng);
}

int random(int max)
{
    return random(0, max);
}

sf::Color makeHSV(int hue, float sat, float val, float alpha)
{
	hue %= 360;
	while (hue < 0) hue += 360;

	if (sat < 0.f) sat = 0.f;
	if (sat > 1.f) sat = 1.f;

	if (val < 0.f) val = 0.f;
	if (val > 1.f) val = 1.f;

	int h = hue / 60;
	float f = float(hue) / 60 - h;
	float p = val * (1.f - sat);
	float q = val * (1.f - sat * f);
	float t = val * (1.f - sat * (1 - f));

	switch (h)
	{
	default:
	case 0:
	case 6: return sf::Color(val * 255, t * 255, p * 255, alpha);
	case 1: return sf::Color(q * 255, val * 255, p * 255, alpha);
	case 2: return sf::Color(p * 255, val * 255, t * 255, alpha);
	case 3: return sf::Color(p * 255, q * 255, val * 255, alpha);
	case 4: return sf::Color(t * 255, p * 255, val * 255, alpha);
	case 5: return sf::Color(val * 255, p * 255, q * 255, alpha);
	}
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