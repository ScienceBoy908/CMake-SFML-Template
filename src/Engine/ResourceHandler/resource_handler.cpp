#include "resource_handler.hpp"

#include "embedded_resources.hpp"
#include "zip_file.hpp"


std::vector<unsigned char> resource_vector(embedded_resources, embedded_resources + embedded_resources_len);
miniz_cpp::zip_file resource_file = miniz_cpp::zip_file(resource_vector);

// Debug print filenames
void DebugResources()
{
	for (const auto& name : resource_file.infolist()) {
		std::cout << "Collecting resource: " << name.filename << std::endl;
	}
}

std::vector<unsigned char> GetResource(std::string path) 
{
	std::string resource_data_string = resource_file.read(path);
	std::vector<unsigned char> resource_data(resource_data_string.begin(), resource_data_string.end());
	return resource_data;
}

sf::Texture GetTexture(std::string path)
{
	auto image_data = GetResource(path);
	sf::Texture texture;
	texture.loadFromMemory(image_data.data(), image_data.size());

	return texture;
}

FontResource GetFont(std::string path) {
    FontResource fontResource;

    fontResource.fontData = GetResource(path);

    if (!fontResource.font.loadFromMemory(fontResource.fontData.data(), fontResource.fontData.size())) {
        std::cerr << "Failed to load font!" << std::endl;
    }
    else {
        std::cout << "Font loaded successfully!" << std::endl;
    }

    return fontResource;
}