#include "InputSystem.h"
#include <SDL.h>
#include <iostream>

namespace digi {

	const uint32_t key_space = SDL_SCANCODE_SPACE;
	const uint32_t key_up = SDL_SCANCODE_W;
	const uint32_t key_down = SDL_SCANCODE_S;
	const uint32_t key_left = SDL_SCANCODE_A;
	const uint32_t key_right = SDL_SCANCODE_D;
	const uint32_t key_escape = SDL_SCANCODE_ESCAPE;

	const uint32_t button_left = 0;
	const uint32_t button_middle = 1;
	const uint32_t button_right = 2;

	void InputSystem::Initialize()
	{
		const uint8_t* keyBoardState = SDL_GetKeyboardState(&m_numKeys);

		m_keyboardState.resize(m_numKeys);
		std::copy(keyBoardState, keyBoardState + m_numKeys, m_keyboardState.begin());
		m_prevKeyboardState = m_keyboardState;
	}
	void InputSystem::Shutdown()
	{
		// Nothing... yet.
	}
	void InputSystem::Update()
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		//save previous state
		m_prevKeyboardState = m_keyboardState;
		//std::copy(m_keyboardState.begin(), m_keyboardState.end(), m_prevKeyboardState.begin());

		//Grab current state
		const uint8_t* keyBoardState = SDL_GetKeyboardState(nullptr);
		std::copy(keyBoardState, keyBoardState + m_numKeys, m_keyboardState.begin());

		m_prevMouseButtonState = m_mouseButtonState;
		int x, y;
		uint32_t buttons = SDL_GetMouseState(&x, &y);
		m_mousePosition = Vector2{ (float)x , (float)y };
		m_mouseButtonState[0] = buttons & SDL_BUTTON_LMASK; // buttons [0001] & [0RML] 
		m_mouseButtonState[1] = buttons & SDL_BUTTON_MMASK; // buttons [0010] & [0RML] 
		m_mouseButtonState[2] = buttons & SDL_BUTTON_RMASK; // buttons [0100] & [0RML] 
	}
	InputSystem::State InputSystem::GetKeyState(uint32_t key)
	{
		State keyState = State::Idle;

		bool keyDown = GetKeyDown(key);
		bool prevKeyDown = GetPreviousKeyDown(key);

		//std::cout << "CURR: " << keyDown << "\t PREV: " << prevKeyDown << std::endl;

		// set the keyState if keyDown (true) and prevKeyDown (true) 
		if (keyDown && prevKeyDown) {
			keyState = State::Held;
		}
		// set the keyState if keyDown (true) and prevKeyDown (false)
		else if (keyDown && (!prevKeyDown)) {
			keyState = State::Pressed;
		}
		// set the keyState if keyDown (false) and prevKeyDown (true) 
		else if ((!keyDown) && prevKeyDown) {
			keyState = State::Released;
		}
		// set the keyState if keyDown (false) and prevKeyDown (false) 
		// Not necessary, it's the default value.

		return keyState;
	}
	InputSystem::State InputSystem::GetButtonState(uint32_t button)
	{
		State keyState = State::Idle;

		bool buttonDown = GetButtonDown(button);
		bool prevButtonDown = GetPreviousButtonDown(button);

		// set the keyState if keyDown (true) and prevKeyDown (true) 
		if (buttonDown && prevButtonDown) {
			keyState = State::Held;
		}
		// set the keyState if keyDown (true) and prevKeyDown (false)
		else if (buttonDown && (!prevButtonDown)) {
			keyState = State::Pressed;
		}
		// set the keyState if keyDown (false) and prevKeyDown (true) 
		else if ((!buttonDown) && prevButtonDown) {
			keyState = State::Released;
		}

		return keyState;
	}
}
