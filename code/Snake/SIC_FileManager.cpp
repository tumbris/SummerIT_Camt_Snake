#include <Snake/SIC_FileManager.hpp>

std::unique_ptr<sf::FileInputStream> SIC_FileManager::OpenFile(const char* filename)
{
	auto file = std::make_unique<sf::FileInputStream>();
	file->open(CreatePhysicalPath(filename).generic_string());
	return file;
}

std::filesystem::path SIC_FileManager::CreatePhysicalPath(const std::filesystem::path& path)
{
	return DATA_ROOT / path;
}
