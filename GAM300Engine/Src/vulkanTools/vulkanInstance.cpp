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

		//should this put before device?

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
		m_SwapChainHandle.connect(m_VKhandler, m_PhysDeviceHandle, m_logicalDevice);
		m_SwapChainHandle.initSurface(_Windows.getHInstance(), _Windows.getWindowHandler());

		//create logical devices
		{
			QueueFamilyIndices indices = findQueueFamilies(m_PhysDeviceHandle);

			std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
			std::set<uint32_t> uniqueQueueFamilies = 
			{ indices.graphicsFamily.value(), 
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
			  createInfo.sType				   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
			  createInfo.queueCreateInfoCount    = static_cast<uint32_t>(queueCreateInfos.size());
			  createInfo.pQueueCreateInfos	   = queueCreateInfos.data();
			  createInfo.pEnabledFeatures		   = &deviceFeatures;
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
			uint32_t winWidth  = _Windows.getWidth();
			uint32_t winHeight = _Windows.getHeight();
			m_SwapChainHandle.create(&winWidth, &winHeight);
		}

	}

	VulkanInstance::~VulkanInstance()
	{
		m_SwapChainHandle.cleanup();
		vkDestroyDevice(m_logicalDevice, nullptr);
		if(enableValidate)
			TDS::Debug::freeDebugger(m_VKhandler);


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
					std::cerr << "Validation layer VK_LAYER_KHRONOS_validation not present, validation is disabled";
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

		for (const auto& layerName : validationLayers)
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
				return true;
			}
		}


		return false;
	}

	bool VulkanInstance::isDeviceSuitable(VkPhysicalDevice device)
	{
		QueueFamilyIndices indices = findQueueFamilies(device);

		return indices.isComplete();
	}

	VulkanInstance::QueueFamilyIndices VulkanInstance::findQueueFamilies(VkPhysicalDevice device)
	{
		QueueFamilyIndices indices;

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		int i = 0;
		for (const auto& queueFamily : queueFamilies) {
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				indices.graphicsFamily = i;
			}

			if (indices.isComplete()) {
				break;
			}

			i++;
		}

		return indices;
	}
}//namespace TDS