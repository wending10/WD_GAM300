#ifndef TDS_VULKAN_RENDERERMGR
#define TDS_VULKAN_RENDERERMGR

#include "vulkanInstance.h"
#include "Renderer.h"
#include "windowswindow.h"
#include "Pipeline.h"
#include "TDSMath.h"
#include "camera/camera.h"
#include "vulkanTools/Model.h"
#include "FrameInfo.h"
namespace TDS {

	class DLL_API RendererManager {
	public:
		struct SimplePushConstantData {
			Mat4 ModelMat{ 1.f };
			Mat4 NormalMat{ 1.f };
		};
		RendererManager(VulkanInstance& m_Instance, VkRenderPass RenderPass, VkDescriptorSetLayout globalSetlayout);
		~RendererManager();

		RendererManager(const RendererManager&) = delete;
		RendererManager& operator=(const RendererManager&) = delete;

		void draw(FrameInfo& frameinfo);
	private:
		void createPipelineLayout(VkDescriptorSetLayout globalsetlayout);
		void createPipeline(VkRenderPass renderpass);

		VulkanInstance& m_Instance;

		std::unique_ptr<Pipeline>	m_Pipeline;
		VkPipelineLayout			m_PipelineLayout;
	};
}
#endif // !TDS_VULKAN_RENDERERMGR