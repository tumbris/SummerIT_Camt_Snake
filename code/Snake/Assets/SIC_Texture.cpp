#include <Snake/Assets/SIC_Texture.hpp>

#include <Snake/SIC_WorldModel.hpp>
#include <Snake/SIC_FileManager.hpp>

SIC_AssetHandle SIC_AssetLoader<SIC_Texture>::operator()(const char* assetPath, SIC_WorldModel& worldModel)
{
	auto assetContainer = std::make_unique<SIC_AssetContainer<SIC_Texture>>();
	assetContainer->myAsset.loadFromStream(*(worldModel.GetFileManager().OpenFile(assetPath)));
	return assetContainer;
}