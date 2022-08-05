#pragma once

#include <SFML/System/FileInputStream.hpp>

#include <filesystem>
#include <memory>

class SIC_FileManager
{
public:
	std::unique_ptr<sf::FileInputStream> OpenFile(const char* filename);

private:
	static std::filesystem::path CreatePhysicalPath(const std::filesystem::path&);
};