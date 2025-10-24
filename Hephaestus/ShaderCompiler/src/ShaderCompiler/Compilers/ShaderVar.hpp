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

enum HCInputOutputType : uint16_t {
	IO_INVALID = 0,
	IO_BOOL = (1 << 1),
	IO_SIGNED_BYTE = (1 << 2),
	IO_UNSIGNED_BYTE = (1 << 3),
	IO_SIGNED_SHORT = (1 << 4),
	IO_UNSIGNED_SHORT = (1 << 5),
	IO_SIGNED_INT = (1 << 6),
	IO_UNSIGNED_INT = (1 << 7),
	IO_HALF_FLOAT = (1 << 8),
	IO_FLOAT = (1 << 9),
	IO_DOUBLE_FLOAT = (1 << 10)
};

enum HCInterpolationType : uint8_t {
	INTERP_SMOOTH = 0,
	INTERP_FLAT = (1 << 0),
	INTERP_NO_PERSPECTIVE = (1 << 1),
	INTERP_CENTROID = (1 << 2),
	INTERP_SAMPLE = (1 << 3)
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
	uint32_t m_u32Binding = 0;
	uint32_t m_u32Set = 0;
	uint8_t m_u8Flags = 0;
	uint32_t m_u32ArraySize = 0;

	SamplerParameters(uint32_t _u32Binding, uint32_t _u32Set, uint8_t _u8Flags, uint32_t _u32ArraySize)
		: m_u32Binding(_u32Binding)
		, m_u32Set(_u32Set)
		, m_u8Flags(_u8Flags)
		, m_u32ArraySize(_u32ArraySize) {}
};

struct CombinedSamplerParameters : public ShaderVarParameters {
	uint32_t m_u32Binding = 0;
	uint32_t m_u32Set = 0;
	uint8_t m_u8Flags = 0;
	uint32_t m_u32ArraySize = 0;
	uint32_t m_u32Dimension = 0;
	uint32_t m_u32Format = 0;

	CombinedSamplerParameters(uint32_t _u32Binding, uint32_t _u32Set, uint8_t _u8Flags, uint32_t _u32ArraySize, uint32_t _u32Dimension, uint32_t _u32Format)
		: m_u32Binding(_u32Binding)
		, m_u32Set(_u32Set)
		, m_u8Flags(_u8Flags)
		, m_u32ArraySize(_u32ArraySize)
		, m_u32Dimension(_u32Dimension) 
		, m_u32Format(_u32Format) {}
};

struct InputOutputParameters : public ShaderVarParameters {
	uint32_t m_u32Location = 0;
	uint32_t m_u32Component = 0;
	uint16_t m_u16Flags = 0;
	uint32_t m_u32VecSize = 0;
	uint32_t m_u32ColumnSize = 0;
	uint32_t m_u32ArraySize = 0;
	uint8_t m_u8InterpolationType = 0;	

	InputOutputParameters(uint32_t _u32Location, uint32_t _u32Component, uint16_t _u16Flags, uint32_t _u32VecSize, uint32_t _u32ColumnSize, uint32_t _u32ArraySize, uint8_t _u8InterpolationType)
		: m_u32Location(_u32Location)
		, m_u32Component(_u32Component)
		, m_u16Flags(_u16Flags)
		, m_u32VecSize(_u32VecSize)
		, m_u32ColumnSize(_u32ColumnSize)
		, m_u32ArraySize(_u32ArraySize)
		, m_u8InterpolationType(_u8InterpolationType) {}
};

struct BuiltinIOParameters : public ShaderVarParameters {
	uint32_t m_u32BuiltinEnum = 0;
	uint32_t m_u32StorageClass = 0;
	uint16_t m_u16Type = 0;
	uint32_t m_u32VecSize = 0;
	uint32_t m_u32ColumnSize = 0;

	BuiltinIOParameters(uint32_t _u32BuiltinEnum, uint32_t _u32StorageClass, uint16_t _u16Type, uint32_t _u32VecSize, uint32_t _u32ColumnSize)
		: m_u32BuiltinEnum(_u32BuiltinEnum)
		, m_u32StorageClass(_u32StorageClass)
		, m_u16Type(_u16Type)
		, m_u32VecSize(_u32VecSize)
		, m_u32ColumnSize(_u32ColumnSize) {}
};

struct SubpassInputParameters : public ShaderVarParameters {
	uint32_t m_u32Binding = 0;
	uint32_t m_u32Set = 0;
	uint32_t m_u32InputAttachmentIndex = 0;
	uint32_t m_u32Dimension = 0;
	uint32_t m_u32Format = 0;

	SubpassInputParameters(uint32_t _u32Binding,uint32_t _u32Set, uint32_t _u32InputAttachmentIndex, uint32_t _u32Dimension, uint32_t _u32Format)
		: m_u32Binding(_u32Binding)
		, m_u32Set(_u32Set)
		, m_u32InputAttachmentIndex(_u32InputAttachmentIndex)
		, m_u32Dimension(_u32Dimension)
		, m_u32Format(_u32Format) {}
};

struct AccelerationStructureParameters : public ShaderVarParameters {

};

struct ShaderRecordBufferParameters : public ShaderVarParameters {

};

struct AtomicCounterParameters : public ShaderVarParameters {

};

struct GLPlainUniformBufferParameters : public ShaderVarParameters {

};
