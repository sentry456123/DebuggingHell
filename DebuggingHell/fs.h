#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

class FileSystem
{

public:

	static std::string ReadFile(const char* filepath) noexcept;

};

