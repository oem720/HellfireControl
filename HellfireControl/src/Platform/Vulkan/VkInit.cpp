
#include <Platform/Vulkan/VkInit.hpp>
#include <stdexcept>

namespace PlatformRenderer {
	struct VkVars {
		VkInstance m_iInstance;
	};

	static VkVars g_vVars = {};

	void InitRenderer(const std::string& _strAppName, uint32_t _u32Version) {
		GetInstance(_strAppName, _u32Version);
	}

	void GetInstance(const std::string& _strAppName, uint32_t _u32Version) {
		VkApplicationInfo aiInfo = {
			.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
			.pNext = nullptr,
			.pApplicationName = _strAppName.c_str(),
			.applicationVersion = HC_ENGINE_VERSION,
			.pEngineName = "Hellfire Control Engine",
			.engineVersion = _u32Version,
			.apiVersion = VK_API_VERSION_1_0
		};

		VkInstanceCreateInfo iciInfo = {
			.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.pApplicationInfo = &aiInfo,
			.enabledLayerCount = 0,
			.ppEnabledLayerNames = nullptr,
			.enabledExtensionCount = 0,
			.ppEnabledExtensionNames = nullptr
		};

		if (vkCreateInstance(&iciInfo, nullptr, &g_vVars.m_iInstance) != VK_SUCCESS) {
			throw std::runtime_error("ERROR: Failed to create Vulkan Instance!");
		}
	}

	void CleanupRenderer() {
		vkDestroyInstance(g_vVars.m_iInstance, nullptr);
	}
}