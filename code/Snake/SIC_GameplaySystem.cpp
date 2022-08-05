#include <Snake/SIC_GameplaySystem.hpp>

#include <Snake/SIC_TileMap.hpp>
#include <Snake/SIC_InputManager.hpp>
#include <Snake/SIC_AssetManager.hpp>
#include <Snake/SIC_WorldModel.hpp>
#include <Snake/SIC_ExecutionContext.hpp>

#include <random>
#include <cassert>

SIC_GameplaySystem::SIC_GameplaySystem(SIC_WorldModel& worldModel)
	: myWorldModel(worldModel)
{
	SetupInputHandlers();
}

SIC_GameplaySystem::~SIC_GameplaySystem()
{
	RemoveInputHandlers();
}

void SIC_GameplaySystem::Initialize()
{
	if (!LoadAssets())
	{
		assert(false);
		return;
	}

	myFieldConfig.myCountX = Constants::WindowSizeX / Constants::TileSize;
	myFieldConfig.myCountY = Constants::WindowSizeY / Constants::TileSize;
	myFieldConfig.myTileSizeX = Constants::TileSize;
	myFieldConfig.myTileSizeY = Constants::TileSize;

	myFieldConfig.myTileSprites.resize(Constants::GameFieldTileMapping::COUNT);
	{
		myFieldConfig.myTileSprites[Constants::GameFieldTileMapping::Empty].setTexture(*myEmptyTileTexture);

		myFieldConfig.myTileSprites[Constants::GameFieldTileMapping::SnakeHead].setTexture(mySnakeBodyTileSet->GetTile(Constants::SnakeTileIndex::Head));
		myFieldConfig.myTileSprites[Constants::GameFieldTileMapping::SnakeCorner].setTexture(mySnakeBodyTileSet->GetTile(Constants::SnakeTileIndex::Corner));
		myFieldConfig.myTileSprites[Constants::GameFieldTileMapping::SnakeCorner2].setTexture(mySnakeBodyTileSet->GetTile(Constants::SnakeTileIndex::Corner2));
		myFieldConfig.myTileSprites[Constants::GameFieldTileMapping::SnakeTail].setTexture(mySnakeBodyTileSet->GetTile(Constants::SnakeTileIndex::Tail));
		myFieldConfig.myTileSprites[Constants::GameFieldTileMapping::SnakeBody].setTexture(mySnakeBodyTileSet->GetTile(Constants::SnakeTileIndex::Body));

		myFieldConfig.myTileSprites[Constants::GameFieldTileMapping::Apple].setTexture(*myAppleTexture);
	}

	myField = std::make_unique<SIC_TileMap>(myFieldConfig);

	assert(Constants::DefaultSnakeLength < myFieldConfig.myCountX);
	mySnake.reserve(Constants::DefaultSnakeLength);
	for (size_t i = 1; i <= Constants::DefaultSnakeLength; i++)
		mySnake.push_back({ 0, int(Constants::DefaultSnakeLength - i) , Right });
}

void SIC_GameplaySystem::Update(SIC_ExecutionContext& context)
{
	switch (myGameState)
	{
	case GameState::WaitingForStart:
		UpdateField(context);
		break;
	case GameState::Playing:
		UpdateSnake(context);
		CheckCollisions(context);
		CheckBounds(context);
		UpdateField(context);
		break;
	default: break;
	}

	context.myWindow.draw(*myField);

	if (myShouldExit)
		context.myWindow.close();
}

void SIC_GameplaySystem::SetupInputHandlers()
{
	SIC_InputManager& inputManager = myWorldModel.GetInputManager();

	myUpActionHandlerId = inputManager.AddAction({ HandleUpAction, this, InputAction::Up, InputActionType::Pressed });
	myDownActionHandlerId = inputManager.AddAction({ HandleDownAction, this, InputAction::Down, InputActionType::Pressed });
	myLeftActionHandlerId = inputManager.AddAction({ HandleLeftAction, this, InputAction::Left, InputActionType::Pressed });
	myRightActionHandlerId = inputManager.AddAction({ HandleRightAction, this, InputAction::Right, InputActionType::Pressed });
	myPauseActionHandlerId = inputManager.AddAction({ HandlePauseAction, this, InputAction::Pause, InputActionType::Pressed });
	myStartActionHandlerId = inputManager.AddAction({ HandleStartAction, this, InputAction::Start, InputActionType::Pressed });
	myExitActionHandlerId = inputManager.AddAction({ HandleExitAction, this, InputAction::Exit, InputActionType::SystemEvent });
}

void SIC_GameplaySystem::RemoveInputHandlers()
{
	SIC_InputManager& inputManager = myWorldModel.GetInputManager();

	inputManager.RemoveAction(myUpActionHandlerId);
	inputManager.RemoveAction(myDownActionHandlerId);
	inputManager.RemoveAction(myLeftActionHandlerId);
	inputManager.RemoveAction(myRightActionHandlerId);
	inputManager.RemoveAction(myPauseActionHandlerId);
	inputManager.RemoveAction(myStartActionHandlerId);
	inputManager.RemoveAction(myExitActionHandlerId);
}

void SIC_GameplaySystem::HandleUpAction(std::any thisAny)
{
	SIC_GameplaySystem& localThis = *std::any_cast<SIC_GameplaySystem*>(thisAny);
	if (localThis.CanSnakeChangeDirection(Up))
		localThis.mySnakeDirection = Up;
}

void SIC_GameplaySystem::HandleDownAction(std::any thisAny)
{
	SIC_GameplaySystem& localThis = *std::any_cast<SIC_GameplaySystem*>(thisAny);
	if (localThis.CanSnakeChangeDirection(Down))
		localThis.mySnakeDirection = Down;
}

void SIC_GameplaySystem::HandleLeftAction(std::any thisAny)
{
	SIC_GameplaySystem& localThis = *std::any_cast<SIC_GameplaySystem*>(thisAny);
	if (localThis.CanSnakeChangeDirection(Left))
		localThis.mySnakeDirection = Left;
}

void SIC_GameplaySystem::HandleRightAction(std::any thisAny)
{
	SIC_GameplaySystem& localThis = *std::any_cast<SIC_GameplaySystem*>(thisAny);
	if (localThis.CanSnakeChangeDirection(Right))
		localThis.mySnakeDirection = Right;
}

void SIC_GameplaySystem::HandlePauseAction(std::any thisAny)
{
	SIC_GameplaySystem& localThis = *std::any_cast<SIC_GameplaySystem*>(thisAny);
}

void SIC_GameplaySystem::HandleStartAction(std::any thisAny)
{
	SIC_GameplaySystem& localThis = *std::any_cast<SIC_GameplaySystem*>(thisAny);
	localThis.myGameState = GameState::Playing;
	localThis.SpawnApple();
	localThis.mySnakeMoveTimer = -1; // So that snake moves right away
}

void SIC_GameplaySystem::HandleExitAction(std::any thisAny)
{
	SIC_GameplaySystem& localThis = *std::any_cast<SIC_GameplaySystem*>(thisAny);
	localThis.myShouldExit = true;
}

bool SIC_GameplaySystem::LoadAssets()
{
	if (SIC_Texture* texture = myWorldModel.GetAssetManager().GetAsset<SIC_Texture>(Constants::AppleTilePath, true))
		myAppleTexture = texture;

	if (SIC_Texture* texture = myWorldModel.GetAssetManager().GetAsset<SIC_Texture>(Constants::EmptyTilePath, true))
		myEmptyTileTexture = texture;

	if (SIC_TileSet* tileSet = myWorldModel.GetAssetManager().GetAsset<SIC_TileSet>(Constants::SnakeBodyTilesetPath, true))
	{
		mySnakeBodyTileSet = tileSet;
		mySnakeBodyTileSet->SetTileCount(Constants::SnakeTileCount);
		mySnakeBodyTileSet->SetTileSize(Constants::TileSize, Constants::TileSize);
		mySnakeBodyTileSet->UpdateTiles();
	}

	return myAppleTexture
		&& mySnakeBodyTileSet
		&& myEmptyTileTexture;
}

void SIC_GameplaySystem::UpdateSnake(SIC_ExecutionContext& context)
{
	assert(mySnake.size() >= Constants::MinSnakeLength);

	auto& [headX, headY, snakeDir] = mySnake.front();
	snakeDir = mySnakeDirection;

	if (mySnakeMoveTimer < 0)
	{
		// Move body
		for (size_t i = mySnake.size() - 1; i > 0; i--)
			mySnake[i] = mySnake[i - 1];

		//Move snake head
		switch (mySnakeDirection)
		{
		case Up: headX--; break;
		case Down: headX++; break;
		case Left: headY--; break;
		case Right: headY++; break;
		default: break;
		}

		ResetSnakeTimer();
	}
	else
		mySnakeMoveTimer -= context.myFrameTime;
}

void SIC_GameplaySystem::CheckCollisions(SIC_ExecutionContext& context)
{
	for (size_t i = 1; i < mySnake.size(); ++i)
	{
		auto [snakeX, snakeY, _1] = mySnake[i];
		auto [headX, headY, _2] = mySnake[0];
		if (snakeX == headX && snakeY == headY)
		{
			GameOver();
			return;
		}
	}

	if (myApple.has_value())
	{
		auto [snakeX, snakeY, _] = mySnake[0];
		auto [appleX, appleY] = myApple.value();

		if (snakeX == appleX && snakeY == appleY)
		{
			mySnake.push_back(mySnake.back());
			SpawnApple();
		}
	}
}

void SIC_GameplaySystem::CheckBounds(SIC_ExecutionContext& context)
{
	auto [snakeX, snakeY, _] = mySnake[0];

	if (snakeY >= myFieldConfig.myCountX || snakeY < 0 || snakeX >= myFieldConfig.myCountY || snakeX < 0)
	{
		GameOver();
	}
}

void SIC_GameplaySystem::UpdateField(SIC_ExecutionContext& context)
{
	SIC_TileMap& field = *myField;
	field.Clear();

	{ // Update directions
		// We need to calculate direction only for second segment
		auto& [snakeX, snakeY, snakeDir] = mySnake[1];
		const auto [nextX, nextY, _] = mySnake[0];
		const int diffX = nextX - snakeX;
		const int diffY = nextY - snakeY;
		if (diffX == 0)
		{
			if (diffY > 0) snakeDir = Right;
			else snakeDir = Left;
		}
		else if (diffY == 0)
		{
			if (diffX > 0) snakeDir = Down;
			else snakeDir = Up;
		}
	}
	{ // Update field
		// Head
		auto& headTile = field[std::get<0>(mySnake[0])][std::get<1>(mySnake[0])];
		headTile.myTileIndex = Constants::GameFieldTileMapping::SnakeHead;
		headTile.myDirection = static_cast<SIC_TileMap::Tile::Direction>(std::get<SnakeDirection>(mySnake[0]));

		//Body
		for (size_t i = 1; i < mySnake.size() - 1; i++)
		{
			auto [snakeX, snakeY, snakeDir] = mySnake[i];
			SnakeDirection nextSnakeDir = std::get<SnakeDirection>(mySnake[i + 1]);
			// Corner check
			if (snakeDir != nextSnakeDir)
			{
				if ((nextSnakeDir == Up && snakeDir == Right) ||
					(nextSnakeDir == Down && snakeDir == Left) ||
					(nextSnakeDir == Left && snakeDir == Up) ||
					(nextSnakeDir == Right && snakeDir == Down))
					field[snakeX][snakeY].myTileIndex = Constants::GameFieldTileMapping::SnakeCorner;
				else
					field[snakeX][snakeY].myTileIndex = Constants::GameFieldTileMapping::SnakeCorner2;

			}
			else
			{
				field[snakeX][snakeY].myTileIndex = Constants::GameFieldTileMapping::SnakeBody;
			}
			field[snakeX][snakeY].myDirection = static_cast<SIC_TileMap::Tile::Direction>(snakeDir);
		}

		//Tail
		auto& tailTile = field[std::get<0>(mySnake.back())][std::get<1>(mySnake.back())];
		tailTile.myTileIndex = Constants::GameFieldTileMapping::SnakeTail;
		tailTile.myDirection = static_cast<SIC_TileMap::Tile::Direction>(std::get<SnakeDirection>(mySnake.back()));

		// Apple
		if (myApple.has_value())
		{
			const auto [appleX, appleY] = myApple.value();
			auto& appleTile = field[appleX][appleY];
			appleTile.myTileIndex = Constants::GameFieldTileMapping::Apple;
			appleTile.myDirection = SIC_TileMap::Tile::Direction::Up; // Always Up for the apple 
		}
	}
}

void SIC_GameplaySystem::ResetSnakeTimer()
{
	const float score = float(mySnake.size()) - float(Constants::DefaultSnakeLength);
	const float speedIncreaseRate = std::powf(Constants::SnakeSpeedUpRate, score);

	mySnakeMoveTimer = std::max(Constants::SnakeMoveBaseTimeout * speedIncreaseRate, Constants::SnakeMoveMinTimouot);
}

void SIC_GameplaySystem::SpawnApple()
{
	const SIC_TileMap::Config& fieldConfig = myField->GetConfig();

	std::default_random_engine dre(std::random_device{}());
		
	std::uniform_int_distribution<size_t> uniformDistX(1, fieldConfig.myCountX - 1);
	std::uniform_int_distribution<size_t> uniformDistY(1, fieldConfig.myCountY - 1);

	myApple = std::make_pair(uniformDistY(dre), uniformDistX(dre));
	auto& [appleX, appleY] = myApple.value();

	while ((*myField)[appleX][appleY].myTileIndex != Constants::GameFieldTileMapping::Empty)
	{
		appleX = uniformDistY(dre);
		appleY = uniformDistX(dre);
	}
}

void SIC_GameplaySystem::GameOver()
{
	ResetGame();
}

bool SIC_GameplaySystem::CanSnakeChangeDirection(SnakeDirection newDirection) const
{
	SnakeDirection neckDirection = std::get<SnakeDirection>(mySnake[1]);

	auto checkDirection = [newDirection](SnakeDirection direction) -> bool
	{
		if (std::abs(int(newDirection) - int(direction)) == 2)
			return false;
		return true;
	};

	if (!checkDirection(neckDirection) || !checkDirection(mySnakeDirection))
		return false;
	return true;
}

void SIC_GameplaySystem::ResetGame()
{
	myApple.reset();
	mySnake.clear();
	for (size_t i = 1; i <= Constants::DefaultSnakeLength; i++)
		mySnake.push_back({ 0, int(Constants::DefaultSnakeLength - i) , Right });
	myField->Clear();
	myGameState = GameState::WaitingForStart;
	mySnakeDirection = Right;
}
