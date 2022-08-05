#include <Snake/SIC_WorldModel.hpp>

#include <Snake/SIC_FileManager.hpp>
#include <Snake/SIC_AssetManager.hpp>
#include <Snake/SIC_GameplaySystem.hpp>
#include <Snake/SIC_InputManager.hpp>

SIC_WorldModel::SIC_WorldModel()
{
    myFileManager = std::make_unique<SIC_FileManager>();
    myAssetManager = std::make_unique<SIC_AssetManager>(*this);
    myInputManager = std::make_unique<SIC_InputManager>();



    myGameplaySystem = std::make_unique<SIC_GameplaySystem>(*this);
}

SIC_WorldModel::~SIC_WorldModel() = default;

void SIC_WorldModel::Initialize()
{
    myGameplaySystem->Initialize();
}

void SIC_WorldModel::Update(SIC_ExecutionContext& context)
{
    myInputManager->HandleSFInput(context);
    myGameplaySystem->Update(context);
}

SIC_FileManager& SIC_WorldModel::GetFileManager()
{
    return *myFileManager;
}

const SIC_FileManager& SIC_WorldModel::GetFileManager() const
{
    return *myFileManager;
}

SIC_AssetManager& SIC_WorldModel::GetAssetManager()
{
    return *myAssetManager;
}

const SIC_AssetManager& SIC_WorldModel::GetAssetManager() const
{
    return *myAssetManager;
}

SIC_GameplaySystem& SIC_WorldModel::GetGameplaySystem()
{
    return *myGameplaySystem;
}

const SIC_GameplaySystem& SIC_WorldModel::GetGameplaySystem() const
{
    return *myGameplaySystem;
}

SIC_InputManager& SIC_WorldModel::GetInputManager()
{
    return *myInputManager;
}

const SIC_InputManager& SIC_WorldModel::GetInputManager() const
{
    return *myInputManager;
}
