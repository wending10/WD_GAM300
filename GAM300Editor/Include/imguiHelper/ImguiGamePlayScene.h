#ifndef IMGUI_GAMEPLAYSCENE
#define IMGUI_GAMEPLAYSCENE

#include "ImguiHelper.h"
#include "imguiHelper/ImguiHierarchy.h"
namespace TDS
{
	class GamePlayScene : public LevelEditorPanel
	{
	public:
		GamePlayScene();

		void init();
		void update();
		void Resize();

		Vec2 get_scene_window_size();

		bool isFocus{ false };
	private:
		VkDescriptorSet m_GamePlayDesc{};

		ImVec2 window_size;
		ImVec2 window_pos;

		bool exit_cursor;
		BOOL show_cursor;
	};
}

#endif // IMGUI_GAMEPLAYSCENE
