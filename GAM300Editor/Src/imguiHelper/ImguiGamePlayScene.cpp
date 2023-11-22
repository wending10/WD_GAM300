#include "imguiHelper/ImguiGamePlayScene.h"
#include "Rendering/GraphicsManager.h"
#include "Rendering/RenderTarget.h"


//static float TDS::TDSCamera::length_x, TDS::TDSCamera::length_y;

TDS::GamePlayScene::GamePlayScene()
{
	flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse;
	panelTitle = "GamePlayScene";
	windowPadding = ImVec2(0.f, 0.f);

	exit_cursor = true;
	show_cursor = 1;
}

void TDS::GamePlayScene::init()
{
	m_GamePlayDesc = ImGui_ImplVulkan_AddTexture(GraphicsManager::getInstance().getFinalImage().getSampler(), GraphicsManager::getInstance().getFinalImage().getImageView(), VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
}

void TDS::GamePlayScene::update()
{
	isFocus = ImGui::IsWindowFocused() && ImGui::IsItemVisible();

	if (ImGui::BeginMenuBar())
	{
		if (isPlaying)
		{			
			if (Input::isKeyPressed(TDS_ESCAPE))
			{
				exit_cursor = !exit_cursor;
				Input::releaseTheKey(TDS_ESCAPE);
			}

			if(exit_cursor)
			{
				window_size = ImGui::GetWindowSize();
				window_pos = ImGui::GetWindowPos();

				Input::setCurrentMousePos(ImGui::GetMousePos().x, ImGui::GetMousePos().y, Vec2(window_pos.x, window_pos.x + window_size.x), Vec2(window_pos.y, window_pos.y + window_size.y));

				ImGuiIO& cursor_input = ImGui::GetIO();
				cursor_input.WantSetMousePos = true;
				cursor_input.MousePos = { window_pos.x + (window_size.x * .5f), window_pos.y + (window_size.y * .5f) };

				Input::setCenteredMouse(cursor_input.MousePos.x, cursor_input.MousePos.y);

				//ImGui::SetMouseCursor(ImGuiMouseCursor_None);
				show_cursor = 0;
			}
			else
			{
				ImGuiIO& cursor_input = ImGui::GetIO();
				cursor_input.WantSetMousePos = false;
				show_cursor = 1;
			}

			ShowCursor(show_cursor);
			
			if (ImGui::BeginMenu("Game is Running..."))
			{
				ImGui::EndMenu();
			}
		}
		else
		{
			CameraSystem::SetIsPlaying(false);
			
			if (ImGui::BeginMenu("Game is Paused"))
			{
				ImGui::EndMenu();
			}
		}

		ImGui::EndMenuBar();
	}
	ImVec2 vSize = ImGui::GetContentRegionAvail();

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
