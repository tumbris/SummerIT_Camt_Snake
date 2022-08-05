#pragma once

#include <Snake/SIC_Asset.hpp>

#include <Utility/SIC_UID.hpp>

#include <unordered_map>
#include <memory>

class SIC_WorldModel;

class SIC_AssetManager
{
public:
	SIC_AssetManager(SIC_WorldModel& worldModel);

	template <CT_Asset AssetType>
	AssetType* GetAsset(const char* assetPath, bool loadOnFailure = false)
	{
		auto assetIt = myAssetStorage.find(assetPath);
		if (assetIt == myAssetStorage.end())
		{
			if (!loadOnFailure)
				return nullptr;

			SIC_AssetHandle& assetHandle = myAssetStorage[assetPath] = SIC_AssetLoader<AssetType>{}(assetPath, myWorldModel);
			return assetHandle->Get<AssetType>();
		}
		return assetIt->second->Get<AssetType>();
	}
private:
	std::unordered_map<SIC_UID, SIC_AssetHandle> myAssetStorage;

	SIC_WorldModel& myWorldModel;
};