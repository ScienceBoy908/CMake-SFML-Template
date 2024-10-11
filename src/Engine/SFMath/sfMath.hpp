#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>

namespace sfMath
{
	// extra color operators
	sf::Color operator*(const sf::Color& color, float scalar);


	// Lerp two values
	template <typename T>
	inline T Lerp(const T& a, const T& b, float t) {
		return a + ((b - a) * t);
	}

	sf::Color LerpColor(const sf::Color& a, const sf::Color& b, float t);

	void CenterAlignText(sf::Text& txt);
}