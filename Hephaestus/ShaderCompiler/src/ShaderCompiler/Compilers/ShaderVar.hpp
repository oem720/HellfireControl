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
	IO_DOUBLE_FLOAT = (1 << 10),
	IO_MAX = 0x7FE
};

enum HCInterpolationType : uint8_t {
	INTERP_SMOOTH = 0,
	INTERP_FLAT = (1 << 0),
	INTERP_NO_PERSPECTIVE = (1 << 1),
	INTERP_CENTROID = (1 << 2),
	INTERP_SAMPLE = (1 << 3)
};

struct HCShaderVar {
	HCShaderVarType m_svtType;

	//Flag values
	uint8_t  m_u8InterpolationType = 0;
	uint16_t m_u16Flags = 0; 

	//Common descriptor set / binding info
	uint32_t m_u32Binding = 0;
	uint32_t m_u32Set = 0;

	//Common type / format info
	uint32_t m_u32Format = 0;   
	uint32_t m_u32Dimension = 0;

	//Size / memory layout
	uint32_t m_u32StaticSize = 0;  
	uint32_t m_u32Offset = 0;
	uint32_t m_u32UnsizedArrayStride = 0;
	uint32_t m_u32StaticArraySize = 0;

	//Array and vector/matrix info
	uint32_t m_u32VecSize = 0;   
	uint32_t m_u32ColumnSize = 0;

	//Input/output specific
	uint32_t m_u32Location = 0;
	uint32_t m_u32Component = 0;

	//Builtin IO
	uint32_t m_u32BuiltinEnum = 0;

	//Subpass input
	uint32_t m_u32InputAttachmentIndex = 0;
};