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
	isFocus = ImGui::IsWindowFocused() && ImGui::IsItemVisible();
	ImVec2 vSize = ImGui::GetContentRegionAvail();


	ImGui::Image((ImTextureID)m_GamePlayDesc, vSize);
	
	//TDSCamera::getImguiWindowSize({ImGui::GetWindowWidth(), ImGui::GetWindowHeight()});
}

void TDS::GamePlayScene::Resize()
{
	if (m_GamePlayDesc)
	{
		ImGui_ImplVulkan_RemoveTexture(m_GamePlayDesc);
		m_GamePlayDesc = ImGui_ImplVulkan_AddTexture(GraphicsManager::getInstance().getFinalImage().getSampler(), GraphicsManager::getInstance().getFinalImage().getImageView(), VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

	}


}
