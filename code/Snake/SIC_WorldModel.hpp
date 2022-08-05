#pragma once

#include <memory>

class SIC_FileManager;
class SIC_AssetManager;
class SIC_GameplaySystem;
class SIC_InputManager;

class SIC_ExecutionContext;

class SIC_WorldModel
{
public:
	SIC_WorldModel();
	~SIC_WorldModel();

	void Initialize();
	void Update(SIC_ExecutionContext& context);

	SIC_WorldModel(SIC_WorldModel&&) = default;

	SIC_FileManager& GetFileManager();
	const SIC_FileManager& GetFileManager() const;

	SIC_AssetManager& GetAssetManager();
	const SIC_AssetManager& GetAssetManager() const;

	SIC_GameplaySystem& GetGameplaySystem();
	const SIC_GameplaySystem& GetGameplaySystem() const;

	SIC_InputManager& GetInputManager();
	const SIC_InputManager& GetInputManager() const;

private:
	// ORDER MATTERS!!

	std::unique_ptr<SIC_FileManager> myFileManager;
	std::unique_ptr<SIC_AssetManager> myAssetManager;
	std::unique_ptr<SIC_InputManager> myInputManager;
	std::unique_ptr<SIC_GameplaySystem> myGameplaySystem;
};