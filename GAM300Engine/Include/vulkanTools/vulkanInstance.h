#ifndef VULKAN_CREATE_INSTANCE
#define VULKAN_CREATE_INSTANCE

#define	VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>
#include <vector>
#include <string>
#include <iostream>
#include <set>

#include "windowswindow.h"
#include "vulkanTools/vulkanDebugger.h"
#include "vulkanTools/vulkanDevice.h"
#include "vulkanSwapChain.h"

namespace TDS
{
	
	class VulkanInstance
	{
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
	public://functions

		VulkanInstance(const  WindowsWin& enableWindows);
		~VulkanInstance();
		VkResult createInstance(bool enableValidation);

		//getters
		VkInstance		 getVkInstance()const		{ return m_VKhandler; }
		VkPhysicalDevice getVkPhysicalDevice()const { return m_PhysDeviceHandle; }
		VkDevice		 getVkLogicalDevice()const { return m_logicalDevice; }

	private:

		bool			   checkValidationLayerSupport();
		bool			   isDeviceSuitable(VkPhysicalDevice device);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	public://members

		static constexpr decltype(VkApplicationInfo::apiVersion) apiVersion		{ VK_API_VERSION_1_3 };
		std::vector<std::string> supportedInstanceExtensions{};
		std::vector<const char*> enabledInstanceExtensions{};
	
	private:

		VkInstance		 m_VKhandler;
		VkPhysicalDevice m_PhysDeviceHandle{ VK_NULL_HANDLE }; //where selected graphic card is stored
		VkDevice		 m_logicalDevice;
		VkQueue			 m_graphicQueue;	
		VkQueue			 m_presentQueue;
		const std::vector<const char*> validationLayers { "VK_LAYER_KHRONOS_validation" };

		const std::vector<const char*> deviceExtensions { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
		
		bool			 enableValidate{ false };

		VulkanSwapChain	 m_SwapChainHandle;

	};








}//namespace TDS



#endif//!VULKAN_CREATE_INSTANCE