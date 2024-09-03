#include "resource_handler.hpp"
#include "zip_file.hpp"

bool resources_loaded = false;
std::vector<unsigned char> resource_vector(embedded_resources, embedded_resources + embedded_resources_len);
miniz_cpp::zip_file resource_file = miniz_cpp::zip_file(resource_vector);;

// Debug print filenames
void debug_resources()
{
	for (const auto& name : resource_file.infolist()) {
		std::cout << "Collecting resource: " << name.filename << std::endl;
	}
}

std::vector<unsigned char> get_resource_data(std::string path) 
{

	if (!resource_file.has_file(path))
	{
		throw std::runtime_error("ERROR: that resource: " + path + " doesn't exists. :/");
	}

	std::string resource_data_string = resource_file.read(path);
	std::vector<unsigned char> resource_data(resource_data_string.begin(), resource_data_string.end());
	return resource_data;
}