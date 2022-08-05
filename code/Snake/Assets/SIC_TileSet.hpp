#pragma once

#include <Snake/Assets/SIC_Texture.hpp>

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <vector>

class SIC_TileSet : public SIC_Asset, public sf::Image 
{
public:
	void SetTileCount(size_t count) { myTileCount = count; }
	void SetTileSize(size_t x, size_t y) { myTileSizeX = x; myTileSizeY = y; }

	size_t GetTileCount() const { return myTileCount; }
	std::pair<size_t, size_t> GetTileSize() const { return { myTileSizeX, myTileSizeY }; }

	void UpdateTiles();

	const SIC_Texture& GetTile(size_t n) const { return myTileStorage[n]; }

private:

	std::vector<SIC_Texture> myTileStorage;

	size_t myTileCount = 0;
	size_t myTileSizeX = 0;
	size_t myTileSizeY = 0;
};

template <>
struct SIC_AssetLoader<SIC_TileSet>
{
	SIC_AssetHandle operator()(const char* assetPath, SIC_WorldModel& worldModel);
};