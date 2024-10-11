#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

// Struct to hold both font data and sf::Font
struct FontResource {
    std::vector<unsigned char> fontData;  // Keeps font data alive
    sf::Font font;  // The actual SFML font object
};

void DebugResources();

std::vector<unsigned char> GetResource(std::string path);

sf::Texture GetTexture(std::string path);
FontResource GetFont(std::string path);