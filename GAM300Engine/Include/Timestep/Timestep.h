#ifndef TIMESTEP_H
#define TIMESTEP_H

#include "dotnet/ImportExport.h"

namespace TDS
{
class DLL_API TimeStep
{
public:
	
	static float GetDeltaTime() { return mDeltaTime; }
	static float GetFixedDeltaTime() { return mFixedTime; }
	static float GetFps() { return mFps; }
	static void CalculateDeltaTime();

private:
	// functions

private:
	// variables
	static float mDeltaTime;
	static float mFixedTime;
	static float mFps;
	static std::chrono::time_point<std::chrono::high_resolution_clock>InternalClock;

};


	
}




#endif // !TIMESTEP_H
