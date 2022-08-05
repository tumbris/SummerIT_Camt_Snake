#pragma once

#include <Snake/Input.hpp>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

namespace InputMapper
{
	InputActionType MapInputActionType(sf::Event::EventType eventType)
	{
		switch (eventType)
		{
		case sf::Event::KeyPressed: return InputActionType::Pressed;
		case sf::Event::KeyReleased: return InputActionType::Released;
			// System events
		case sf::Event::Closed:
			return InputActionType::SystemEvent;

		default: return InputActionType::Invalid;
		}
	}

	InputAction MapInputAction(sf::Event event)
	{
		if (MapInputActionType(event.type) == InputActionType::Invalid)
			return InputAction::Invalid;

		// Mapping SFML input to SIC input action
		// System events
		if (event.type == sf::Event::Closed) return InputAction::Exit;

		// Game actions
		switch (event.key.code)
		{
		case sf::Keyboard::W: return InputAction::Up;
		case sf::Keyboard::A: return InputAction::Left;
		case sf::Keyboard::D: return InputAction::Right;
		case sf::Keyboard::S: return InputAction::Down;
		case sf::Keyboard::Space: return InputAction::Start;
		case sf::Keyboard::Escape: return InputAction::Pause;
		default: break;
		}

		return InputAction::Invalid;
	}
}