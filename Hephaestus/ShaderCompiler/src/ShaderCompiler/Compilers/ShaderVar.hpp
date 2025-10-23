#pragma once

#include <HellfireControl/Core/Common.hpp>

enum HCShaderVarType : uint8_t {
	VAR_COMBINED_IMAGE_SAMPLER,
	VAR_SAMPLER,
	VAR_TEXTURE_2D,
	VAR_IMAGE_2D,
	VAR_UNIFORM_TEXEL_BUFFER,
	VAR_STORAGE_TEXEL_BUFFER,
	VAR_UNIFORM_BUFFER,
	VAR_STORAGE_BUFFER,
	VAR_PUSH_CONSTANT_BUFFER,
	VAR_STAGE_INPUT,
	VAR_STAGE_OUTPUT,
	VAR_SUBPASS_INPUT,
	VAR_BUILTIN_STAGE_INPUT,
	VAR_BUILTIN_STAGE_OUTPUT,
	VAR_ACCELERATION_STRUCTURE,
	VAR_SHADER_RECORD_BUFFER,
	VAR_ATOMIC_COUNTER,
	VAR_GL_PLAIN_UNIFORM
};

struct ShaderVarParameters {};

struct HCShaderVar {
	HCShaderVarType m_svtType;

	std::string m_strVarName;

	std::shared_ptr<ShaderVarParameters> m_pParameters;
};

struct BufferParameters : public ShaderVarParameters {
	uint32_t m_u32Binding = 0;
	uint32_t m_u32Set = 0;
	uint32_t m_u32Size = 0;
	uint32_t m_u32UnsizedArrayStride = 0;

	BufferParameters(uint32_t _u32Binding, uint32_t _u32Set, uint32_t _u32Size, uint32_t _u32UnsizedArrayStride)
		: m_u32Binding(_u32Binding)
		, m_u32Set(_u32Set)
		, m_u32Size(_u32Size)
		, m_u32UnsizedArrayStride(_u32UnsizedArrayStride) {
	}
};

struct PushConstantParameters : public ShaderVarParameters {
	uint32_t m_u32Offset = 0;
	uint32_t m_u32Size = 0;

	PushConstantParameters(uint32_t _u32Offset, uint32_t _u32Size)
		: m_u32Offset(_u32Offset)
		, m_u32Size(_u32Size) {
	}
};

struct TexelBufferParameters : public ShaderVarParameters {
	uint32_t m_u32Binding = 0;
	uint32_t m_u32Set = 0;
	uint32_t m_u32Format = 0;

	TexelBufferParameters(uint32_t _u32Binding, uint32_t _u32Set, uint32_t _u32Format)
		: m_u32Binding(_u32Binding)
		, m_u32Set(_u32Set)
		, m_u32Format(_u32Format) {
	}
};

struct ImageParameters : public ShaderVarParameters {
	uint32_t m_u32Binding = 0;
	uint32_t m_u32Set = 0;
	uint8_t m_u8Flags = 0;
	uint32_t m_u32ArraySize = 0;
	uint32_t m_u32Dimension = 0;
	uint32_t m_u32Format = 0;

	ImageParameters(uint32_t _u32Binding, uint32_t _u32Set, uint8_t _u8Flags, uint32_t _u32ArraySize, uint32_t _u32Dimension, uint32_t _u32Format)
		: m_u32Binding(_u32Binding)
		, m_u32Set(_u32Set)
		, m_u8Flags(_u8Flags)
		, m_u32ArraySize(_u32ArraySize)
		, m_u32Dimension(_u32Dimension)
		, m_u32Format(_u32Format) {}
};

struct SamplerParameters : public ShaderVarParameters {

};

struct InputOutputParameters : public ShaderVarParameters {

};

struct SubpassInputParameters : public ShaderVarParameters {

};

struct AccelerationStructureParameters : public ShaderVarParameters {

};

struct ShaderRecordBufferParameters : public ShaderVarParameters {

};

struct AtomicCounterParameters : public ShaderVarParameters {

};

struct GLPlainUniformBufferParameters : public ShaderVarParameters {

};
