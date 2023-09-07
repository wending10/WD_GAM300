#pragma warning(disable : 28251)

#include <iostream>
#include <filesystem>
#include "application.h"
#include "Include/fmod/AudioEngine.h"


#if _DEBUG
#pragma comment( linker, "/subsystem:console" )
void audiotest(); //Forward Declaration

int main(int argc, const char** argv) {
    
	audiotest();
	
	return WinMain(GetModuleHandle(NULL), NULL, GetCommandLineA(), 0);
}
#else
#pragma comment( linker, "/subsystem:windows" )
#endif



TDS::Application* g_Application {nullptr};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    
    const wchar_t classname[] = L"TDSWindowClass"; //class name

    g_Application = new TDS::Application(hInstance,nCmdShow,classname);
    g_Application->Initialize();
    g_Application->Update();
    g_Application->~Application();

    delete g_Application;

    return 0;
}

void audiotest()
{
	AudioEngine audioeng;

	unsigned int x { 2 };
	FMOD::System* sys{};
	bool check{ false };

	int i{ 1 }, channels{ 0 };

	audioeng.init();

	SoundInfo test_track{ "../assets/audioFiles/Songs/test.flac" };
	test_track.setVolume(80.f);
	test_track.set3DCoords(-2.f, 0.f, 1.f);

	audioeng.loadSound(test_track);
	audioeng.playSound(test_track);

	/*audioeng.loadFMODStudioEvent("testing phase");
	audioeng.playEvent("testing phase");*/
	std::cout << "Check loaded: " << test_track.isLoaded() << std::endl;
	std::cout << "Volume of track: " << test_track.getVolume() << std::endl;

	while (i)
	{
		audioeng.update();


		//std::cout << audioeng.soundIsPlaying(test_track) << std::endl;
		
		//++i;
	}

	audioeng.deactivate();
}