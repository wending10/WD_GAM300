#ifndef IMGUI_SCENE
#define IMGUI_SCENE

#include "ImguiHelper.h"
#include "imguiHelper/ImguiHierarchy.h"
namespace TDS 
{
	class EditorScene : public LevelEditorPanel
	{
	public:
		EditorScene();

		void init();
		void update();
		void Resize();

		Vec2 get_scene_window_size();

		bool isFocus {true};
	private:
		int m_gizmoType = 7;
		bool m_gizmoActive = false;

		ImVec2 window_size;
	};
}

#endif // IMGUI_SCENE
