#include "GraphicsHelper.hpp"
#include "Engine/SFMath/sfMath.hpp"
using namespace sfMath;

namespace GraphicsHelper
{
	ThickVertex::ThickVertex(const sf::Vector2f& position, const sf::Color& color, float _thickness) 
		: vertex(position, color), thickness(_thickness) {}


	ThickLine::ThickLine(unsigned int numSides, float thickness)
	{
		vertices.resize(numSides, {sf::Vector2f(0,0), sf::Color::White, thickness});
	}
	ThickVertex& ThickLine::operator[](size_t index)
	{
		return vertices[index];
	}
	void ThickLine::setColor(sf::Color color)
	{
		for (auto& vertex : vertices) 
		{
			vertex.vertex.color = color;
		}
	}
	void ThickLine::setThickness(float thickness)
	{
		for (auto& vertex : vertices) 
		{
			vertex.thickness = thickness;
		}
	}
	void ThickLine::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (vertices.size() < 2)
		{
			return;
		}

		sf::VertexArray va(sf::TriangleStrip, vertices.size() * 2);

		float lastAngle = 0;
		for (int i = 0; i < vertices.size(); ++i)
		{
			// Get the angle from this point to the next, or if the last point than the one before it.
			float angle = lastAngle;

			if (i < vertices.size() - 1)
			{
				sf::Vector2f vector = vertices[i + 1].vertex.position - vertices[i].vertex.position;
				angle = GetVectorAngle(vector);
				lastAngle = angle;
			}

			// Get properties
			float thickness = vertices[i].thickness;
			sf::Vector2f position = vertices[i].vertex.position;
			sf::Color color = vertices[i].vertex.color;

			// Create the right and left sides
			sf::Vector2f rightSide(thickness / 2.f, 0.f);
			rightSide = RotateVector(rightSide, angle + Rad(-90.f));

			sf::Vector2f leftSide(thickness / 2.f, 0.f);
			leftSide = RotateVector(leftSide, angle + Rad(90.f));

			// Change the vertex array
			va[2*i].position = rightSide + position;
			va[2*i].color = color;
			va[2*i+1].position = leftSide + position;
			va[2*i+1].color = color;
		}
		// Draw
		target.draw(va, states);
	}
}
