#pragma once

namespace Constants
{
	// Window
	const static size_t WindowSizeX = 400;
	const static size_t WindowSizeY = 800;
	const static char* WindowTitle = "Summer IT Camp: Snake";
	
	// Tiles
	const static char* AppleTilePath = "apple.png";
	const static char* EmptyTilePath = "empty_tile.png";
	const static char* SnakeBodyTilesetPath = "snake_body_tileset.png";
	const static size_t SnakeTileCount = 5;

	namespace SnakeTileIndex
	{
		enum : size_t
		{
			Head = 0,
			Corner = 1,
			Tail = 2,
			Body = 3,
			Corner2 = 4
		};
	}
	
	namespace GameFieldTileMapping
	{
		enum : size_t
		{
			Empty = 0,
			SnakeHead = 1,
			SnakeCorner = 2,
			SnakeCorner2 = 3,
			SnakeTail = 4,
			SnakeBody = 5,
			Apple = 6,

			COUNT
		};
	}

	const static size_t TileSize = 40;

	// Game
	const static size_t DefaultSnakeLength = 3;
	const static size_t MinSnakeLength = 3;
	const static float SnakeMoveBaseTimeout = 0.7f; //Snake will move every SnakeMoveBaseTimeout seconds
	const static float SnakeMoveMinTimouot = 0.1f;
	const static float SnakeSpeedUpRate = 0.9f;
}