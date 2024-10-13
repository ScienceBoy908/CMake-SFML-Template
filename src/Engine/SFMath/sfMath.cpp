#include "SFMath/sfMath.hpp"

namespace sfMath {
    sf::Color operator*(const sf::Color& color, float scalar) {
        return sf::Color(
            std::min(255, static_cast<int>(color.r * scalar)),
            std::min(255, static_cast<int>(color.g * scalar)),
            std::min(255, static_cast<int>(color.b * scalar)),
            std::min(255, static_cast<int>(color.a * scalar))
        );
    }

    sf::Color LerpColor(const sf::Color& a, const sf::Color& b, float t)
    {
        return sf::Color(
            Lerp<sf::Uint8>(a.r, b.r, t),
            Lerp<sf::Uint8>(a.g, b.g, t),
            Lerp<sf::Uint8>(a.b, b.b, t),
            Lerp<sf::Uint8>(a.a, b.a, t)
        );
    }

    void CenterAlignText(sf::Text& txt)
    {
        sf::FloatRect txtBounds = txt.getLocalBounds();
        txt.setOrigin(txtBounds.width / 2, txtBounds.height / 2);
    }

    float GetVectorAngle(const sf::Vector2f& vector)
    {
        return std::atan2(vector.y, vector.x);
    }
    float GetVectorLength(const sf::Vector2f& vector) {
        return std::sqrt(vector.x * vector.x + vector.y * vector.y);
    }

    sf::Vector2f RotateVector(const sf::Vector2f& vector, float angleRadians)
    {
        float cosTheta = std::cos(angleRadians);
        float sinTheta = std::sin(angleRadians);

        // Apply the rotation transformation
        return sf::Vector2f(
            vector.x * cosTheta - vector.y * sinTheta,
            vector.x * sinTheta + vector.y * cosTheta
        );
    }

    sf::Vector2f NormalizeVector(const sf::Vector2f& vector, float toLength=1)
    {
        float length = GetVectorLength(vector) * toLength;
        if (length != 0) {
            return sf::Vector2f(vector.x / length, vector.y / length);
        }
        else {
            return sf::Vector2f(0.f, toLength);  // Return zero vector if length is zero
        }
    }

    float Rad(float deg)
    {
        return deg *  3.14159265f / 180.f;
    }
    float Deg(float rad) 
    {
        return rad * 180.f / 3.14159265f;
    }
}
