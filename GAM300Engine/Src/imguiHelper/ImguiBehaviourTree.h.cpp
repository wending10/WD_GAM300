#include "imguiHelper/ImguiBehaviourTree.h"

namespace TDS
{
	BehaviourTree::BehaviourTree()
	{
		flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse;
		panelTitle = "Scene Browser";
		windowPadding = ImVec2(10.f, 10.f);
	}

	void BehaviourTree::update()
	{
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
				if (ImGui::MenuItem("New")) 
				{
				}
				if (ImGui::MenuItem("Save")) 
				{
				}
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
	}
}