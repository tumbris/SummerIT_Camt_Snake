#pragma once

#include <Snake/SIC_Asset.hpp>
#include <SFML/Graphics/Texture.hpp>

class SIC_Texture : public SIC_Asset, public sf::Texture {};

template <>
struct SIC_AssetLoader<SIC_Texture>
{
	SIC_AssetHandle operator()(const char* assetPath, SIC_WorldModel& worldModel);
};