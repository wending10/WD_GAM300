#pragma warning(disable : 28251)

//reduce code from windows.h 
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include <Windows.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#if _DEBUG
#pragma comment( linker, "/subsystem:console" )
int main(int argc, const char** argv) {
    return WinMain(GetModuleHandle(NULL), NULL, GetCommandLineA(), SW_SHOWDEFAULT);
}
#else
#pragma comment( linker, "/subsystem:windows" )
#endif


#include "application.h"

TDS::Application* g_Application {0};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    
    const wchar_t classname[] = L"TDSWindowClass"; //class name

    g_Application = new TDS::Application(hInstance,nCmdShow,classname);
    g_Application->Initialize();
    g_Application->Update();
    delete g_Application;

    return 0;
}
