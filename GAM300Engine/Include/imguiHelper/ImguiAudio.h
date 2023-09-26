#ifndef IMGUI_AUDIO
#define IMGUI_AUDIO

#include "ImguiHelper.h"

namespace TDS
{
	class AudioImgui : public LevelEditorPanel
	{
	public:
		AudioImgui();

		void update();

	private:
		unsigned int AudioID;
	};
}

#endif