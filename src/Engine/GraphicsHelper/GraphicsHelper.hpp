#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace GraphicsHelper
{
	class ThickVertex
	{
	public:
		ThickVertex(const sf::Vector2f& position, const sf::Color& color, float _thickness);
		sf::Vertex vertex;
		float thickness;
	};

	class ThickLine : public sf::Drawable
	{
	public:
		ThickLine(unsigned int numSides, float thickness);
		ThickVertex& operator[](size_t index);
		void setColor(sf::Color color);
		void setThickness(float _thickness);

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		std::vector<ThickVertex> vertices;
	};
}