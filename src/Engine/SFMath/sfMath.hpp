#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <cmath>

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

	float GetVectorAngle(const sf::Vector2f& vector);
	float GetVectorLength(const sf::Vector2f& vector);

	sf::Vector2f RotateVector(const sf::Vector2f& vector, float angleRadians);

	sf::Vector2f NormalizeVector(const sf::Vector2f& vector, float length);

	float Rad(float deg);
	float Deg(float rad);

}
