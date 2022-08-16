#pragma once
#include "../Math/Vector2.h"
#include <vector>
#include <array>
#include <cstdint>

namespace digi {

	class InputSystem {
		public:
			enum State {
				Idle, 
				Pressed, 
				Held, 
				Released
			};
		public:
			InputSystem() = default;
			~InputSystem() = default;

			void Initialize();
			void Shutdown();

			void Update();

			bool GetKeyDown(int key) { return m_keyboardState[key]; }
			bool GetPreviousKeyDown(int key) { return m_prevKeyboardState[key]; }
			State GetKeyState(uint32_t key);

			const Vector2& GetMousePosition() const { return m_mousePosition; }

			State GetButtonState(uint32_t button);
			bool GetButtonDown(uint32_t button) { return m_mouseButtonState[button]; }
			bool GetPreviousButtonDown(uint32_t button) { return m_prevMouseButtonState[button]; }
		
		private:
			int m_numKeys = 0;
			std::vector<uint8_t> m_keyboardState;
			std::vector<uint8_t> m_prevKeyboardState;

			Vector2 m_mousePosition;
			std::array<uint8_t, 3> m_mouseButtonState;
			std::array<uint8_t, 3> m_prevMouseButtonState;
	};

	extern const uint32_t key_space;
	extern const uint32_t key_up;
	extern const uint32_t key_down;
	extern const uint32_t key_left;
	extern const uint32_t key_right;
	extern const uint32_t key_escape;

	extern const uint32_t button_left;
	extern const uint32_t button_middle;
	extern const uint32_t button_right;
}