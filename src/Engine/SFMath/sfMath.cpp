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
}