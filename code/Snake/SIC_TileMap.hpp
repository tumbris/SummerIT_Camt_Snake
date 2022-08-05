#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <vector>

class SIC_TileMap : public sf::Drawable, public sf::Transformable
{
public:
	struct Config
	{
		size_t myCountX = 0;
		size_t myCountY = 0;
		size_t myTileSizeX = 0;
		size_t myTileSizeY = 0;

		std::vector<sf::Sprite> myTileSprites;
	};

	struct Tile
	{
		enum Direction
		{
			Up = 0,
			Right,
			Down,
			Left
		} myDirection = Up;
		size_t myTileIndex = 0;

	};

	SIC_TileMap(const Config& config);

	std::vector<Tile>& operator[](size_t n);
	const std::vector<Tile>& operator[](size_t n) const;

	const Config& GetConfig() const { return myConfig; }

	void Clear();

private:
	const Config myConfig;
	std::vector<std::vector<Tile>> myTiles;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};