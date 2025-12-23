#pragma once 

#include <Platform/GLCommon.hpp>

#include <HellfireControl/Asset/Shader.hpp>

class VkShader : public PlatformShader {
private:
	VkShaderModule m_smShaderModule = VK_NULL_HANDLE;
	Array<VkVertexInputAttributeDescription> m_vVertexInputAttributes;
	Array<VkVertexInputBindingDescription> m_vVertexInputBindings;

	void CalculateInputSizes(Map<uint32, Array<VkVertexInputAttributeDescription>>& _mAttributes);

	VkFormat TranslateInputFormat(const HCShaderVar& _svVar);
	uint32 GetFormatSize(VkFormat _fFormat);

public:
	void Init(const Array<uint32>& _vCodeBlob, const Map<String, HCShaderVar>& _mVars);
	void Cleanup();

	[[nodiscard]] HC_INLINE const VkShaderModule& GetShaderModule() const { return m_smShaderModule; }
	[[nodiscard]] HC_INLINE const Array<VkVertexInputAttributeDescription>& GetVertexInputAttributes() const { return m_vVertexInputAttributes; }
	[[nodiscard]] HC_INLINE const Array<VkVertexInputBindingDescription>& GetVertexInputBindings() const { return m_vVertexInputBindings; }
};