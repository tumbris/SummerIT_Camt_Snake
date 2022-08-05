#pragma once

#include <Utility/SIC_TypeId.hpp>
#include <Utility/SIC_UID.hpp>

#include <memory>
#include <cassert>

class SIC_WorldModel;

// Abstract base class for assets
class SIC_Asset
{
public:
	virtual ~SIC_Asset() = default;

#if defined(DEBUG)
	const std::string& GetDebugName() const { return myUID.Str(); }
	SIC_UID myUID;
#endif //DEBUG
};

template <class T>
concept CT_Asset = std::is_base_of_v<SIC_Asset, T>;

// Abstract base class for asset containers
class SIC_AssetContainerBase
{
public:
	virtual ~SIC_AssetContainerBase() = default;

	template <CT_Asset AssetType> AssetType* Get()
	{
		return reinterpret_cast<AssetType*>(GetAssetInternal(SIC_TypeId::Get<AssetType>()));
	}

protected:
	virtual SIC_Asset* GetAssetInternal(const SIC_TypeId& asType) = 0;
};

template <CT_Asset AssetType>
struct SIC_AssetContainer : SIC_AssetContainerBase
{
	SIC_Asset* GetAssetInternal(const SIC_TypeId& asType) override { return asType.Is<AssetType>() ? &myAsset : nullptr; }
	AssetType myAsset;
};

using SIC_AssetHandle = std::unique_ptr<SIC_AssetContainerBase>;

//To implement for your asset types
template <CT_Asset AssetType>
struct SIC_AssetLoader
{
	SIC_AssetHandle operator()(const char*, SIC_WorldModel&)
	{
		assert("AssetType is not supported!");
		return nullptr; 
	}
};
