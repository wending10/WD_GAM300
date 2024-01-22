#include "../Input/InputSystem.h"
#include <Windows.h>


InputSystem::InputSystem() : m_KeyDelayTimer{0.25f}, m_KeyRepeatTimer{0.01f}, m_Keypressed{false}
{
	
}


InputSystem::~InputSystem()
{
}

void InputSystem::update()
{
	if (::GetKeyboardState(m_keys_state))
	{
		for (unsigned int i = 0; i < 256; i++)
		{
			// KEY IS DOWN
			if ((m_keys_state[i] & 0x80) && m_keys_state[i] != m_old_keys_state[i])
			{
				std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();
				while (it != m_set_listeners.end())
				{
					(*it)->onKeyPressed(i);
					++it;
				}
				m_KeyDelayTimer = 0.25f;
			}
			else if ((m_keys_state[i] & 0x80) && m_keys_state[i] == m_old_keys_state[i])
			{
				m_KeyDelayTimer -= TDS::TimeStep::GetDeltaTime();
				std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();
				if (m_KeyDelayTimer <= 0.0f)
				{
					while (it != m_set_listeners.end())
					{
						(*it)->onKeyDown(i);
						++it;
					}
				}
			}
			else // KEY IS UP
			{
				if (m_keys_state[i] != m_old_keys_state[i])
				{
					std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

					while (it != m_set_listeners.end())
					{
						(*it)->onKeyUp(i);
						++it;
					}
				}
			}

		}
		// store current keys state to old keys state buffer
		::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
	}
}

void InputSystem::addListener(InputListener* listener)
{
	m_set_listeners.insert(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
	m_set_listeners.erase(listener);
}

InputSystem* InputSystem::get()
{
	static InputSystem system;
	return &system;
}