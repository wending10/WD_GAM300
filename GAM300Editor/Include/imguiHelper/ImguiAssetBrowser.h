#ifndef IMGUI_ASSET_BROWSER
#define IMGUI_ASSET_BROWSER

#include "ImguiHelper.h"
#include "ImguiAudio.h"

namespace TDS 
{
	class AssetBrowser : public LevelEditorPanel
	{
	public:
		AssetBrowser();
		void getFileNameFromPath(const char* full_path, std::string* path, std::string* file, std::string* fileWithExtension, std::string* extension) const;
		void init() {}
		void update();
		static inline std::filesystem::path m_curr_path;
	private:
		float thumbnail_size = 60;
		float padding = 10.f;
		std::string path1;
		std::string selectedpath;
		AudioImgui audimg;
	};
}

#endif // IMGUI_ASSET_BROWSER
