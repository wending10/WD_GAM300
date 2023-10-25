#ifndef RENDERPASS
#define RENDERPASS

#include "vulkanTools/FrameBuffer.h"
#include "Rendering/RenderTarget.h"

namespace TDS {
	
	struct AttachmentClearColor
	{
		VkClearColorValue color{ {0.f,0.f,0.f,1.f} };
		VkClearDepthStencilValue depth{ 1.f, 0 };
	};
	struct AttachmentInfo
	{
		RenderTarget* framebufferAttachment;
		VkAttachmentLoadOp loadOP;
		VkAttachmentStoreOp storeOP;
		VkAttachmentLoadOp stencilLoadOP;
		VkAttachmentStoreOp stencilStoreOP;
		AttachmentClearColor clear = AttachmentClearColor{};
	};
	class RenderPass
	{
	public:
		RenderPass(VkDevice device, const std::vector<AttachmentInfo>& attachments);
		~RenderPass();
		//no move and copy ctor
		RenderPass(const RenderPass&) = delete;
		RenderPass& operator=(const RenderPass&) = delete;
		RenderPass(RenderPass&&) = delete;
		RenderPass& operator=(RenderPass&&) = delete;

		void beginRenderPass(VkCommandBuffer commandBuffer, FrameBuffer* framebuffer, uint32_t viewports = 1);
		void endRenderPass(VkCommandBuffer commandBuffer);

		void setViewportSize(uint32_t w, uint32_t h) { m_Width = w; m_Height = h; }

		VkRenderPass getRenderPass()const { return m_RenderPass; }
	private:
		VkRenderPass m_RenderPass{};
		uint32_t m_Width{};
		uint32_t m_Height{};

		VkDevice& m_Device;

		std::vector<VkClearValue> m_clearValues{};
	};




}//END namespace



#endif // !RENDERPASS

