#include <Snake/Assets/SIC_TileSet.hpp>

#include <Snake/SIC_WorldModel.hpp>
#include <Snake/SIC_FileManager.hpp>

SIC_AssetHandle SIC_AssetLoader<SIC_TileSet>::operator()(const char* assetPath, SIC_WorldModel& worldModel)
{
	auto assetContainer = std::make_unique<SIC_AssetContainer<SIC_TileSet>>();
	assetContainer->myAsset.loadFromStream(*(worldModel.GetFileManager().OpenFile(assetPath)));
	return assetContainer;
}

void SIC_TileSet::UpdateTiles()
{
	auto [imageX, imageY] = sf::Image::getSize();

	// Verify sizes
#if defined(DEBUG)
	{
		const size_t imageArea = imageX * imageY;
		const size_t tileArea = myTileCount * (myTileSizeX * myTileSizeY);
		assert(imageArea == tileArea && "Tilesheet mismatch");
	}
#endif //DEBUG

	for (size_t heigth = 0, i = 0; heigth < imageY; i++)
	{
		for (size_t width = 0, j = 0; width < imageX; j++)
		{
			sf::Texture& tile = myTileStorage.emplace_back();
			tile.loadFromImage(*this, { int(width), int(heigth), int(myTileSizeX), int(myTileSizeY) });
			width += myTileSizeX;
		}
		heigth += myTileSizeY;
	}
}
