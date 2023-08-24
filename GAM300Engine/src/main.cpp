#include <iostream>

#include "../header/AudioEngine.h"

int main()
{
	AudioEngine audioeng;

	unsigned int x { 2 };
	FMOD::System* sys{};
	FMOD::Studio::System* sys2{};
	bool check{ false };

	int i{ 1 }, channels{ 0 };

	audioeng.init();

	SoundInfo test_track{ "../GAM300Game/Assets/AudioFiles/Songs/test2.flac" };
	test_track.setVolume(80.f);

	audioeng.loadSound(test_track);
	audioeng.playSound(test_track);

	/*audioeng.loadFMODStudioEvent("testing phase");
	audioeng.playEvent("testing phase");*/

	while (i)
	{
		audioeng.update();

		//std::cout << "Volume of track: " << test_track.getVolume() << std::endl;
		std::cout << "Check loaded: " << test_track.isLoaded() << std::endl;

		//std::cout << audioeng.soundIsPlaying(test_track) << std::endl;

		//std::cout << "Matthew: " << sys->getVersion(&x) << std::endl;
		//++i;
	}

	audioeng.deactivate();
}