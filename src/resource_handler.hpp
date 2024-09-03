#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "embedded_resources.hpp"
#include <stdexcept>

void debug_resources();
std::vector<unsigned char> get_resource_data(std::string path);