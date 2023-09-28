#include "Timestep/Timestep.h"

namespace TDS
{	
	float TimeStep::mDeltaTime = 0.0f;
	float TimeStep::mFixedTime = 0.0166666f;
	float TimeStep::mFps = 0.0f;
	std::chrono::time_point<std::chrono::high_resolution_clock> TimeStep::InternalClock = std::chrono::high_resolution_clock::now();

	void TimeStep::CalculateDeltaTime()
	{
		auto  Now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> ElapsedSeconds = Now - InternalClock;
		mDeltaTime = ElapsedSeconds.count();
		mFps = 1.0f / mDeltaTime;
		InternalClock = Now;
	}


	
}
