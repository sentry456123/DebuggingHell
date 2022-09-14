#include "fs.h"

std::string FileSystem::ReadFile(const char* filepath) noexcept
{
	std::ifstream file(filepath);
	if (!file) {
		std::cerr << "File " << filepath << " does not exist" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	std::ostringstream stream;
	stream << file.rdbuf();
	return stream.str();
}