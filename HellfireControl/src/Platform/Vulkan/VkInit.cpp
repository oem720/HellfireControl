#include <stdexcept>
#include <optional>
#include <set>
#include <limits>

#include <Platform/Vulkan/VkInit.hpp>

#include <HellfireControl/Core/Window.hpp>
#include <HellfireControl/Math/Internal/Vector/Vector2_F.hpp>


#define HC_INCLUDE_SURFACE_VK
#include <Platform/OSInclude.hpp>

#define HC_CLAMP(_val, _min, _max) _val > _max ? _max : (_val < _min ? _min : _val)

namespace LayersAndExtensions {
	std::vector<const char*> g_vValidationLayers = {
			"VK_LAYER_KHRONOS_validation"
	};

#ifndef NDEBUG
	const bool g_bEnableValidationLayers = true;
#else
	const bool g_bEnableValidationLayers = false;
#endif

	const std::vector<const char*> g_vInstanceExtensions = {
		VK_KHR_SURFACE_EXTENSION_NAME,
#ifdef WIN32
		VK_KHR_WIN32_SURFACE_EXTENSION_NAME
#else

#endif
	};

	const std::vector<const char*> g_vDeviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};
}

using namespace LayersAndExtensions;

namespace PlatformRenderer {
	struct VkQueueFamilyIndices {
		std::optional<uint32_t> m_u32GraphicsFamily;
		std::optional<uint32_t> m_u32PresentFamily;

		HC_INLINE bool IsComplete() {
			return m_u32GraphicsFamily.has_value() && m_u32PresentFamily.has_value();
		}
	};

	struct VkSwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR m_scCapabilities = {};
		std::vector<VkSurfaceFormatKHR> m_vFormats;
		std::vector<VkPresentModeKHR> m_vPresentModes;
	};

	struct VkVars {
		uint64_t g_u64WindowHandle;

		VkInstance g_iInstance = VK_NULL_HANDLE;
		VkPhysicalDevice g_pdPhysicalDevice = VK_NULL_HANDLE;
		VkDevice g_dDeviceHandle = VK_NULL_HANDLE;
		VkQueue g_qGraphicsQueue = VK_NULL_HANDLE;
		VkQueue g_qPresentQueue = VK_NULL_HANDLE;
		VkSurfaceKHR g_sSurface = VK_NULL_HANDLE;
		VkSwapchainKHR g_scSwapChain = VK_NULL_HANDLE;
	};

	static VkVars g_vVars = {};

	void CreateInstance(const std::string& _strAppName, uint32_t _u32Version);
	void CreateSurface(uint64_t _u64WindowHandle);
	void SelectPhysicalDevice();
	void CreateLogicalDevice();
	void CreateSwapChain();
	void ValidateSupportedLayers();
	bool ValidateSupportedDeviceExtensions(VkPhysicalDevice _pdDevice);
	bool CheckDeviceSuitability(VkPhysicalDevice _pdDevice);
	VkQueueFamilyIndices GetQueueFamilies(VkPhysicalDevice _pdDevice);
	VkSwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice _pdDevice);
	VkSurfaceFormatKHR SelectSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& _vAvailableFormats);
	VkPresentModeKHR SelectSwapPresentMode(const std::vector<VkPresentModeKHR>& _vAvailablePresentModes);
	VkExtent2D SelectSwapExtent(const VkSurfaceCapabilitiesKHR& _scCapabilities);

	void InitRenderer(const std::string& _strAppName, uint32_t _u32AppVersion, uint64_t _u64WindowHandle) {
		g_vVars.g_u64WindowHandle = _u64WindowHandle;

		CreateInstance(_strAppName, _u32AppVersion);

		CreateSurface(_u64WindowHandle);

		SelectPhysicalDevice();

		CreateLogicalDevice();

		CreateSwapChain();
	}

	void CreateInstance(const std::string& _strAppName, uint32_t _u32AppVersion) {
		VkApplicationInfo aiAppInfo = {
			.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
			.pNext = nullptr,
			.pApplicationName = _strAppName.c_str(),
			.applicationVersion = HC_ENGINE_VERSION,
			.pEngineName = "Hellfire Control Engine",
			.engineVersion = _u32AppVersion,
			.apiVersion = VK_API_VERSION_1_3
		};

		VkInstanceCreateInfo icInstanceInfo = {
			.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.pApplicationInfo = &aiAppInfo,
			.enabledLayerCount = 0,
			.ppEnabledLayerNames = nullptr,
			.enabledExtensionCount = static_cast<uint32_t>(g_vInstanceExtensions.size()),
			.ppEnabledExtensionNames = g_vInstanceExtensions.data()
		};

		if (g_bEnableValidationLayers) {
			ValidateSupportedLayers();
		
			icInstanceInfo.enabledLayerCount = static_cast<uint32_t>(g_vValidationLayers.size());
			icInstanceInfo.ppEnabledLayerNames = g_vValidationLayers.data();
		}

		if (vkCreateInstance(&icInstanceInfo, nullptr, &g_vVars.g_iInstance) != VK_SUCCESS) {
			throw std::runtime_error("ERROR: Failed to create Vulkan Instance!");
		}
	}

	void CreateSurface(uint64_t _u32WindowHandle) {
		PlatformSurface::CreatePlatformSurface(_u32WindowHandle, g_vVars.g_iInstance, g_vVars.g_sSurface);
	}

	void SelectPhysicalDevice() {
		uint32_t u32DeviceCount = 0;
		vkEnumeratePhysicalDevices(g_vVars.g_iInstance, &u32DeviceCount, nullptr);

		if (!u32DeviceCount) {
			throw std::runtime_error("ERROR: Failed to find compatible GPUs!");
		}

		std::vector<VkPhysicalDevice> vDevices(u32DeviceCount);
		vkEnumeratePhysicalDevices(g_vVars.g_iInstance, &u32DeviceCount, vDevices.data());

		for (const auto& aDevice : vDevices) {
			if (CheckDeviceSuitability(aDevice)) {
				g_vVars.g_pdPhysicalDevice = aDevice;
				break;
			}
		}

		if (g_vVars.g_pdPhysicalDevice == VK_NULL_HANDLE) {
			throw std::runtime_error("ERROR: Failed to find a suitable GPU!");
		}
	}

	void CreateLogicalDevice() {
		VkQueueFamilyIndices qfiIndices = GetQueueFamilies(g_vVars.g_pdPhysicalDevice);

		std::vector<VkDeviceQueueCreateInfo> vQueueCreateInfos;
		std::set<uint32_t> sUniqueQueueFamilies = {
			qfiIndices.m_u32GraphicsFamily.value(),
			qfiIndices.m_u32PresentFamily.value()
		};

		float fQueuePriority = 1.0f; //BLECK, REQUIRED FOR FUNCTION.

		for (uint32_t u32QueueFamily : sUniqueQueueFamilies) {
			VkDeviceQueueCreateInfo dqciQueueInfo = {
				.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0,
				.queueFamilyIndex = qfiIndices.m_u32GraphicsFamily.value(),
				.queueCount = 1,
				.pQueuePriorities = &fQueuePriority
			};

			vQueueCreateInfos.push_back(dqciQueueInfo);
		}

		VkPhysicalDeviceFeatures pdfFeatures = {}; //TODO Enumerate device features needed for engine function

		VkDeviceCreateInfo dciDeviceInfo = {
			.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.queueCreateInfoCount = static_cast<uint32_t>(vQueueCreateInfos.size()),
			.pQueueCreateInfos = vQueueCreateInfos.data(),
			.enabledLayerCount = 0,
			.ppEnabledLayerNames = nullptr,
			.enabledExtensionCount = static_cast<uint32_t>(g_vDeviceExtensions.size()),
			.ppEnabledExtensionNames = g_vDeviceExtensions.data(),
			.pEnabledFeatures = &pdfFeatures,
		};

		if (g_bEnableValidationLayers) {
			dciDeviceInfo.enabledLayerCount = static_cast<uint64_t>(g_vValidationLayers.size());
			dciDeviceInfo.ppEnabledLayerNames = g_vValidationLayers.data();
		}

		if (vkCreateDevice(g_vVars.g_pdPhysicalDevice, &dciDeviceInfo, nullptr, &g_vVars.g_dDeviceHandle) != VK_SUCCESS) {
			throw std::runtime_error("ERROR: Failed to create logical device!");
		}

		vkGetDeviceQueue(g_vVars.g_dDeviceHandle, qfiIndices.m_u32GraphicsFamily.value(), 0, &g_vVars.g_qGraphicsQueue);
		vkGetDeviceQueue(g_vVars.g_dDeviceHandle, qfiIndices.m_u32PresentFamily.value(), 0, &g_vVars.g_qPresentQueue);
	}

	void CreateSwapChain() {
		VkSwapChainSupportDetails scsdSupport = QuerySwapChainSupport(g_vVars.g_pdPhysicalDevice);

		VkSurfaceFormatKHR sfFormat = SelectSwapSurfaceFormat(scsdSupport.m_vFormats);
		VkPresentModeKHR pmMode = SelectSwapPresentMode(scsdSupport.m_vPresentModes);
		VkExtent2D eExtent = SelectSwapExtent(scsdSupport.m_scCapabilities);

		uint32_t u32ImageCount = scsdSupport.m_scCapabilities.minImageCount + 1;

		if (scsdSupport.m_scCapabilities.maxImageCount > 0 && u32ImageCount > scsdSupport.m_scCapabilities.maxImageCount) {
			u32ImageCount = scsdSupport.m_scCapabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR scciSwapChainInfo = {
			.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
			.pNext = nullptr,
			.flags = 0,
			.surface = g_vVars.g_sSurface,
			.minImageCount = u32ImageCount,
			.imageFormat = sfFormat.format,
			.imageColorSpace = sfFormat.colorSpace,
			.imageExtent = eExtent,
			.imageArrayLayers = 1,
			.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
			.preTransform = scsdSupport.m_scCapabilities.currentTransform,
			.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
			.presentMode = pmMode,
			.clipped = VK_TRUE,
			.oldSwapchain = VK_NULL_HANDLE,
		};

		VkQueueFamilyIndices qfiIndices = GetQueueFamilies(g_vVars.g_pdPhysicalDevice);
		uint32_t u32QueueFamilyIndices[] = { 
			qfiIndices.m_u32GraphicsFamily.value(),
			qfiIndices.m_u32PresentFamily.value()
		};

		if (qfiIndices.m_u32GraphicsFamily != qfiIndices.m_u32PresentFamily) {
			scciSwapChainInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			scciSwapChainInfo.queueFamilyIndexCount = 2;
			scciSwapChainInfo.pQueueFamilyIndices = u32QueueFamilyIndices;
		}
		else {
			scciSwapChainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			scciSwapChainInfo.queueFamilyIndexCount = 0;
			scciSwapChainInfo.pQueueFamilyIndices = nullptr;
		}

		if (vkCreateSwapchainKHR(g_vVars.g_dDeviceHandle, &scciSwapChainInfo, nullptr, &g_vVars.g_scSwapChain) != VK_SUCCESS) {
			throw std::runtime_error("ERROR: Failed to create swapchain!");
		}
	}

	void ValidateSupportedLayers() {
		uint32_t u32LayerCount = 0;		
		vkEnumerateInstanceLayerProperties(&u32LayerCount, nullptr);

		std::vector<VkLayerProperties> vLayerProperties(u32LayerCount);		
		vkEnumerateInstanceLayerProperties(&u32LayerCount, vLayerProperties.data());

		for (int ndx = 0; ndx < g_vValidationLayers.size(); ++ndx) {
			bool bLayerFound = false;

			for (const auto& aLayerProperties : vLayerProperties) {
				if (!strcmp(g_vValidationLayers[ndx], aLayerProperties.layerName)) {
					bLayerFound = true;
					break;
				}
			}

			if (!bLayerFound) {
				g_vValidationLayers.erase(g_vValidationLayers.begin() + ndx--); //If our layer is unsupported, remove it.
			}
		}
	}

	bool ValidateSupportedDeviceExtensions(VkPhysicalDevice _pdDevice) {
		uint32_t u32ExtensionCount;
		vkEnumerateDeviceExtensionProperties(_pdDevice, nullptr, &u32ExtensionCount, nullptr);

		std::vector<VkExtensionProperties> vAvailableExtensions(u32ExtensionCount);
		vkEnumerateDeviceExtensionProperties(_pdDevice, nullptr, &u32ExtensionCount, vAvailableExtensions.data());

		std::set<std::string> sRequiredExtensions(g_vDeviceExtensions.begin(), g_vDeviceExtensions.end());

		for (const auto& aExtension : vAvailableExtensions) {
			sRequiredExtensions.erase(aExtension.extensionName);
		}

		return sRequiredExtensions.empty();
	}

	bool CheckDeviceSuitability(VkPhysicalDevice _pdDevice) {
		VkPhysicalDeviceProperties pdpProperties = {};
		vkGetPhysicalDeviceProperties(_pdDevice, &pdpProperties);

		VkQueueFamilyIndices qfiIndices = GetQueueFamilies(_pdDevice);

		bool bExtensionsSupported = ValidateSupportedDeviceExtensions(_pdDevice);

		bool bSwapChainAdequate = false;

		if (bExtensionsSupported) {
			VkSwapChainSupportDetails scsdSupport = QuerySwapChainSupport(_pdDevice);
			bSwapChainAdequate = !scsdSupport.m_vFormats.empty() && !scsdSupport.m_vPresentModes.empty();
		}
		
		return pdpProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && qfiIndices.IsComplete() && bExtensionsSupported && bSwapChainAdequate;
	}

	VkQueueFamilyIndices GetQueueFamilies(VkPhysicalDevice _pdDevice) {
		VkQueueFamilyIndices qfiIndices = {};

		uint32_t u32FamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(_pdDevice, &u32FamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> vFamilies(u32FamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(_pdDevice, &u32FamilyCount, vFamilies.data());

		int iFamilyNumber = 0;
		VkBool32 bPresentSupport = false;
		for (const auto& aFamily : vFamilies) {
			if (aFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				qfiIndices.m_u32GraphicsFamily = iFamilyNumber;
			}

			vkGetPhysicalDeviceSurfaceSupportKHR(_pdDevice, iFamilyNumber, g_vVars.g_sSurface, &bPresentSupport);
			if (bPresentSupport) {
				qfiIndices.m_u32PresentFamily = iFamilyNumber;
			}

			if (qfiIndices.IsComplete()) {
				break;
			}

			++iFamilyNumber;
		}

		return qfiIndices;
	}

	VkSwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice _pdDevice) {
		VkSwapChainSupportDetails scsdDetails = {};

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_pdDevice, g_vVars.g_sSurface, &scsdDetails.m_scCapabilities);

		uint32_t u32FormatCount = 0;
		vkGetPhysicalDeviceSurfaceFormatsKHR(_pdDevice, g_vVars.g_sSurface, &u32FormatCount, nullptr);

		if (u32FormatCount) {
			scsdDetails.m_vFormats.resize(u32FormatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(_pdDevice, g_vVars.g_sSurface, &u32FormatCount, scsdDetails.m_vFormats.data());
		}

		uint32_t u32PresentModeCount = 0;
		vkGetPhysicalDeviceSurfacePresentModesKHR(_pdDevice, g_vVars.g_sSurface, &u32PresentModeCount, nullptr);

		if (u32PresentModeCount) {
			scsdDetails.m_vPresentModes.resize(u32PresentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(_pdDevice, g_vVars.g_sSurface, &u32PresentModeCount, scsdDetails.m_vPresentModes.data());
		}

		return scsdDetails;
	}

	VkSurfaceFormatKHR SelectSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& _vAvailableFormats) {
		for (const auto& aAvailableFormat : _vAvailableFormats) {
			if (aAvailableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && aAvailableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
				return aAvailableFormat;
			}
		}

		return _vAvailableFormats[0];
	}

	VkPresentModeKHR SelectSwapPresentMode(const std::vector<VkPresentModeKHR>& _vAvailablePresentModes) {
		for (const auto& aAvailablePresentMode : _vAvailablePresentModes) {
			if (aAvailablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
				return aAvailablePresentMode;
			}
		}

		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D SelectSwapExtent(const VkSurfaceCapabilitiesKHR& _scCapabilities) {
		if (_scCapabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
			return _scCapabilities.currentExtent;
		}
		else {
			Vec2F v2Size = Window(g_vVars.g_u64WindowHandle).GetWindowSize();

			VkExtent2D eViewportSize = {
				.width = static_cast<uint32_t>(v2Size.x),
				.height = static_cast<uint32_t>(v2Size.y)
			};

			eViewportSize.width = HC_CLAMP(eViewportSize.width, _scCapabilities.minImageExtent.width, _scCapabilities.maxImageExtent.width);
			eViewportSize.height = HC_CLAMP(eViewportSize.height, _scCapabilities.minImageExtent.height, _scCapabilities.maxImageExtent.height);

			return eViewportSize;
		}
	}

	void CleanupRenderer() {
		vkDestroySwapchainKHR(g_vVars.g_dDeviceHandle, g_vVars.g_scSwapChain, nullptr);
		vkDestroyDevice(g_vVars.g_dDeviceHandle, nullptr);
		vkDestroySurfaceKHR(g_vVars.g_iInstance, g_vVars.g_sSurface, nullptr);
		vkDestroyInstance(g_vVars.g_iInstance, nullptr);
	}
}