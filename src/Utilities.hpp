#ifndef UTILITIES_H
#define UTILITIES_H

#include <SFML/Graphics.hpp>
#include <filesystem>


class Utilities {
	public:
		template <class T> static T min(T x1, T x2);
		template <class T> static T max(T x1, T x2);
		sf::Color static makeHSV(int hue, float sat, float val, float alpha);
		
		static int random(int min, int max);
		static int random(int max);
};

template<class T>
inline T Utilities::min(T x1, T x2)
{
	return x1 < x2 ? x1 : x2;
}

template<class T>
inline T Utilities::max(T x1, T x2)
{
	return x1 > x2 ? x1 : x2;
}

// hue: 0-360°; sat: 0.f-1.f; val: 0.f-1.f
inline sf::Color Utilities::makeHSV(int hue, float sat, float val, float alpha)
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

template<typename T>
void centerOrigin(T& t) {
    t.setOrigin(t.getLocalBounds().width/2.0, t.getLocalBounds().height/2.0);
}

void fit(sf::Sprite& s);


std::filesystem::path strip_root(const std::filesystem::path& p);


#endif // !UTILITIES_H