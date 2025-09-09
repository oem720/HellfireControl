
#include <HellfireControl/Render/Renderer.hpp>

#if HC_USE_VULKAN
#include <Platform/Vulkan/VkRenderer.hpp>
#include <Platform/Vulkan/VkRenderManager.hpp>

void Renderer::Init() {

}

void Renderer::Render() {
	std::cout << "Running render layer: " << m_u32Tag << "\n";
}

void Renderer::Cleanup() {

}
#endif