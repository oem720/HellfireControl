
#include <HellfireControl/Asset/Shader.hpp>

#if HC_USE_VULKAN
#include <Platform/Vulkan/VkShader.hpp>
#include <Platform/Vulkan/VkRenderManager.hpp>

void Shader::Init() {
	if (m_pPlatformShader != nullptr) {
		return;
	}

	m_pPlatformShader = Shared<VkShader>(new VkShader(), PlatformShader::Deleter);

	m_pPlatformShader->Init(m_vCodeBlob, m_mVariables);
	m_vCodeBlob.clear();
}

void VkShader::Init(const Array<uint32>& _vCodeBlob, const Map<String, HCShaderVar>& _mVars) {
	VkShaderModuleCreateInfo smciCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.codeSize = _vCodeBlob.size() * sizeof(uint32),
		.pCode = _vCodeBlob.data()
	};

	if (vkCreateShaderModule(VkRenderManager::GetDevice(), &smciCreateInfo, nullptr, &m_smShaderModule) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create Vulkan shader module!");
	}

	Map<uint32, Array<VkVertexInputAttributeDescription>> mVertexInputAttributes;

	for (const auto& aVarPair : _mVars) {
		if (aVarPair.second.m_u16Type == VAR_STAGE_INPUT) {
			VkVertexInputAttributeDescription viaaAttributeDesc = {
				.location = aVarPair.second.m_arrData[0],
				.binding = aVarPair.second.m_arrData[1],
				.format = TranslateInputFormat(aVarPair.second),
				.offset = 0
			};

			mVertexInputAttributes[viaaAttributeDesc.binding].push_back(viaaAttributeDesc);
		}
	}

	for(auto& aBindingPair : mVertexInputAttributes) {
		std::sort(aBindingPair.second.begin(), aBindingPair.second.end(),
			[](const VkVertexInputAttributeDescription& _a, const VkVertexInputAttributeDescription& _b) {
				return _a.location < _b.location;
			}
		);
	}

	CalculateInputSizes(mVertexInputAttributes);

	for(const auto& aBindingPair : mVertexInputAttributes) {
		m_vVertexInputAttributes.insert(m_vVertexInputAttributes.end(), aBindingPair.second.begin(), aBindingPair.second.end());
	}
}

void VkShader::Cleanup() {
	//TODO: Find a way to remove this entirely to save memory. There's almost certain to be a way to check if the shader module is no longer needed,
	//and it is likely after initialization is complete. Of course, because shader recompiles can cause stuttering, it may be best to not worry about
	//it for a while, especially not until solutions can be profiled and stuttering can be accounted for.
	if (m_smShaderModule != VK_NULL_HANDLE) {
		vkDestroyShaderModule(VkRenderManager::GetDevice(), m_smShaderModule, nullptr);
	}

	m_vVertexInputAttributes.clear();
	m_vVertexInputBindings.clear();
}

void VkShader::CalculateInputSizes(Map<uint32, Array<VkVertexInputAttributeDescription>>& _mAttributes) {
	for (auto& aBindingPair : _mAttributes) {
		uint32 u32Stride = 0;
		for (int iNdx = 0; iNdx < aBindingPair.second.size(); ++iNdx) {
			aBindingPair.second[iNdx].offset = u32Stride;
			u32Stride += GetFormatSize(aBindingPair.second[iNdx].format);
		}

		m_vVertexInputBindings.push_back(
			VkVertexInputBindingDescription{
				.binding = aBindingPair.first,
				.stride = u32Stride,
				.inputRate = VK_VERTEX_INPUT_RATE_VERTEX
			}
		);
	}
}

VkFormat VkShader::TranslateInputFormat(const HCShaderVar& _svVar) {
	uint16 u16Type = _svVar.m_u16Flags & IO_MAX;

	switch (u16Type) {
	case IO_BOOL:
	case IO_UNSIGNED_BYTE:
		if(_svVar.m_arrData[3] == 1) {
			return VK_FORMAT_R8_UINT;
		}
		else if(_svVar.m_arrData[3] == 2) {
			return VK_FORMAT_R8G8_UINT;
		}
		else if(_svVar.m_arrData[3] == 3) {
			return VK_FORMAT_R8G8B8_UINT;
		}
		else if(_svVar.m_arrData[3] == 4) {
			return VK_FORMAT_R8G8B8A8_UINT;
		}
		else {
			return VK_FORMAT_UNDEFINED;
		}
	case IO_SIGNED_BYTE:
		if(_svVar.m_arrData[3] == 1) {
			return VK_FORMAT_R8_SINT;
		}
		else if(_svVar.m_arrData[3] == 2) {
			return VK_FORMAT_R8G8_SINT;
		}
		else if(_svVar.m_arrData[3] == 3) {
			return VK_FORMAT_R8G8B8_SINT;
		}
		else if(_svVar.m_arrData[3] == 4) {
			return VK_FORMAT_R8G8B8A8_SINT;
		}
		else {
			return VK_FORMAT_UNDEFINED;
		}
	case IO_SIGNED_SHORT:
		if(_svVar.m_arrData[3] == 1) {
			return VK_FORMAT_R16_SINT;
		}
		else if(_svVar.m_arrData[3] == 2) {
			return VK_FORMAT_R16G16_SINT;
		}
		else if(_svVar.m_arrData[3] == 3) {
			return VK_FORMAT_R16G16B16_SINT;
		}
		else if(_svVar.m_arrData[3] == 4) {
			return VK_FORMAT_R16G16B16A16_SINT;
		}
		else {
			return VK_FORMAT_UNDEFINED;
		}
	case IO_UNSIGNED_SHORT:
		if(_svVar.m_arrData[3] == 1) {
			return VK_FORMAT_R16_UINT;
		}
		else if(_svVar.m_arrData[3] == 2) {
			return VK_FORMAT_R16G16_UINT;
		}
		else if(_svVar.m_arrData[3] == 3) {
			return VK_FORMAT_R16G16B16_UINT;
		}
		else if(_svVar.m_arrData[3] == 4) {
			return VK_FORMAT_R16G16B16A16_UINT;
		}
		else {
			return VK_FORMAT_UNDEFINED;
		}
	case IO_SIGNED_INT:
		if(_svVar.m_arrData[3] == 1) {
			return VK_FORMAT_R32_SINT;
		}
		else if(_svVar.m_arrData[3] == 2) {
			return VK_FORMAT_R32G32_SINT;
		}
		else if(_svVar.m_arrData[3] == 3) {
			return VK_FORMAT_R32G32B32_SINT;
		}
		else if(_svVar.m_arrData[3] == 4) {
			return VK_FORMAT_R32G32B32A32_SINT;
		}
		else {
			return VK_FORMAT_UNDEFINED;
		}
		break;
	case IO_UNSIGNED_INT:
		if(_svVar.m_arrData[3] == 1) {
			return VK_FORMAT_R32_UINT;
		}
		else if(_svVar.m_arrData[3] == 2) {
			return VK_FORMAT_R32G32_UINT;
		}
		else if(_svVar.m_arrData[3] == 3) {
			return VK_FORMAT_R32G32B32_UINT;
		}
		else if(_svVar.m_arrData[3] == 4) {
			return VK_FORMAT_R32G32B32A32_UINT;
		}
		else {
			return VK_FORMAT_UNDEFINED;
		}
		break;
	case IO_HALF_FLOAT:
		if(_svVar.m_arrData[3] == 1) {
			return VK_FORMAT_R16_SFLOAT;
		}
		else if(_svVar.m_arrData[3] == 2) {
			return VK_FORMAT_R16G16_SFLOAT;
		}
		else if(_svVar.m_arrData[3] == 3) {
			return VK_FORMAT_R16G16B16_SFLOAT;
		}
		else if(_svVar.m_arrData[3] == 4) {
			return VK_FORMAT_R16G16B16A16_SFLOAT;
		}
		else {
			return VK_FORMAT_UNDEFINED;
		}
	case IO_FLOAT:
		if(_svVar.m_arrData[3] == 1) {
			return VK_FORMAT_R32_SFLOAT;
		}
		else if(_svVar.m_arrData[3] == 2) {
			return VK_FORMAT_R32G32_SFLOAT;
		}
		else if(_svVar.m_arrData[3] == 3) {
			return VK_FORMAT_R32G32B32_SFLOAT;
		}
		else if(_svVar.m_arrData[3] == 4) {
			return VK_FORMAT_R32G32B32A32_SFLOAT;
		}
		else {
			return VK_FORMAT_UNDEFINED;
		}
	case IO_DOUBLE_FLOAT:
		if(_svVar.m_arrData[3] == 1) {
			return VK_FORMAT_R64_SFLOAT;
		}
		else if(_svVar.m_arrData[3] == 2) {
			return VK_FORMAT_R64G64_SFLOAT;
		}
		else if(_svVar.m_arrData[3] == 3) {
			return VK_FORMAT_R64G64B64_SFLOAT;
		}
		else if(_svVar.m_arrData[3] == 4) {
			return VK_FORMAT_R64G64B64A64_SFLOAT;
		}
		else {
			return VK_FORMAT_UNDEFINED;
		}
	default:
		return VK_FORMAT_UNDEFINED;
	};
}

uint32 VkShader::GetFormatSize(VkFormat _fFormat) {
	switch (_fFormat) {
	case VK_FORMAT_R8_UINT:
	case VK_FORMAT_R8_SINT:
		return 1;
	case VK_FORMAT_R8G8_UINT:
	case VK_FORMAT_R8G8_SINT:
		return 2;
	case VK_FORMAT_R8G8B8_UINT:
	case VK_FORMAT_R8G8B8_SINT:
		return 3;
	case VK_FORMAT_R8G8B8A8_UINT:
	case VK_FORMAT_R8G8B8A8_SINT:
		return 4;
	case VK_FORMAT_R16_UINT:
	case VK_FORMAT_R16_SINT:
	case VK_FORMAT_R16_SFLOAT:
		return 2;
	case VK_FORMAT_R16G16_UINT:
	case VK_FORMAT_R16G16_SINT:
	case VK_FORMAT_R16G16_SFLOAT:
		return 4;
	case VK_FORMAT_R16G16B16_UINT:
	case VK_FORMAT_R16G16B16_SINT:
	case VK_FORMAT_R16G16B16_SFLOAT:
		return 6;
	case VK_FORMAT_R16G16B16A16_UINT:
	case VK_FORMAT_R16G16B16A16_SINT:
	case VK_FORMAT_R16G16B16A16_SFLOAT:
		return 8;
	case VK_FORMAT_R32_UINT:
	case VK_FORMAT_R32_SINT:
	case VK_FORMAT_R32_SFLOAT:
		return 4;
	case VK_FORMAT_R32G32_UINT:
	case VK_FORMAT_R32G32_SINT:
	case VK_FORMAT_R32G32_SFLOAT:
		return 8;
	case VK_FORMAT_R32G32B32_UINT:
	case VK_FORMAT_R32G32B32_SINT:
	case VK_FORMAT_R32G32B32_SFLOAT:
		return 12;
	case VK_FORMAT_R32G32B32A32_UINT:
	case VK_FORMAT_R32G32B32A32_SINT:
	case VK_FORMAT_R32G32B32A32_SFLOAT:
		return 16;
	default:
		return 0;
	}
}
#endif