#ifndef VULKAN_CREATE_INSTANCE
#define VULKAN_CREATE_INSTANCE

#ifndef NOMINMAX
#define NOMINMAX
#endif//NOMINMAX
#define	VK_USE_PLATFORM_WIN32_KHR

#include <vulkan/vulkan.h>
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <limits>
#include <algorithm>
#include <fstream>
#include <array>

#include "windowswindow.h"
#include "vulkanTools/vulkanDebugger.h"
#include "vulkanTools/vulkanDevice.h"
#include "Vector2.h"//for testing
namespace TDS
{
	
	class VulkanInstance
	{

		static std::vector<char> readFile(const std::string& filename) 
		{
			std::ifstream file(filename, std::ios::ate | std::ios::binary);

			if (!file.is_open()) {
				throw std::runtime_error("failed to open file!");
			}

			size_t fileSize = (size_t)file.tellg();
			std::vector<char> buffer(fileSize);

			file.seekg(0);
			file.read(buffer.data(), fileSize);

			file.close();

			return buffer;
		}
		struct QueueFamilyIndices
		{
			std::optional<uint32_t> graphicsFamily;
			std::optional<uint32_t>	presentFamily;
			bool isComplete()
			{
				return graphicsFamily.has_value() &&
					   presentFamily.has_value();
			}
		};
		struct SwapChainSupportDetails
		{
			VkSurfaceCapabilitiesKHR capabilities{};
			std::vector<VkSurfaceFormatKHR> formats{};
			std::vector<VkPresentModeKHR> presentModes{};
		};

		struct Vertex
		{
			Vec2 pos;
			Vec3 color;

			static VkVertexInputBindingDescription getBindingDescription() 
			{
				VkVertexInputBindingDescription bindingDescription{};
				bindingDescription.binding = 0;
				bindingDescription.stride = sizeof(Vertex);
				bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX; //or can per instance (VK_VERTEX_INPUT_RATE_INSTANCE)

				return bindingDescription;
			}
			static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() 
			{
				std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
				//pos which now is vec 2
				attributeDescriptions[0].binding = 0;
				attributeDescriptions[0].location = 0;
				attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT; //r32g32 using 2 floats
				attributeDescriptions[0].offset = offsetof(Vertex, pos);

				//color which now is vec3
				attributeDescriptions[1].binding = 0;
				attributeDescriptions[1].location = 1;
				attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;//using 3 floats
				attributeDescriptions[1].offset = offsetof(Vertex, color);

				return attributeDescriptions;
			}
			
		};

	public://functions

		VulkanInstance(const  WindowsWin& enableWindows);
		~VulkanInstance();
		VkResult createInstance(bool enableValidation);
		void	 drawFrame(const WindowsWin& _Windows);
		//getters
		//VkInstance		 getVkInstance()const		{ return m_VKhandler; }
		//VkPhysicalDevice getVkPhysicalDevice()const { return m_PhysDeviceHandle; }
		VkDevice		 getVkLogicalDevice()const { return m_logicalDevice; }
	private:

		bool			   checkValidationLayerSupport();
		bool			   isDeviceSuitable(VkPhysicalDevice device);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

		//to be moved to other file
		bool					 checkDeviceExtensionSupport(VkPhysicalDevice device);
		SwapChainSupportDetails  querySwapChainSupport(const VkPhysicalDevice& device);
		VkSurfaceFormatKHR		 chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR         chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D				 chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, const WindowsWin& windows);
		VkShaderModule			 createShaderModule(const std::vector<char>& code);
		void					 recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
	
		void					 recreateSwapChain(const WindowsWin& _Windows);
		void					 createSwapChain(const WindowsWin& _Windows);
		void					 cleanupSwapChain();
		void					 createImageViews();
		void					 createFrameBuffer();
		
		//to be removed
		void					 createBuffers(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer,
											   VkDeviceMemory& buffermemory);
		void					 createVertexBuffer();
		void					 createIndexBuffer();
		uint32_t				 findMemoryType(const uint32_t& typeFiler, VkMemoryPropertyFlags properties);
		void					 copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

public://members


		static constexpr decltype(VkApplicationInfo::apiVersion) apiVersion		{ VK_API_VERSION_1_3 };
		std::vector<std::string> supportedInstanceExtensions{};
		std::vector<const char*> enabledInstanceExtensions{};

		bool framebufferResized { false };
	
	private:

		//frames processed concurrently
		const int MAX_FRAMES_IN_FLIGHT { 2 };	//maybe set as a macro, will see

		uint32_t  m_currentFrame{ 0 }; //keep track to make sure using the right objects every frame


		/*Each frame should have its own command buffer, set of semaphores, and fence*/
		std::vector <VkCommandBuffer> m_commandBuffers;
		std::vector <VkSemaphore>	  m_imageAvailableSemaphore;
		std::vector <VkSemaphore>	  m_renderFinishedSemaphore;
		std::vector <VkFence>		  m_inFlightFence;


		std::vector<VkImageView> swapChainImageViews;
		VkInstance			m_VKhandler;
		VkPhysicalDevice	m_PhysDeviceHandle{ VK_NULL_HANDLE }; //where selected graphic card is stored
		VkDevice			m_logicalDevice;
		VkQueue				m_graphicQueue;	
		VkQueue				m_presentQueue;
		VkSurfaceKHR		m_Surface{};
		VkSwapchainKHR		m_SwapChain{};
		VkFormat			m_swapChainImageFormat;
		VkExtent2D			m_swapChainExtent;
		VkSurfaceFormatKHR  m_VKSurfaceFormat{};
		VkRenderPass		m_RenderPass;
		VkPipelineLayout	m_pipelineLayout;
		VkPipeline			m_graphicPipeline;
		VkCommandPool		m_commandPool;

		//handle vertex
		VkBuffer			m_vertexBuffer; //use it in rendering commands, does not depend on swapchain
		VkDeviceMemory		m_vertexBufferMemory;// store the handle to the memory 

		//handle indices
		VkBuffer			m_indexBuffer;
		VkDeviceMemory		m_IndexBufferMemory;

		std::vector<VkImage>		   m_swapChainImages;
		std::vector<VkFramebuffer>	   m_swapChainFramebuffers;
		const std::vector<const char*> validationLayers { "VK_LAYER_KHRONOS_validation" };
		const std::vector<const char*> deviceExtensions { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
		std::vector <VkPipelineShaderStageCreateInfo> shaderStages{};
		bool	enableValidate{ false };
		
		const std::vector<Vertex> vertices
		{
			{{-0.5f, -0.5f}, { 1.0f, 0.0f, 0.0f }},
			{ {0.5f, -0.5f}, {0.0f, 1.0f, 0.0f} },
			{ {0.5f, 0.5f}, {0.0f, 0.0f, 1.0f} },
			{ {-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f} }
		};

		const std::vector<uint16_t> indices//uint16_t 65535 unique vertices
		{
			0, 1, 2, 2, 3, 0
		};
	};








}//namespace TDS



#endif//!VULKAN_CREATE_INSTANCE