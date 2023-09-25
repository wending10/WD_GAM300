#ifndef IMGUI_ASSET_BROWSER
#define IMGUI_ASSET_BROWSER

#include "ImguiHelper.h"

namespace TDS 
{
	class AssetBrowser : public LevelEditorPanel
	{
	public:
		AssetBrowser();

		void update();

	private:
		float thumbnail_size = 80;
		float padding = 10.f;
		std::string path1;
		std::string selectedpath;
		std::filesystem::path m_curr_path;
	};
}

#endif // IMGUI_ASSET_BROWSER
