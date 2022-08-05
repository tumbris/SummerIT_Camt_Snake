#include <Snake/SIC_InputManager.hpp>
#include <Snake/SIC_ExecutionContext.hpp>

#include <Snake/Input/SF_Input.hpp>

#include <SFML/Window/Event.hpp>

SIC_InputAction::ID SIC_InputManager::ourInputActionIdCounter = 0;

SIC_InputAction::ID SIC_InputManager::AddAction(SIC_InputAction&& action)
{
	myActions[ourInputActionIdCounter] = std::move(action);
	return ourInputActionIdCounter++;
}

bool SIC_InputManager::RemoveAction(SIC_InputAction::ID id)
{
	if (!myActions.contains(id)) return false;

	myActions.erase(id);
	return true;
}

void SIC_InputManager::HandleSFInput(SIC_ExecutionContext& context)
{
	sf::Event event;
	while (context.myWindow.pollEvent(event))
	{
		for (auto& [_, inputAction] : myActions)
		{
			if (inputAction.myHandler == nullptr)
				continue;

			if (inputAction.myInputType != InputMapper::MapInputActionType(event.type))
				continue;

			if (inputAction.myAction != InputMapper::MapInputAction(event))
				continue;

			inputAction.myHandler(inputAction.myUserData);
		}
	}
}
