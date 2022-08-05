#pragma once

#include <Snake/Input.hpp>

#include <unordered_map>

class SIC_ExecutionContext;

class SIC_InputManager
{
public:
	
	SIC_InputAction::ID AddAction(SIC_InputAction&& action);
	bool RemoveAction(SIC_InputAction::ID id);

	void HandleSFInput(SIC_ExecutionContext& context);

private:
	static SIC_InputAction::ID ourInputActionIdCounter;

	std::unordered_map<SIC_InputAction::ID, SIC_InputAction> myActions;
};