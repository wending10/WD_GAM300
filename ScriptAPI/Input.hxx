#pragma once
#include "IncludeFromEngine.hxx"
#include "../GAM300Engine/Include/Input/Input.h"
#include <algorithm>

#define Mouse_X TDS::Input::getMousePosition()->x
#define Mouse_Y TDS::Input::getMousePosition()->y


namespace ScriptAPI
{
    /*public enum class Keys : uint32_t
    {
        Key_A = TDS_A,
        Key_W = TDS_W,
        Key_S = TDS_S,
        Key_D = TDS_D
    };*/

    public ref class Input
    {
    public:
        Input();
        static float GetAxisRaw(System::String^ code);
        static float GetAxis(System::String^ code);
        static bool GetKey(uint32_t keycode);
        static bool GetKeyDown(uint32_t keycode);
        static bool GetKeyUp(uint32_t keycode);
        static bool GetMouseButton(uint32_t button);
        static bool GetMouseButtonUp(uint32_t button);
        static bool GetMouseButtonDown(uint32_t button);

        static uint32_t Key_W = TDS_W;
        static uint32_t Key_A = TDS_A;
        static uint32_t Key_D = TDS_D;
        static uint32_t Key_S = TDS_S;

    private:
        static System::Collections::Generic::Dictionary<System::String^, System::Tuple<uint32_t, uint32_t>^>^ AxisDictionary;
    };
}