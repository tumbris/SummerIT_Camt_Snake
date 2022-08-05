#pragma once

#include <Snake/SIC_WorldModel.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

class SIC_WorldModel;

class SIC_ExecutionContext
{
public:
	static std::unique_ptr<SIC_ExecutionContext> PrepareContext();

	SIC_WorldModel myWorldModel;
	sf::RenderWindow myWindow;
	float myFrameTime = 0;

	void Initialize();
	void Update();
	bool ShouldUpdate() const;

private:
	SIC_ExecutionContext() = default;

	sf::Clock myFrameClock;
};