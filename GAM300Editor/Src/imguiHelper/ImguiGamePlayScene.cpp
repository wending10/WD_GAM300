#include "imguiHelper/ImguiGamePlayScene.h"
#include "Rendering/GraphicsManager.h"
#include "Rendering/RenderTarget.h"


//static float TDS::TDSCamera::length_x, TDS::TDSCamera::length_y;

TDS::GamePlayScene::GamePlayScene()
{
	flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse;
	panelTitle = "GamePlayScene";
	windowPadding = ImVec2(0.f, 0.f);

	exit_cursor = 0;
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
			if (Input::isKeyPressed(TDS_ESCAPE))
			{
				++exit_cursor;
				Input::keyboard.keys
			}

			if((exit_cursor % 2) == 0)
			{
				window_size = ImGui::GetWindowSize();
				window_pos = ImGui::GetWindowPos();

				ImGuiIO& cursor_input = ImGui::GetIO();
				cursor_input.WantSetMousePos = true;
				cursor_input.MousePos = { window_pos.x + (window_size.x / 2), window_pos.y + (window_size.y / 2) };

				ImGui::SetMouseCursor(ImGuiMouseCursor_None);
			}
			
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
