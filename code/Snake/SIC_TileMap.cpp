#include <Snake/SIC_TileMap.hpp>

#include <Snake/Constants.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

#include <cassert>

SIC_TileMap::SIC_TileMap(const Config& config)
	: myConfig(config)
{
	myTiles.resize(config.myCountY, std::vector<Tile>(config.myCountX));
}

void SIC_TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Sprite templateSprite;
	for (size_t i = 0; i < myTiles.size(); i++)
	{
		for (size_t j = 0; j < myTiles[i].size(); j++)
		{
			Tile tile = myTiles[i][j];
			assert(tile.myTileIndex < myConfig.myTileSprites.size());
			templateSprite = myConfig.myTileSprites[tile.myTileIndex];

			templateSprite.setOrigin(myConfig.myTileSizeX / 2.f, myConfig.myTileSizeY / 2.f);

			float positionX = (float)j * myConfig.myTileSizeX + templateSprite.getOrigin().x;
			float positionY = (float)i * myConfig.myTileSizeY + templateSprite.getOrigin().y;
			templateSprite.setPosition(positionX, positionY);
			templateSprite.setRotation(size_t(tile.myDirection) * 90.f);

			target.draw(templateSprite, states);
		}
	}
}

std::vector<SIC_TileMap::Tile>& SIC_TileMap::operator[](size_t n)
{
	assert(n < myConfig.myCountY);
	return myTiles[n];
}

const std::vector<SIC_TileMap::Tile>& SIC_TileMap::operator[](size_t n) const
{
	assert(n < myConfig.myCountY);
	return myTiles[n];
}

void SIC_TileMap::Clear()
{
	for (auto& row : myTiles)
	{
		for (auto& tile : row)
			tile.myTileIndex = Constants::GameFieldTileMapping::Empty;
	}
}
