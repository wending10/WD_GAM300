#include "Input.hxx"
using namespace System;
using namespace System::Runtime::InteropServices;

namespace ScriptAPI
{
	void Input::InputSetup()
	{
		AxisDictionary = gcnew System::Collections::Generic::Dictionary<System::String^, System::Tuple<uint32_t, uint32_t>^>();
		AxisDictionary->Add("Horizontal", gcnew System::Tuple<uint32_t, uint32_t>(TDS_D, TDS_A));
		AxisDictionary->Add("Vertical", gcnew System::Tuple<uint32_t, uint32_t>(TDS_W, TDS_S));
		AxisDictionary->Add("Mouse X", gcnew System::Tuple<uint32_t, uint32_t>(Keycode::M1, Keycode::M1));
		AxisDictionary->Add("Mouse Y", gcnew System::Tuple<uint32_t, uint32_t>(Keycode::M2, Keycode::M2));
	}

	float Input::GetAxisRaw(System::String^ code)
	{
		if (GetKeyDown(AxisDictionary[code]->Item1))
		{
			return 1.0f;
		}
		if (GetKeyDown(AxisDictionary[code]->Item2))
		{
			return -1.0f;
		}

		return 0.0f;
	}

	float Input::GetAxis(System::String^ code)
	{
		float AxisValue = 0.0f;
		float minValue = -1.0f;
		float maxValue = 1.0f;
		
		if (AxisDictionary[code]->Item1 >= TDS_MAX_KEYS)
		{
			if (code == "Mouse X") // X (may want to change)
			{
				float getMouseDifferenceX = GetMousePositionDifferenceX();
				if (getMouseDifferenceX > 0)
				{
					AxisValue += 0.05f;
				}
				else if (getMouseDifferenceX < 0)
				{
					AxisValue -= 0.05f;
				}
			}
			else if (code == "Mouse Y")// Y (may want to change)
			{
				float getMouseDifferenceY = GetMousePositionDifferenceY();
				if (getMouseDifferenceY > 0)
				{
					AxisValue += 0.05f;
				}
				else if (getMouseDifferenceY < 0)
				{
					AxisValue -= 0.05f;
				}
			}
		}
		else
		{
			if (GetKeyDown(AxisDictionary[code]->Item1))
			{
				AxisValue += 0.05f;
			}
		}

		if (AxisDictionary[code]->Item2 < TDS_MAX_KEYS)
		{
			if (GetKeyDown(AxisDictionary[code]->Item2))
			{
				AxisValue -= 0.05f;
			}
		}

		return std::clamp<float>(AxisValue, minValue, maxValue);
	}

	bool Input::GetKey(uint32_t keycode)
	{
		return TDS::Input::isKeyPressed(keycode);
	}

	bool Input::GetKeyDown(uint32_t keycode)
	{
		return TDS::Input::isKeyPressed(keycode);
	}

	bool Input::GetKeyUp(uint32_t keycode)
	{
		return TDS::Input::isKeyReleased(keycode);
	}

	bool Input::GetMouseButton(uint32_t button)
	{
		return TDS::Input::isMouseButtonPressed(button - Keycode::MAX_KEYS);
	}

	bool Input::GetMouseButtonDown(uint32_t button)
	{
		return TDS::Input::isMouseButtonPressed(button - Keycode::MAX_KEYS);
	}

	bool Input::GetMouseButtonUp(uint32_t button)
	{
		return TDS::Input::isMouseButtonReleased(button - Keycode::MAX_KEYS);
	}

	float Input::GetMousePositionDifferenceX()
	{
		return TDS::Input::getMousePosition().x - mousePositionX;
	}
	float Input::GetMousePositionDifferenceY()
	{
		return mousePositionY - TDS::Input::getMousePosition().y;
	}

	void Input::InputUpdate()
	{
		mousePositionX = TDS::Input::getMousePosition().x;
		mousePositionY = TDS::Input::getMousePosition().y;
	}
}
