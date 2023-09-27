#include "imguiHelper/ImguiHierarchy.h"

namespace TDS
{
	Hierarchy::Hierarchy()
	{
		selectedEntity = 0;
		//selectedFolder = -1;
		//renameCheck = false;

		flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse;
		panelTitle = "Hierarchy";
		windowPadding = ImVec2(0.f, 0.f);

		//insertEntities();
	}

	void Hierarchy::update()
	{
		if (ImGui::BeginMenuBar())
		{
			// Add entity (make it a menu item if there are prefabs)
			if (ImGui::BeginMenu("+ v"))
			{
				if (ImGui::MenuItem("Empty"))
				{
					Entity newEntity;
					newEntity.add<NameTag>();
					newEntity.add<Transform>();
					selectedEntity = newEntity.getID();
				}
				if (ImGui::MenuItem("Square"))
				{
					// Add Sprite or smth to render a square
					Entity newEntity;
					newEntity.add<NameTag>();
					newEntity.add<Transform>();
					selectedEntity = newEntity.getID();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGuiTreeNodeFlags nodeFlags =
			ImGuiTreeNodeFlags_DefaultOpen |
			ImGuiTreeNodeFlags_FramePadding |
			ImGuiTreeNodeFlags_SpanAvailWidth |
			ImGuiTreeNodeFlags_SpanFullWidth;

		if (ImGui::TreeNodeEx(SceneManager::GetInstance()->getCurrentScene().c_str(), nodeFlags))
		{
			for (auto entityID : ECS::getEntities())
			{
				if (NameTag* nameTagComponent = ECS::getComponent<NameTag>(entityID))
				{
					bool itemHovered = false;

					ImGui::PushID(entityID);

					bool selectable = ImGui::Selectable(nameTagComponent->GetNameTag().c_str(), selectedEntity == entityID);
					if (ImGui::IsItemHovered())
					{
						itemHovered = true;
					}
					if (selectable)
					{
						selectedEntity = entityID;
					}

					if (ImGui::BeginPopupContextItem("entityPopup"))
					{
						if (ImGui::Selectable("Remove Entity"))
						{
							ECS::removeEntity(selectedEntity);
							selectedEntity = 0;
						}

						ImGui::EndPopup();
					}

					if (rightClick && itemHovered)
					{
						selectedEntity = entityID;
						ImGui::OpenPopup("componentsPopup");
					}

					ImGui::PopID();
				}
			}
			ImGui::TreePop();
		}
	}
}