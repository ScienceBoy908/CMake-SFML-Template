#include <iostream>

#include "events.hpp"
#include "config.hpp"

void processEvents(sf::Window& window)
{
    for (auto event = sf::Event{}; window.pollEvent(event);)
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed)
        {
            auto key = event.key.code;

            if (key == sf::Keyboard::Escape)
            {
                window.close();
            }
        }

        if (event.type == sf::Event::Resized)
        {
            conf::windowSizeU = { event.size.width, event.size.height };
            conf::windowSizeF = static_cast<sf::Vector2f>(conf::windowSizeU);
            std::cout << "Window resized";
        }
    }
}