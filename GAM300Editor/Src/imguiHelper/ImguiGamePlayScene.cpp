#include "imguiHelper/ImguiGamePlayScene.h"
#include "Rendering/GraphicsManager.h"
#include "Rendering/RenderTarget.h"


//static float TDS::TDSCamera::length_x, TDS::TDSCamera::length_y;

TDS::GamePlayScene::GamePlayScene()
{
	flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse;
	panelTitle = "GamePlayScene";
	windowPadding = ImVec2(0.f, 0.f);

}

void TDS::GamePlayScene::init()
{

	m_GamePlayDesc = ImGui_ImplVulkan_AddTexture(GraphicsManager::getInstance().getFinalImage().getSampler(), GraphicsManager::getInstance().getFinalImage().getImageView(), VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
}

void TDS::GamePlayScene::update()
{
	if (ImGui::BeginMenuBar())
	{
		if (isPlaying)
		{
			if (ImGui::BeginMenu("Game is Running..."))
			{
				ImGui::EndMenu();
			}
		}
		else
		{
			if (ImGui::BeginMenu("Game is Paused"))
			{
				ImGui::EndMenu();
			}
		}
		ImGui::EndMenuBar();
	}
	isFocus = ImGui::IsWindowFocused() && ImGui::IsItemVisible();
	ImVec2 vSize = ImGui::GetContentRegionAvail();

	window_size = ImGui::GetWindowSize();
	if (Input::isKeyPressed(TDS_P))
	{
		auto& [x, y] = window_size;
		
		std::cout << "Window.x: " << x << " Window.y: " << y << '\n';

		/*ImGuiMouseCursor invisible_mouse(-1);
		ImGui::SetMouseCursor(invisible_mouse);*/

		//ImGui::SetCursorPos({ 0.f, 0.f });
	}

	//TDSCamera::getImguiWindowSize(ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

	ImGui::Image((ImTextureID)m_GamePlayDesc, vSize);
	
}

void TDS::GamePlayScene::Resize()
{
	if (m_GamePlayDesc)
	{
		ImGui_ImplVulkan_RemoveTexture(m_GamePlayDesc);
		m_GamePlayDesc = ImGui_ImplVulkan_AddTexture(GraphicsManager::getInstance().getFinalImage().getSampler(), GraphicsManager::getInstance().getFinalImage().getImageView(), VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

	}
}

TDS::Vec2 TDS::GamePlayScene::get_scene_window_size()
{
	return Vec2({ window_size.x, window_size.y });
}
