#pragma once

#include <Snake/Input.hpp>
#include <Snake/Assets/SIC_TileSet.hpp>
#include <Snake/Constants.hpp>
#include <Snake/SIC_TileMap.hpp>

#include <any>
#include <tuple>
#include <optional>

class SIC_WorldModel;
class SIC_ExecutionContext;
class SIC_TileMap;

class SIC_GameplaySystem
{
public:
	SIC_GameplaySystem(SIC_WorldModel& worldModel);
	~SIC_GameplaySystem();

	void Initialize();

	void Update(SIC_ExecutionContext& context);
private:
	// Input handling
	void SetupInputHandlers();
	void RemoveInputHandlers();
	static void HandleUpAction(std::any thisAny);
	static void HandleDownAction(std::any thisAny);
	static void HandleLeftAction(std::any thisAny);
	static void HandleRightAction(std::any thisAny);
	static void HandlePauseAction(std::any thisAny);
	static void HandleStartAction(std::any thisAny);
	static void HandleExitAction(std::any thisAny);

	SIC_InputAction::ID myUpActionHandlerId = SIC_InputAction::ourInvalidId;
	SIC_InputAction::ID myDownActionHandlerId = SIC_InputAction::ourInvalidId;
	SIC_InputAction::ID myLeftActionHandlerId = SIC_InputAction::ourInvalidId;
	SIC_InputAction::ID myRightActionHandlerId = SIC_InputAction::ourInvalidId;
	SIC_InputAction::ID myPauseActionHandlerId = SIC_InputAction::ourInvalidId;
	SIC_InputAction::ID myStartActionHandlerId = SIC_InputAction::ourInvalidId;
	SIC_InputAction::ID myExitActionHandlerId = SIC_InputAction::ourInvalidId;

	// Load
	bool LoadAssets();

	// Game loop
	void UpdateSnake(SIC_ExecutionContext& context);
	void CheckCollisions(SIC_ExecutionContext& context);
	void CheckBounds(SIC_ExecutionContext& context);
	void UpdateField(SIC_ExecutionContext& context);
	void ResetSnakeTimer();
	void SpawnApple();
	void GameOver();

private:
	SIC_WorldModel& myWorldModel;
	bool myShouldExit = false;

	// Assets
	SIC_TileSet* mySnakeBodyTileSet = nullptr;
	SIC_Texture* myAppleTexture = nullptr;
	SIC_Texture* myEmptyTileTexture = nullptr;

	// Map
	std::unique_ptr<SIC_TileMap> myField;
	SIC_TileMap::Config myFieldConfig;

	// Game
	enum class GameState
	{
		None,
		WaitingForStart,
		Playing
	} myGameState = GameState::WaitingForStart;

	enum SnakeDirection
	{
		Up = 0, 
		Right,
		Down,
		Left
	} mySnakeDirection = Right; // Default snake direction
	int mySnakeLength = Constants::DefaultSnakeLength;
	float mySnakeMoveTimer = Constants::SnakeMoveBaseTimeout;

	std::vector<std::tuple<int, int, SnakeDirection>> mySnake;
	std::optional<std::pair<size_t, size_t>> myApple;

private:
	bool CanSnakeChangeDirection(SnakeDirection newDirection) const;
	void ResetGame();
};