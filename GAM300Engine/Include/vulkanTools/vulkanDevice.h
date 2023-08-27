#ifndef VULKAN_DEFINE_DEVICE
#define VULKAN_DEFINE_DEVICE

#include <vector>

#include <vulkan/vulkan.h>
#include <optional>
#include "vulkanInstance.h"

namespace TDS
{
	class VulkanDevice
	{
	public://functions

		VulkanDevice(/*std::shared_ptr<VulkanInstance>& pVKInst*/);
		~VulkanDevice();



	private:

		

	public:

		VkDevice							m_LogicalDevice{};

	private:
		

	};






}//namespace TDS



#endif // !VULKAN_DEFINE_DEVICE
