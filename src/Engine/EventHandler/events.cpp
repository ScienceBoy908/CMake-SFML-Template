#include "Engine/EventHandler/events.hpp"

Events::EventHandler::EventHandler(sf::Vector2u windowSizeU, bool fullscreen, std::string windowName)
    : window({ windowSizeU.x, windowSizeU.y }, windowName, (fullscreen ? sf::Style::Fullscreen : sf::Style::Default)),
    inputStates()
{
    elapsedTime = 0.0f;
    dt = 0.0f;
    sf::Uint32 style = (fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    window.setFramerateLimit(144);


    // create input states
    inputStates.resize(static_cast<int>(sf::Keyboard::KeyCount));
    for (int i = 0; i < sf::Keyboard::KeyCount; i++)
    {
        Events::InputState inputState{ i,Events::InType::None };
        inputStates[i] = inputState;
    }
    windowSizeF = static_cast<sf::Vector2f>(window.getSize());
}

bool Events::EventHandler::TestInput(sf::Keyboard::Key key, InType inType)
{
    InputState inState = inputStates[key];
    return inState.state == inType;
}

void Events::EventHandler::Step()
{

    dt = clock.restart().asSeconds();
    elapsedTime += dt;

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
            sf::Vector2u windowSizeU(event.size.width, event.size.height);
            windowSizeF = static_cast<sf::Vector2f>(windowSizeU);
        }
    }

    // Update key inputs
    for (int i = 0; i < inputStates.size(); i++)
    {
        InputState& inState = inputStates[i];
        bool pressed = sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(inState.keyCode));

        switch (inState.state) {
        case InType::None:
            if (pressed) {
                inState.state = InType::Pressed;
            }
            break;

        case InType::Pressed:
            if (pressed) {
                inState.state = InType::Held;
            }
            else {
                inState.state = InType::Released;
            }
            break;

        case InType::Released:
            if (pressed) {
                inState.state = InType::Pressed;
            }
            else {
                inState.state = InType::None;
            }
            break;

        case InType::Held:
            if (!pressed) {
                inState.state = InType::Released;
            }
            break;

        default:
            break;
        }

    }

}
