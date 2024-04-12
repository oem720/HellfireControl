#pragma once

#include <Platform/GLCommon.hpp>

#include <Platform/Vulkan/VkCore.hpp>

class RenderContext; //Forward Declare

class PlatformRenderContext {
	friend class PlatformRenderer;
	friend class PlatformBuffer;
private:
	struct VkSyncedBufferVars {
		VkBufferUsageFlags m_bufFlags = 0;

		std::vector<VkBuffer> m_vBuffers;
		std::vector<VkDeviceMemory> m_vMemory;
		std::vector<void*> m_vMappedPtrs;

		void Destroy() {
			for (int ndx = 0; ndx < HC_MAX_FRAMES_IN_FLIGHT; ++ndx) {
				vkDestroyBuffer(PlatformRenderer::m_dDeviceHandle, m_vBuffers[ndx], nullptr);

				vkFreeMemory(PlatformRenderer::m_dDeviceHandle, m_vMemory[ndx], nullptr);
			}

			m_vBuffers.clear(); //Clear lists to prevent UAF error
			m_vMemory.clear();
			m_vMappedPtrs.clear();
		}
	};

	struct VkRenderContextData {
		VkPipelineLayout m_plPipelineLayout = VK_NULL_HANDLE;
		VkPipeline m_pPipeline = VK_NULL_HANDLE;

		std::vector<VkSyncedBufferVars> m_vContextBuffers;

		std::vector<BufferHandleGeneric> m_vVertexBuffers;

		std::vector<BufferHandleGeneric> m_vIndexBuffers;

		void Destroy() {
			vkDeviceWaitIdle(PlatformRenderer::m_dDeviceHandle);

			for (auto& aSyncedBuffer : m_vContextBuffers) {
				aSyncedBuffer.Destroy();
			}

			for (auto& aBufferHandle : m_vVertexBuffers) {
				DestroyBuffer(aBufferHandle);
			}

			for (auto& aBufferHandle : m_vIndexBuffers) {
				DestroyBuffer(aBufferHandle);
			}

			vkDestroyPipelineLayout(PlatformRenderer::m_dDeviceHandle, m_plPipelineLayout, nullptr);

			vkDestroyPipeline(PlatformRenderer::m_dDeviceHandle, m_pPipeline, nullptr);

			m_vContextBuffers.clear(); //Clear list to prevent UAF error
			m_vVertexBuffers.clear();
			m_vIndexBuffers.clear();
		}

		void DestroyBuffer(BufferHandleGeneric& _bhgBuffer) {
			vkDestroyBuffer(PlatformRenderer::m_dDeviceHandle, reinterpret_cast<VkBuffer>(_bhgBuffer.upper), nullptr);
			vkFreeMemory(PlatformRenderer::m_dDeviceHandle, reinterpret_cast<VkDeviceMemory>(_bhgBuffer.lower), nullptr);
		}
	};

	static uint32_t m_u32ActiveRenderContext;

	static std::map<uint32_t, VkRenderContextData> m_mContextMap;

	static VkVertexData GetVertexAttributesFromType(uint8_t _u8VertexType);

	static void CleanupAllContextData();
public:
	static void InitRenderContext(const RenderContext& _rcContext);

	static void CleanupRenderContext(uint32_t _u32ContextID);
};