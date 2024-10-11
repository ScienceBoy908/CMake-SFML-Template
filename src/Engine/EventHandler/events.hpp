#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace Events
{
	enum class InType
	{
		None,
		Pressed,
		Held,
		Released,
	};
	struct InputState
	{

		int keyCode;
		InType state;
	};
	class EventHandler
	{
	public:
		EventHandler(sf::Vector2u windowSizeU, bool fullscreen = false, std::string windowName = "Window");
		void Step();
		bool TestInput(sf::Keyboard::Key key, InType inType);

		sf::RenderWindow window;
		float dt;
		float elapsedTime;
		sf::Vector2f windowSizeF;

	private:
		sf::Clock clock;
		std::vector<InputState> inputStates;

	};
}