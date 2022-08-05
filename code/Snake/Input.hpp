#pragma once

#include <cstdint>
#include <any>

enum class InputAction
{
	Invalid,


	Right,
	Left,
	Up,
	Down,
	Start,
	Pause,
	Exit
};

enum class InputActionType
{
	Invalid,


	Pressed,
	Released,
	SystemEvent
};

struct SIC_InputAction
{
	using InputActionCallback = void(*)(std::any /*User data*/);
	using ID = std::uint32_t;

	const static ID ourInvalidId = -1;

	InputActionCallback myHandler = nullptr;
	std::any myUserData;

	InputAction myAction;
	InputActionType myInputType;
};