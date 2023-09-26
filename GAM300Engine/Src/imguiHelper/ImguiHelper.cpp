#include "ImguiHelper/ImguiHelper.h"
#include "ImguiHelper/ImguiHierarchy.h"
#include "ImguiHelper/ImguiProperties.h"
#include "ImguiHelper/ImguiAssetBrowser.h"
#include "ImguiHelper/ImguiSceneBrowser.h"

#include "ImguiHelper/ImguiFunctionHelper.h"

namespace TDS
{
	// LevelEditorManager ============================================================================================
	std::unique_ptr<LevelEditorManager> LevelEditorManager::m_instance;

	std::unique_ptr<LevelEditorManager>& LevelEditorManager::GetInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = std::make_unique<LevelEditorManager>();

			m_instance->panels[PanelTypes::HIERARCHY] = std::make_shared<Hierarchy>();
			m_instance->panels[PanelTypes::PROPERTIES] = std::make_shared<Properties>();
			m_instance->panels[PanelTypes::ASSETBROWSER] = std::make_shared<AssetBrowser>();
			m_instance->panels[PanelTypes::SCENEBROWSER] = std::make_shared<SceneBrowser>();
		}
		return m_instance;
	}

	// imguiHelper ===================================================================================================
	void imguiHelper::InitializeImgui(ImGui_ImplVulkan_InitInfo initinfo, VkRenderPass RenderPass, void* inHwnd)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io{ ImGui::GetIO() };
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
		ImGui::StyleColorsDark();
		ImGui_ImplVulkan_Init(&initinfo, RenderPass);
		ImGui_ImplWin32_Init(inHwnd);
	}

	void imguiHelper::ImguiCreateFont(VkCommandBuffer SingleUseCommandBuffer)
	{
		ImGui_ImplVulkan_CreateFontsTexture(SingleUseCommandBuffer);
	}

	void imguiHelper::Update()
	{
		ImGui_ImplVulkan_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		// Docking 
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
			ImGuiWindowFlags_NoBackground;

		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		ImGui::Begin("DockSpace", 0, window_flags);

		ImGui::PopStyleVar(3);

		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

		ImGui::End();

		// Panels
		for (auto currentPanel : LevelEditorManager::GetInstance()->panels)
		{
			//ImGui::GetStyle().WindowPadding = currentPanel.second->windowPadding;

			if (ImGui::Begin(currentPanel.second->panelTitle.c_str(), (bool*)0, currentPanel.second->flags))
			{
				if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
				{
					currentPanel.second->rightClick = true;
				}
				else
				{
					currentPanel.second->rightClick = false;
				}

				currentPanel.second->update();
			}
			ImGui::End();
		}
	}

	void imguiHelper::Draw(VkCommandBuffer FCB)
	{
		ImGuiIO& io{ ImGui::GetIO() };

		if (const ImGuiViewport* pViewPort{ ImGui::GetMainViewport() }; pViewPort != nullptr)
		{
			io.DisplaySize = pViewPort->Size;
		}
		ImGui::Render();
		ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), FCB);
	}

	void imguiHelper::Exit()
	{
		ImGui_ImplVulkan_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}


	void ImguiTextInput(std::string variableName, std::string& textVariable)
	{
		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text(variableName.c_str());

		ImGui::TableNextColumn();
		char temp[100];
		strcpy_s(temp, textVariable.c_str());
		ImGui::InputText(("##" + variableName).c_str(), temp, 100);
		textVariable = std::string(temp);
	}

	void ImguiBoolInput(std::string variableName, bool& boolVariable)
	{
		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text(variableName.c_str());

		ImGui::TableNextColumn();
		ImGui::Checkbox(("##" + variableName).c_str(), &boolVariable);
	}

	void ImguiIntInput(std::string variableName, int& intVariable, float speed, float min, float max)
	{
		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text(variableName.c_str());

		ImGui::TableNextColumn();
		if (max > 0)
		{
			ImGui::DragInt(("##" + variableName).c_str(), &intVariable, speed, min);
		}
		else
		{
			ImGui::DragInt(("##" + variableName).c_str(), &intVariable, speed, min, max);
		}
	}

	void ImguiFloatInput(std::string variableName, float& floatVariable, float speed, float min, float max)
	{
		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text(variableName.c_str());

		ImGui::TableNextColumn();
		ImGui::DragFloat(("##" + variableName).c_str(), &floatVariable, speed, min, max);
	}

	void ImguiVec2Input(std::string variableName, Vec2& Vec2Variable)
	{
		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text(variableName.c_str());

		ImGui::TableNextColumn();
		float temp[2]{ Vec2Variable.x, Vec2Variable.y };
		ImGui::DragFloat2(("##" + variableName).c_str(), temp, 1.0f);
		Vec2Variable.x = temp[0];
		Vec2Variable.y = temp[1];
	}

	void ImguiVec3Input(std::string variableName, Vec3& Vec3Variable)
	{
		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text(variableName.c_str());

		ImGui::TableNextColumn();
		float temp[3]{ Vec3Variable.x, Vec3Variable.y, Vec3Variable.z };
		ImGui::DragFloat3(("##" + variableName).c_str(), temp, 1.0f);
		Vec3Variable.x = temp[0];
		Vec3Variable.y = temp[1];
		Vec3Variable.z = temp[2];
	}

}