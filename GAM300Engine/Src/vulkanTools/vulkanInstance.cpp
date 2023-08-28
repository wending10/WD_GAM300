#include "vulkanTools/vulkanInstance.h"


namespace TDS
{
	VulkanInstance::VulkanInstance(const WindowsWin& _Windows)
	{
		VkResult err;

		// Vulkan instance
		err = createInstance(_Windows.settings.validation);
		if (err) {
			std::cerr << "Could not create Vulkan instance :\n";
		}
		
		//if request, enable default validation layers for debugging
		if (_Windows.settings.validation)
		{
			enableValidate = true; //to be remove
			TDS::Debug::setupDebugger(m_VKhandler);
		}

		//win32 surface creation

		{

			VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = {};
			surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
			surfaceCreateInfo.hinstance = _Windows.getHInstance();
			surfaceCreateInfo.hwnd = _Windows.getWindowHandler();
			err = vkCreateWin32SurfaceKHR(m_VKhandler, &surfaceCreateInfo, nullptr, &m_Surface);

			if(err != VK_SUCCESS)
				throw std::runtime_error("failed to create window surface!");
		}



		//get physical device aka gpu card
		{
			uint32_t deviceCount = 0;
			vkEnumeratePhysicalDevices(m_VKhandler, &deviceCount, nullptr);

			if (deviceCount == 0) // if there are 0 devices with vulkan support, ggwp
			{
				throw std::runtime_error("failed to find GPUs with Vulkan support!");
			}

			//otherwise, allocate an array to hold all of the VkPhysicalDevice handles
			std::vector<VkPhysicalDevice> devices(deviceCount);
			vkEnumeratePhysicalDevices(m_VKhandler, &deviceCount, devices.data());

			//evaluate each of them and check suitability
			for (const auto& device : devices) {
				if (isDeviceSuitable(device)) {
					m_PhysDeviceHandle = device;
					break;
				}
			}

			if (m_PhysDeviceHandle == VK_NULL_HANDLE) {
				throw std::runtime_error("failed to find a suitable GPU!");
			}
		}
		
		//create logical devices
		{
			QueueFamilyIndices indices = findQueueFamilies(m_PhysDeviceHandle);

			std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
			std::set<uint32_t> uniqueQueueFamilies = 
			{ 
			  indices.graphicsFamily.value(), 
			  indices.presentFamily.value() 
			};

			float queuePriority = 1.0f;
			for (uint32_t queueFamily : uniqueQueueFamilies) 
			{
				VkDeviceQueueCreateInfo queueCreateInfo{};
				queueCreateInfo.sType			 = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				queueCreateInfo.queueFamilyIndex = queueFamily;
				queueCreateInfo.queueCount		 = 1;
				queueCreateInfo.pQueuePriorities = &queuePriority;
				queueCreateInfos.push_back(queueCreateInfo);
			}
			VkPhysicalDeviceFeatures deviceFeatures{};

			VkDeviceCreateInfo createInfo{};
			  createInfo.sType				     = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
			  createInfo.queueCreateInfoCount    = static_cast<uint32_t>(queueCreateInfos.size());
			  createInfo.pQueueCreateInfos	     = queueCreateInfos.data();
			  createInfo.pEnabledFeatures		 = &deviceFeatures;
			  createInfo.enabledExtensionCount   = static_cast<uint32_t>(deviceExtensions.size());
			  createInfo.ppEnabledExtensionNames = deviceExtensions.data();
			
			if (_Windows.settings.validation)
			{
			  createInfo.enabledLayerCount       = static_cast<uint32_t>(validationLayers.size());
			  createInfo.ppEnabledLayerNames     = validationLayers.data();
			}
			else
			{
				createInfo.enabledLayerCount = 0;
			}

			if (vkCreateDevice(m_PhysDeviceHandle, &createInfo, nullptr, &m_logicalDevice) != VK_SUCCESS)
			{
				throw std::runtime_error("failed to create logical device!");
			}

			vkGetDeviceQueue(m_logicalDevice, indices.graphicsFamily.value(), 0, &m_graphicQueue);
			vkGetDeviceQueue(m_logicalDevice, indices.presentFamily.value() , 0, &m_presentQueue);
		}
		//swapchain setup
		{
			//uint32_t winWidth  = _Windows.getWidth();
			//uint32_t winHeight = _Windows.getHeight();
			//m_SwapChainHandle.create(&winWidth, &winHeight);
			SwapChainSupportDetails swapChainSupport = querySwapChainSupport(m_PhysDeviceHandle);

			VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
			VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
			VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities, _Windows);

			uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
			if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
				imageCount = swapChainSupport.capabilities.maxImageCount;
			}

			VkSwapchainCreateInfoKHR createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
			createInfo.surface = m_Surface;

			createInfo.minImageCount = imageCount;
			createInfo.imageFormat = surfaceFormat.format;
			createInfo.imageColorSpace = surfaceFormat.colorSpace;
			createInfo.imageExtent = extent;
			createInfo.imageArrayLayers = 1;
			createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

			QueueFamilyIndices indices = findQueueFamilies(m_PhysDeviceHandle);
			uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

			if (indices.graphicsFamily != indices.presentFamily) {
				createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
				createInfo.queueFamilyIndexCount = 2;
				createInfo.pQueueFamilyIndices = queueFamilyIndices;
			}
			else {
				createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			}

			createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
			createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
			createInfo.presentMode = presentMode;
			createInfo.clipped = VK_TRUE;

			createInfo.oldSwapchain = VK_NULL_HANDLE;

			if (vkCreateSwapchainKHR(m_logicalDevice, &createInfo, nullptr, &m_SwapChain) != VK_SUCCESS) {
				throw std::runtime_error("failed to create swap chain!");
			}

			vkGetSwapchainImagesKHR(m_logicalDevice, m_SwapChain, &imageCount, nullptr);
			m_swapChainImages.resize(imageCount);
			vkGetSwapchainImagesKHR(m_logicalDevice, m_SwapChain, &imageCount, m_swapChainImages.data());

			m_swapChainImageFormat = surfaceFormat.format;
			m_swapChainExtent = extent;

		}
		//image View
		{
			swapChainImageViews.resize(m_swapChainImages.size());

			for (size_t i = 0; i < m_swapChainImages.size(); i++) {
				VkImageViewCreateInfo createInfo{};
				createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
				createInfo.image = m_swapChainImages[i];
				createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
				createInfo.format = m_swapChainImageFormat;
				createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
				createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
				createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
				createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
				createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
				createInfo.subresourceRange.baseMipLevel = 0;
				createInfo.subresourceRange.levelCount = 1;
				createInfo.subresourceRange.baseArrayLayer = 0;
				createInfo.subresourceRange.layerCount = 1;

				if (vkCreateImageView(m_logicalDevice, &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS) {
					throw std::runtime_error("failed to create image views!");
				}
			}

		}

	}

	VulkanInstance::~VulkanInstance()
	{
		for (auto imageView : swapChainImageViews) {
			vkDestroyImageView(m_logicalDevice, imageView, nullptr);
		}

		vkDestroySwapchainKHR(m_logicalDevice, m_SwapChain, nullptr);
		vkDestroyDevice(m_logicalDevice, nullptr);
		if(enableValidate)
			TDS::Debug::freeDebugger(m_VKhandler);

		vkDestroySurfaceKHR(m_VKhandler, m_Surface, nullptr);
		vkDestroyInstance(m_VKhandler, nullptr);
	}

	VkResult VulkanInstance::createInstance(bool enableValidation)
	{
		//feed our application info to struct VkApplicationInfo
		VkApplicationInfo appInfo{};
		appInfo.sType				= VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pNext				= nullptr;
		appInfo.pApplicationName	= "Tear Drop Studio";
		appInfo.applicationVersion	= 1;
		appInfo.pEngineName			= "Tear Drop Engine";
		appInfo.engineVersion		= 1;
		appInfo.apiVersion			= apiVersion;


		//enabling Extensions
		std::vector<const char*> instanceExtensions
		{
			VK_KHR_SURFACE_EXTENSION_NAME,
			VK_KHR_WIN32_SURFACE_EXTENSION_NAME
		};

		// Get extensions supported by the instance and store for later use
		uint32_t extCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extCount, nullptr);
		if (extCount > 0)
		{
			std::vector<VkExtensionProperties> extensions(extCount);
			if (vkEnumerateInstanceExtensionProperties(nullptr, &extCount, &extensions.front()) == VK_SUCCESS)
			{
				for (const VkExtensionProperties& extension : extensions)
				{
					supportedInstanceExtensions.push_back(extension.extensionName);
				}
			}
		}

		// Enabled requested instance extensions
		if ( enabledInstanceExtensions.size() > 0)
		{
			for (const char* enabledExtension : enabledInstanceExtensions)
			{
				// Output message if requested extension is not available
				if (std::find(supportedInstanceExtensions.begin(), supportedInstanceExtensions.end(), enabledExtension) == supportedInstanceExtensions.end())
				{
					std::cerr << "Enabled instance extension \"" << enabledExtension << "\" is not present at instance level\n";
				}
				instanceExtensions.push_back(enabledExtension);
			}
		}


		//Instance create info
		VkInstanceCreateInfo instanceCreateInfo{};
		{
			instanceCreateInfo.sType				= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			instanceCreateInfo.pNext				= nullptr;
			instanceCreateInfo.flags				= 0;
			instanceCreateInfo.pApplicationInfo		= &appInfo;

			//Validation Layering
			if (enableValidation)
			{
				if (checkValidationLayerSupport())
				{
					instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
					instanceCreateInfo.ppEnabledLayerNames = validationLayers.data();
				}
				else
				{
					std::cerr << "Validation layer VK_LAYER_KHRONOS_validation not present, validation is disabled\n";
				}
			}
			
			if (enableValidation || std::find(supportedInstanceExtensions.begin(), supportedInstanceExtensions.end(), VK_EXT_DEBUG_UTILS_EXTENSION_NAME) != supportedInstanceExtensions.end()) {
				instanceExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
			}

			if (instanceExtensions.size() > 0)
			{
				instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
				instanceCreateInfo.ppEnabledExtensionNames = instanceExtensions.data();
			}	
		};



		VkResult result = vkCreateInstance(&instanceCreateInfo, nullptr, &m_VKhandler);
		if (result != VK_SUCCESS) {
			throw std::runtime_error("failed to create instance!");
		}
		// If the debug utils extension is present we set up debug functions, so samples an label objects for debugging
		if (std::find(supportedInstanceExtensions.begin(), supportedInstanceExtensions.end(), VK_EXT_DEBUG_UTILS_EXTENSION_NAME) != supportedInstanceExtensions.end()) 
		{
			//to do 
			std::cout << "ok\n";
		}

		return result;

	}


	//checks if all of the requested layers are available
	bool VulkanInstance::checkValidationLayerSupport()
	{
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* layerName : validationLayers)
		{
			bool layerFound = false;

			for (const auto& layerProperties : availableLayers)
			{
				if (strcmp(layerName, layerProperties.layerName) == 0)
				{
					layerFound = true;
					break;
				}
			}

			if (!layerFound) {
				return false;
			}
		}


		return true;
	}
	VulkanInstance::SwapChainSupportDetails VulkanInstance::querySwapChainSupport(VkPhysicalDevice device)
	{
		SwapChainSupportDetails details;

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_Surface, &details.capabilities);

		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_Surface, &formatCount, nullptr);

		if (formatCount != 0) {
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_Surface, &formatCount, details.formats.data());
		}

		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_Surface, &presentModeCount, nullptr);

		if (presentModeCount != 0) {
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_Surface, &presentModeCount, details.presentModes.data());
		}

		return details;
	}
	bool VulkanInstance::isDeviceSuitable(VkPhysicalDevice device)
	{
		QueueFamilyIndices indices = findQueueFamilies(device);

		bool extensionsSupported = checkDeviceExtensionSupport(device);

		bool swapChainAdequate = false;

		if (extensionsSupported) {
			SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
		}

		return indices.isComplete() && extensionsSupported && swapChainAdequate;
	}

	VulkanInstance::QueueFamilyIndices VulkanInstance::findQueueFamilies(VkPhysicalDevice device)
	{
		QueueFamilyIndices indices;

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		int i{ 0 };
		for (const auto& queueFamily : queueFamilies) {
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				indices.graphicsFamily = i;
			}

			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_Surface, &presentSupport);

			if (presentSupport) {
				indices.presentFamily = i;
			}

			if (indices.isComplete()) {
				break;
			}

			i++;
		}

		return indices;
	}

	bool VulkanInstance::checkDeviceExtensionSupport(VkPhysicalDevice device)
	{
		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

		std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

		for (const auto& extension : availableExtensions) {
			requiredExtensions.erase(extension.extensionName);
		}

		return requiredExtensions.empty();
	}

	VkSurfaceFormatKHR VulkanInstance::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
	{
		for (const auto& availableFormat : availableFormats) {
			if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
				return availableFormat;
			}
		}

		return availableFormats[0];
	}
	
	VkPresentModeKHR VulkanInstance::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
	{
		for (const auto& availablePresentMode : availablePresentModes) {
			if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
				return availablePresentMode;
			}
		}

		return VK_PRESENT_MODE_FIFO_KHR;
	}
	
	VkExtent2D VulkanInstance::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, WindowsWin windows)
	{
		if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
			return capabilities.currentExtent;
		}
		else {
			//int width, height;
			//glfwGetFramebufferSize(window, &width, &height);

			VkExtent2D actualExtent = {
				windows.getWidth(),
				windows.getHeight()
			};

			actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
			actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

			return actualExtent;
		}

	}

}//namespace TDS