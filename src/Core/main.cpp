#include "Engine.hpp"
using namespace sfMath;

int main()
{
    // Debug info
    string workingDirString = std::filesystem::current_path().string();
    std::cout << "Current Working Directory: " << workingDirString << "\n";
    
    // Prints all loaded resource files and their paths
    DebugResources();

    // Create Window using the event handler class
    Events::EventHandler eventHandler({ 800,800 }, true, "HI! My name is.. What?! My name is- WHO?!");
    auto& window = eventHandler.window;

    /****************************************************/
    
    // Create a background color
    sf::Color backgroundColor = sf::Color::Black;

    // Create a Gearod the frog (TM)
    sf::Texture txr_Gearod = GetTexture("frogside.png");
    sf::Sprite spr_Gearod = sf::Sprite(txr_Gearod);
    txr_Gearod.setSmooth(true);
    
    sf::Vector2f txrSize = static_cast<sf::Vector2f>(txr_Gearod.getSize());
    spr_Gearod.setOrigin(txrSize.x/2.f,txrSize.y/2.f);

    // Create a label
    FontResource arial = GetFont("arial.ttf");
    sf::Text textLabel("Gearod the Frog �", arial.font);
    textLabel.setCharacterSize(30u);



    // Begin game loop
    while (window.isOpen())
    {

        eventHandler.Step();

        // shift the background color if space is pressed/held
        sf::Color targetBackgroundColor = sf::Color::Black;
        if (eventHandler.TestInput(sf::Keyboard::Space,Events::InType::Held)) 
        {
            targetBackgroundColor = sf::Color::Red;
        }

        backgroundColor = LerpColor(backgroundColor, targetBackgroundColor, std::min(eventHandler.dt * 2,1.f));

        // Set Gearod to the mouse position
        sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition());
        spr_Gearod.setPosition(
            Lerp<sf::Vector2f>(
                spr_Gearod.getPosition(),
                mousePosition,
                std::min(eventHandler.dt * 5 * (backgroundColor.r / 255.f + 0.1), 1.)
            )
        );

        // Set the text to the frog's position
        textLabel.setPosition(spr_Gearod.getPosition() - sf::Vector2f(0,150));

        // Change the origin
        CenterAlignText(textLabel);

        /***************************DRAW-STAGE*************************/

        window.clear(backgroundColor);

        window.draw(spr_Gearod); // draw the frog

        window.draw(textLabel); // draw text

        window.display();
    }
    // Cleanup
    return 0;
}