#include <iostream>
#include "fmod.hpp"
#include <fmod_studio.hpp>

//#include "../header/AudioEngine.h"
int main()
{
	//AudioEngine audioeng;
	//audioeng.init();

	unsigned int x { 2 };
	FMOD::System* sys{};

	while (1)
	{
		//audioeng.update();
		std::cout << "Matthew: " << sys->getVersion(&x) << std::endl;
	}
}