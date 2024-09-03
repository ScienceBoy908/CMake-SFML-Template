#include <iostream>
#include <vector>
#include <filesystem>
using std::string;

#include <SFML/Graphics.hpp>
#include "resource_handler.hpp"
#include "events.hpp"
#include "config.hpp"




int main()
{
    // Debug info
    string workingDirString = std::filesystem::current_path().string();
    std::cout << "Current Working Directory: " << workingDirString << "\n";
    
    debug_resources();

    // Create Window
    auto window = sf::RenderWindow{ sf::VideoMode(conf::windowSizeU.x,conf::windowSizeU.y), "CMake SFML Project", sf::Style::Fullscreen};
    window.setFramerateLimit(conf::fps);

    // Get current window size because fullscreen changes it
    conf::windowSizeU = window.getSize();
    conf::windowSizeF = static_cast<sf::Vector2f>(conf::windowSizeU);

    // PRE GAME START ---
    sf::Clock clock;
    float total_time = 0.0f;
    float dt = 0;

    sf::Texture test_texture;
    test_texture.setSmooth(false);
    test_texture.generateMipmap();

    auto mem_img = get_resource_data("frogside.png");
    test_texture.loadFromMemory(mem_img.data(),mem_img.size());

    sf::Sprite sprite;
    sprite.setTexture(test_texture);
    
    

    // Begin game loop
    while (window.isOpen())
    {
        // Get DeltaTime
        dt = clock.restart().asSeconds();
        total_time += dt;

        processEvents(window);

        window.clear();

        sf::Vector2f scale_factor(cos(total_time), cos(total_time));
        scale_factor += sf::Vector2f(2, 2);
        sprite.setRotation(cos(total_time*2.0f)*15.0f);
        sprite.setScale(scale_factor);
        auto offset = static_cast<sf::Vector2f>(test_texture.getSize()) * 0.5f;
        sprite.setOrigin(offset);
        sprite.setPosition((conf::windowSizeF / 2.0f));
        window.draw(sprite);

        window.display();
    }
    // Cleanup
    return 0;
}
