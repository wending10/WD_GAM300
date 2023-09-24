#include "editor.h"

#include <imgui.h>
#include <imgui_internal.h>

#include "ecs/ecs.h"

// reference: https://vkguide.dev/docs/extra-chapter/implementing_imgui/#:~:text=Initializing%20Imgui,after%20vulkan%20is%20fully%20initialized.&text=We%20begin%20by%20creating%20a%20descriptor%20pool%20that%20imgui%20needs.

void editorInitialize()
{
	IMGUI_CHECKVERSION();

	//this initializes the core structures of imgui
	ImGui::CreateContext();

	//this initializes imgui for SDL
	//ImGui_ImplSDL2_InitForVulkan(_window);

	//this initializes imgui for Vulkan
	//ImGui_ImplVulkan_InitInfo init_info = {};
	//init_info.Instance = _instance;
	//init_info.PhysicalDevice = _chosenGPU;
	//init_info.Device = _device;
	//init_info.Queue = _graphicsQueue;
	//init_info.DescriptorPool = imguiPool;
	//init_info.MinImageCount = 3;
	//init_info.ImageCount = 3;
	//init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;

	//ImGui_ImplVulkan_Init(&init_info, _renderPass);

	ImGui::StyleColorsDark();

	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;
}

void editorUpdate()
{
	ImGui::NewFrame();
	ImGui::DockSpaceOverViewport();
}
