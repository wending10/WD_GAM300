#ifndef VKFRAMEBUFFER
#define VKFRAMEBUFFER

#include "Rendering/RenderTarget.h"
//#include "dotnet/ImportExport.h"
namespace TDS
{
	//Dear Xing Xiang, please ignore this and use ur frame buffer class with my pipeline. THis is just for to test my pipeline

	//THIS IS FOR DIRECT RENDERING 
	//OK
	class RenderPass;
	class FrameBuffer
	{
	public:
		FrameBuffer(VkDevice _device, VkRenderPass _renderPass, const std::vector<RenderTarget*>& _attachments, uint32_t _layer = 0, uint32_t _mipLevel = 0 );
		FrameBuffer(VkDevice _device, VkRenderPass _renderPass, bool _imageless, Vec3 _ImageLessDim);
		~FrameBuffer();

		//no copy or move ctor
		FrameBuffer(const FrameBuffer&) = delete;
		FrameBuffer& operator=(const FrameBuffer&) = delete;
		FrameBuffer(FrameBuffer&&) = delete;
		FrameBuffer& operator=(FrameBuffer&&) = delete;

		Vec3 getDimensions() { return { static_cast<float>(m_Width, m_Height, m_Depth) }; }
		VkFramebuffer getFrameBuffer() { return m_FrameBuffer; }
		void resize(Vec3 _newdim, VkRenderPass _renderPass);


	private:
		void create(VkDevice& _device, VkRenderPass _renderPass, const std::vector<RenderTarget*>& _attachments);
		void createImageless(VkDevice& _device, VkRenderPass _renderPass);
		void destroy();


		VkDevice& m_device;

		uint32_t m_Width{};
		uint32_t m_Height{};
		uint32_t m_Depth{};
		uint32_t m_UseMipLevel{ 0 };
		uint32_t m_UseLayer{ 0 };

		VkFramebuffer m_FrameBuffer{};
		std::vector<RenderTarget*> m_Attachments;
	


	};

}
#endif // !VKFRAMEBUFFER