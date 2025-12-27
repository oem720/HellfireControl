#pragma once

#include <HellfireControl/Core/Common.hpp>
#include <HellfireControl/Math/Vector.hpp>
#include <HellfireControl/Asset/Shader.hpp>

enum PipelineBindPoint : uint32 {
    PIPELINE_BIND_POINT_GRAPHICS = 0,
    PIPELINE_BIND_POINT_COMPUTE = 1,
    PIPELINE_BIND_POINT_RAY_TRACING = 1000165000
};

enum ImageFormat : int32 {
    FORMAT_SWAPCHAIN_DETERMINED = -2,
    FORMAT_DEPTH_DETERMINED = -1,
    FORMAT_UNDEFINED = 0,
    FORMAT_R8_UNORM = 9,
    FORMAT_R8_SNORM = 10,
    FORMAT_R8_UINT = 13,
    FORMAT_R8_SINT = 14,
    FORMAT_R8_SRGB = 15,
    FORMAT_RG8_UNORM = 16,
    FORMAT_RG8_SNORM = 17,
    FORMAT_RG8_UINT = 20,
    FORMAT_RG8_SINT = 21,
    FORMAT_RG8_SRGB = 22,
    FORMAT_RGB8_UNORM = 23,
    FORMAT_RGB8_SNORM = 24,
    FORMAT_RGB8_UINT = 27,
    FORMAT_RGB8_SINT = 28,
    FORMAT_RGB8_SRGB = 29,
    FORMAT_RGBA8_UNORM = 37,
    FORMAT_RGBA8_SNORM = 38,
    FORMAT_RGBA8_UINT = 41,
    FORMAT_RGBA8_SINT = 42,
    FORMAT_RGBA8_SRGB = 43,
    FORMAT_BGRA8_UNORM = 44,
    FORMAT_BGRA8_SRGB = 50,
    FORMAT_A2R10G10B10_UNORM = 58,
    FORMAT_A2R10G10B10_UINT = 62,
    FORMAT_A2B10G10R10_UNORM = 64,
    FORMAT_A2B10G10R10_UINT = 68,
    FORMAT_R16_UNORM = 70,
    FORMAT_R16_SNORM = 71,
    FORMAT_R16_UINT = 74,
    FORMAT_R16_SINT = 75,
    FORMAT_R16_FLOAT = 76,
    FORMAT_RG16_UNORM = 77,
    FORMAT_RG16_SNORM = 78,
    FORMAT_RG16_UINT = 81,
    FORMAT_RG16_SINT = 82,
    FORMAT_RG16_FLOAT = 83,
    FORMAT_RGB16_UNORM = 84,
    FORMAT_RGB16_SNORM = 85,
    FORMAT_RGB16_UINT = 88,
    FORMAT_RGB16_SINT = 89,
    FORMAT_RGB16_FLOAT = 90,
    FORMAT_RGBA16_UNORM = 91,
    FORMAT_RGBA16_SNORM = 92,
    FORMAT_RGBA16_UINT = 95,
    FORMAT_RGBA16_SINT = 96,
    FORMAT_RGBA16_FLOAT = 97,
    FORMAT_R32_UINT = 98,
    FORMAT_R32_SINT = 99,
    FORMAT_R32_FLOAT = 100,
    FORMAT_RG32_UINT = 101,
    FORMAT_RG32_SINT = 102,
    FORMAT_RG32_FLOAT = 103,
    FORMAT_RGB32_UINT = 104,
    FORMAT_RGB32_SINT = 105,
    FORMAT_RGB32_FLOAT = 106,
    FORMAT_RGBA32_UINT = 107,
    FORMAT_RGBA32_SINT = 108,
    FORMAT_RGBA32_FLOAT = 109,
    FORMAT_R64_FLOAT = 112,
    FORMAT_RG64_FLOAT = 115,
    FORMAT_RGB64_FLOAT = 118,
    FORMAT_RGBA64_FLOAT = 121,
    FORMAT_B10G11R11_FLOAT = 122,
    FORMAT_E5B9G9R9_FLOAT = 123,
    FORMAT_D16_UNORM = 124,
    FORMAT_D32_FLOAT = 126,
    FORMAT_S8_UINT = 127,
    FORMAT_D16_UNORM_S8_UINT = 128,
    FORMAT_D24_UNORM_S8_UINT = 129,
    FORMAT_D32_FLOAT_S8_UINT = 130,
    FORMAT_BC1_UNORM = 131,
    FORMAT_BC1_SRGB = 132,
    FORMAT_BC1_RGBA_UNORM = 133,
    FORMAT_BC1_RGBA_SRGB = 134,
    FORMAT_BC2_UNORM = 135,
    FORMAT_BC2_SRGB = 136,
    FORMAT_BC3_UNORM = 137,
    FORMAT_BC3_SRGB = 138,
    FORMAT_BC4_UNORM = 139,
    FORMAT_BC4_SNORM = 140,
    FORMAT_BC5_UNORM = 141,
    FORMAT_BC5_SNORM = 142,
    FORMAT_BC6H_UFLOAT = 143,
    FORMAT_BC6H_SFLOAT = 144,
    FORMAT_BC7_UNORM = 145,
    FORMAT_BC7_SRGB = 146,
};

enum AttachmentSampleCount : uint32 {
    ATTACHMENT_SAMPLE_COUNT_1_BIT = 1,
    ATTACHMENT_SAMPLE_COUNT_2_BIT = 2,
    ATTACHMENT_SAMPLE_COUNT_4_BIT = 4,
    ATTACHMENT_SAMPLE_COUNT_8_BIT = 8,
    ATTACHMENT_SAMPLE_COUNT_16_BIT = 16,
    ATTACHMENT_SAMPLE_COUNT_32_BIT = 32,
    ATTACHMENT_SAMPLE_COUNT_64_BIT = 64
};

enum AttachmentLoadOp : uint32 {
    ATTACHMENT_LOAD_OP_LOAD = 0,
    ATTACHMENT_LOAD_OP_CLEAR = 1,
    ATTACHMENT_LOAD_OP_DONT_CARE = 2,
    ATTACHMENT_LOAD_OP_NONE = 1000400000
};

enum AttachmentStoreOp : uint32 {
    ATTACHMENT_STORE_OP_STORE = 0,
    ATTACHMENT_STORE_OP_DONT_CARE = 1,
    ATTACHMENT_STORE_OP_NONE = 1000301000
};

enum ImageLayout : uint32 {
    IMAGE_LAYOUT_UNDEFINED = 0,
    IMAGE_LAYOUT_GENERAL = 1,
    IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL = 2,
    IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL = 3,
    IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL = 4,
    IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL = 5,
    IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL = 6,
    IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL = 7,
    IMAGE_LAYOUT_PREINITIALIZED = 8,
    IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL = 1000241000,
    IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL = 1000241001,
    IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL = 1000241002,
    IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL = 1000241003,
    IMAGE_LAYOUT_READ_ONLY_OPTIMAL = 1000314000,
    IMAGE_LAYOUT_ATTACHMENT_OPTIMAL = 1000314001,
    IMAGE_LAYOUT_PRESENT_SRC = 1000001002,
    IMAGE_LAYOUT_ALL = 0x7FFFFFFF
};

enum PipelineType : uint8 {
    PIPELINE_TYPE_GRAPHICS = 0,
    PIPELINE_TYPE_COMPUTE = 1,
    PIPELINE_TYPE_RAY_TRACING = 2
};

enum PolygonMode : uint8 {
    POLYGON_MODE_FILL = 0,
    POLYGON_MODE_LINE = 1,
    POLYGON_MODE_POINT = 2
};

enum CullMode : uint8 {
    CULL_MODE_NONE = 0,
    CULL_MODE_FRONT = 1,
    CULL_MODE_BACK = 2,
    CULL_MODE_FRONT_AND_BACK = 3
};

enum WindingOrder : uint8 {
    WINDING_ORDER_COUNTER_CLOCKWISE = 0,
    WINDING_ORDER_CLOCKWISE = 1
};

enum CompareOperator : uint8 {
    COMPARE_OPERATOR_NEVER = 0,
    COMPARE_OPERATOR_LESS = 1,
    COMPARE_OPERATOR_EQUAL = 2,
    COMPARE_OPERATOR_LESS_OR_EQUAL = 3,
    COMPARE_OPERATOR_GREATER = 4,
    COMPARE_OPERATOR_NOT_EQUAL = 5,
    COMPARE_OPERATOR_GREATER_OR_EQUAL = 6,
    COMPARE_OPERATOR_ALWAYS = 7
};

enum StencilOperator : uint8 {
    STENCIL_OP_KEEP = 0,
    STENCIL_OP_ZERO = 1,
    STENCIL_OP_REPLACE = 2,
    STENCIL_OP_INCREMENT_AND_CLAMP = 3,
    STENCIL_OP_DECREMENT_AND_CLAMP = 4,
    STENCIL_OP_INVERT = 5,
    STENCIL_OP_INCREMENT_AND_WRAP = 6,
    STENCIL_OP_DECREMENT_AND_WRAP = 7,
};

enum PrimitiveTopology : uint8 {
    PRIMITIVE_TOPOLOGY_POINT_LIST = 0,
    PRIMITIVE_TOPOLOGY_LINE_LIST = 1,
    PRIMITIVE_TOPOLOGY_LINE_STRIP = 2,
    PRIMITIVE_TOPOLOGY_TRIANGLE_LIST = 3,
    PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP = 4,
    PRIMITIVE_TOPOLOGY_TRIANGLE_FAN = 5,
    PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY = 6,
    PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY = 7,
    PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY = 8,
    PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY = 9,
    PRIMITIVE_TOPOLOGY_PATCH_LIST = 10
};

enum BlendFactor : uint32 {
    BLEND_FACTOR_ZERO = 0,
    BLEND_FACTOR_ONE = 1,
    BLEND_FACTOR_SRC_COLOR = 2,
    BLEND_FACTOR_ONE_MINUS_SRC_COLOR = 3,
    BLEND_FACTOR_DST_COLOR = 4,
    BLEND_FACTOR_ONE_MINUS_DST_COLOR = 5,
    BLEND_FACTOR_SRC_ALPHA = 6,
    BLEND_FACTOR_ONE_MINUS_SRC_ALPHA = 7,
    BLEND_FACTOR_DST_ALPHA = 8,
    BLEND_FACTOR_ONE_MINUS_DST_ALPHA = 9,
    BLEND_FACTOR_CONSTANT_COLOR = 10,
    BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR = 11,
    BLEND_FACTOR_CONSTANT_ALPHA = 12,
    BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA = 13,
    BLEND_FACTOR_SRC_ALPHA_SATURATE = 14,
    BLEND_FACTOR_SRC1_COLOR = 15,
    BLEND_FACTOR_ONE_MINUS_SRC1_COLOR = 16,
    BLEND_FACTOR_SRC1_ALPHA = 17,
    BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA = 18
};

enum BlendOperator : uint32 {
    BLEND_OP_ADD = 0,
    BLEND_OP_SUBTRACT = 1,
    BLEND_OP_REVERSE_SUBTRACT = 2,
    BLEND_OP_MIN = 3,
    BLEND_OP_MAX = 4
};

enum LogicOperator : uint32 {
    LOGIC_OP_CLEAR = 0,
    LOGIC_OP_AND = 1,
    LOGIC_OP_AND_REVERSE = 2,
    LOGIC_OP_COPY = 3,
    LOGIC_OP_AND_INVERTED = 4,
    LOGIC_OP_NO_OP = 5,
    LOGIC_OP_XOR = 6,
    LOGIC_OP_OR = 7,
    LOGIC_OP_NOR = 8,
    LOGIC_OP_EQUIVALENT = 9,
    LOGIC_OP_INVERT = 10,
    LOGIC_OP_OR_REVERSE = 11,
    LOGIC_OP_COPY_INVERTED = 12,
    LOGIC_OP_OR_INVERTED = 13,
    LOGIC_OP_NAND = 14,
    LOGIC_OP_SET = 15
};

enum ColorComponentFlags : uint8 {
    COLOR_COMPONENT_NONE = 0,
    COLOR_COMPONENT_R_BIT = (1 << 0),
    COLOR_COMPONENT_G_BIT = (1 << 1),
    COLOR_COMPONENT_B_BIT = (1 << 2),
    COLOR_COMPONENT_A_BIT = (1 << 3)
};

enum DynamicState : uint32 {
    DYNAMIC_STATE_VIEWPORT = 0,
    DYNAMIC_STATE_SCISSOR = 1,
    DYNAMIC_STATE_LINE_WIDTH = 2,
    DYNAMIC_STATE_DEPTH_BIAS = 3,
    DYNAMIC_STATE_BLEND_CONSTANTS = 4,
    DYNAMIC_STATE_DEPTH_BOUNDS = 5,
    DYNAMIC_STATE_STENCIL_COMPARE_MASK = 6,
    DYNAMIC_STATE_STENCIL_WRITE_MASK = 7,
    DYNAMIC_STATE_STENCIL_REFERENCE = 8,
    DYNAMIC_STATE_VIEWPORT_WITH_COUNT = 1000267003, //These have been directly pulled from Vulkan. It's possible we may
    DYNAMIC_STATE_SCISSOR_WITH_COUNT = 1000267004   //need to add more of them in the future, but will only do so if requested.
};

enum PipelineStageFlags : uint32 {
    PIPELINE_STAGE_NONE = 0,
    PIPELINE_STAGE_TOP_OF_PIPE_BIT = (1 << 0),
    PIPELINE_STAGE_DRAW_INDIRECT_BIT = (1 << 1),
    PIPELINE_STAGE_VERTEX_INPUT_BIT = (1 << 2),
    PIPELINE_STAGE_VERTEX_SHADER_BIT = (1 << 3),
    PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT = (1 << 4),
    PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT = (1 << 5),
    PIPELINE_STAGE_GEOMETRY_SHADER_BIT = (1 << 6),
    PIPELINE_STAGE_FRAGMENT_SHADER_BIT = (1 << 7),
    PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT = (1 << 8),
    PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT = (1 << 9),
    PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT = (1 << 10),
    PIPELINE_STAGE_COMPUTE_SHADER_BIT = (1 << 11),
    PIPELINE_STAGE_TRANSFER_BIT = (1 << 12),
    PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT = (1 << 13),
    PIPELINE_STAGE_HOST_BIT = (1 << 14),
    PIPELINE_STAGE_ALL_GRAPHICS_BIT = (1 << 15),
    PIPELINE_STAGE_ALL_COMMANDS_BIT = (1 << 16),
    PIPELINE_STAGE_CONDITIONAL_RENDERING_BIT = (1 << 18),
    PIPELINE_STAGE_COMMAND_PREPROCESS_BIT = (1 << 17),
    PIPELINE_STAGE_TASK_SHADER_BIT = (1 << 19),
    PIPELINE_STAGE_MESH_SHADER_BIT = (1 << 20),
    PIPELINE_STAGE_RAY_TRACING_SHADER_BIT = (1 << 21),
    PIPELINE_STAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT = (1 << 22),
    PIPELINE_STAGE_FRAGMENT_DENSITY_PROCESS_BIT = (1 << 23),
    PIPELINE_STAGE_TRANSFORM_FEEDBACK_BIT = (1 << 24),
    PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT = (1 << 25),
    PIPELINE_STAGE_FLAG_BITS_ALL = 0x7FFFFFFF
};

enum AccessFlags : uint32 {
    ACCESS_NONE = 0,
    ACCESS_INDIRECT_COMMAND_READ_BIT = (1 << 0),
    ACCESS_INDEX_READ_BIT = (1 << 1),
    ACCESS_VERTEX_ATTRIBUTE_READ_BIT = (1 << 2),
    ACCESS_UNIFORM_READ_BIT = (1 << 3),
    ACCESS_INPUT_ATTACHMENT_READ_BIT = (1 << 4),
    ACCESS_SHADER_READ_BIT = (1 << 5),
    ACCESS_SHADER_WRITE_BIT = (1 << 6),
    ACCESS_COLOR_ATTACHMENT_READ_BIT = (1 << 7),
    ACCESS_COLOR_ATTACHMENT_WRITE_BIT = (1 << 8),
    ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT = (1 << 9),
    ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT = (1 << 10),
    ACCESS_TRANSFER_READ_BIT = (1 << 11),
    ACCESS_TRANSFER_WRITE_BIT = (1 << 12),
    ACCESS_HOST_READ_BIT = (1 << 13),
    ACCESS_HOST_WRITE_BIT = (1 << 14),
    ACCESS_MEMORY_READ_BIT = (1 << 15),
    ACCESS_MEMORY_WRITE_BIT = (1 << 16),
    ACCESS_COMMAND_PREPROCESS_READ_BIT = (1 << 17),
    ACCESS_COMMAND_PREPROCESS_WRITE_BIT = (1 << 18),
    ACCESS_CONDITIONAL_RENDERING_READ_BIT = (1 << 20),
    ACCESS_COLOR_ATTACHMENT_READ_NONCOHERENT_BIT = (1 << 19),
    ACCESS_FRAGMENT_SHADING_RATE_ATTACHMENT_READ_BIT = (1 << 23),
    ACCESS_ACCELERATION_STRUCTURE_READ_BIT = (1 << 21),
    ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT = (1 << 22),
    ACCESS_FRAGMENT_DENSITY_MAP_READ_BIT = (1 << 24),
    ACCESS_TRANSFORM_FEEDBACK_WRITE_BIT = (1 << 25),
    ACCESS_TRANSFORM_FEEDBACK_COUNTER_READ_BIT = (1 << 26),
    ACCESS_TRANSFORM_FEEDBACK_COUNTER_WRITE_BIT = (1 << 27),
    ACCESS_FLAG_BITS_MAX_ENUM = 0x7FFFFFFF
};

enum DependencyFlags : uint32 {
    DEPENDENCY_BY_REGION_BIT = (1 << 0),
    DEPENDENCY_VIEW_LOCAL_BIT = (1 << 1),
    DEPENDENCY_DEVICE_GROUP_BIT = (1 << 2),
    DEPENDENCY_FLAG_BITS_MAX_ENUM = 0x7FFFFFFF
};

struct StencilOperatorState {
    StencilOperator m_soFailOp = STENCIL_OP_KEEP;
    StencilOperator m_soPassOp = STENCIL_OP_KEEP;
    StencilOperator m_soDepthFailOp = STENCIL_OP_KEEP;
    CompareOperator m_coCompareOp = COMPARE_OPERATOR_NEVER;
    uint32 m_u32CompareMask = 0;
    uint32 m_u32WriteMask = 0;
    uint32 m_u32Reference = 0;
};

struct Viewport {
    float m_fX = 0.0f;
    float m_fY = 0.0f;
    float m_fWidth = 0.0f;
    float m_fHeight = 0.0f;
    float m_fMinDepth = 0.0f;
    float m_fMaxDepth = 1.0f;
};

struct Scissor {
    int32 m_i32OffsetX = 0;
    int32 m_i32OffsetY = 0;
    uint32 m_u32ExtentX = 0;
    uint32 m_u32ExtentY = 0;
};

struct BlendAttachmentState {
    uint32 m_bEnableBlend = false;
    BlendFactor m_bfSrcColorBlendFactor = BLEND_FACTOR_ONE;
    BlendFactor m_bfDstColorBlendFactor = BLEND_FACTOR_ZERO;
    BlendOperator m_boColorBlendOp = BLEND_OP_ADD;
    BlendFactor m_bfSrcAlphaBlendFactor = BLEND_FACTOR_ONE;
    BlendFactor m_bfDstAlphaBlendFactor = BLEND_FACTOR_ZERO;
    BlendOperator m_boAlphaBlendOp = BLEND_OP_ADD;
    uint32 m_u32ColorWriteMask = COLOR_COMPONENT_NONE;
};

struct ShaderPipelineData {
    Array<Shared<Shader>> m_vShaderStages;

	PipelineType m_ptPipelineType = PIPELINE_TYPE_GRAPHICS;
    CullMode m_cmCullMode = CULL_MODE_NONE;
    WindingOrder m_woFrontFace = WINDING_ORDER_COUNTER_CLOCKWISE;
    PolygonMode m_pmPolygonMode = POLYGON_MODE_FILL;
    CompareOperator m_coDepthCompareOp = COMPARE_OPERATOR_NEVER;
    PrimitiveTopology m_ptTopology = PRIMITIVE_TOPOLOGY_POINT_LIST;
	LogicOperator m_loLogicOp = LOGIC_OP_CLEAR;

    StencilOperatorState m_sosStencilFront;
    StencilOperatorState m_sosStencilBack;

	bool m_bEnablePrimitiveRestart = false;
    bool m_bEnableDepthClamp = false;
	bool m_bEnableRasterizerDiscard = false;
	bool m_bEnableDepthBias = false;
    bool m_bEnableSampleShading = false;
	bool m_bEnableAlphaToCoverage = false;
	bool m_bEnableAlphaToOne = false;
    bool m_bEnableDepthTest = true;
    bool m_bEnableDepthWrite = true;
	bool m_bEnableDepthBoundsTest = false;
    bool m_bEnableStencilTest = false;
    bool m_bEnableLogicOperator = false;

    float m_fDepthBiasClamp = 0.0f;
	float m_fDepthBiasSlopeFactor = 0.0f;
	float m_fLineWidth = 1.0f;
	float m_fMinSampleShading = 1.0f;
	float m_fMinDepthBounds = 0.0f;
	float m_fMaxDepthBounds = 1.0f;

	Vec4F m_v4BlendConstants = Vec4F(0.0f, 0.0f, 0.0f, 0.0f);

	uint32 m_u32PatchControlPoints = 0;
    uint32 m_u32SampleCount = 1;

    Array<Viewport> m_vViewports;
    Array<Scissor> m_vScissors;
    Array<uint32> m_vSampleMasks;
    Array<BlendAttachmentState> m_vBlendAttachments;
    Array<DynamicState> m_vDynamicStates;
};

struct ClearValue {
    Vec4F m_v4Color = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);
    float m_fDepth = 1.0f;
    uint32 m_u32Stencil = 0;
};

struct AttachmentData {
    ImageFormat m_ifFormat = FORMAT_UNDEFINED;
    uint32 m_u32SampleCount = ATTACHMENT_SAMPLE_COUNT_1_BIT;
    AttachmentLoadOp m_aloLoadOp = ATTACHMENT_LOAD_OP_DONT_CARE;
    AttachmentStoreOp m_asoStoreOp = ATTACHMENT_STORE_OP_DONT_CARE;
    AttachmentLoadOp m_aloStencilLoadOp = ATTACHMENT_LOAD_OP_DONT_CARE;
    AttachmentStoreOp m_asoStencilStoreOp = ATTACHMENT_STORE_OP_DONT_CARE;
    ImageLayout m_ilInitialLayout = IMAGE_LAYOUT_UNDEFINED;
    ImageLayout m_ilFinalLayout = IMAGE_LAYOUT_UNDEFINED;
    ClearValue m_cvClearValue;
};

struct AttachmentReference {
    uint32 m_u32AttachmentNdx;
    ImageLayout m_ilLayout;
};

constexpr uint32 EXTERNAL_SUBPASS = 0xFFFFFFFF;

struct SubpassDependency {
    uint32 m_u32SrcSubpass;
    uint32 m_u32DstSubpass;
    uint32 m_u32SrcStageMask;
    uint32 m_u32DstStageMask;
    uint32 m_u32SrcAccessMask;
    uint32 m_u32DstAccessMask;
    uint32 m_u32DependencyFlags;
};

struct RenderSubpassData {
    uint32 m_u32Flags = 0;
    PipelineBindPoint m_pbpBindPoint = PIPELINE_BIND_POINT_GRAPHICS;
    Array<ShaderPipelineData> m_vShaderPipelines;
    Array<AttachmentReference> m_vColorAttachments;
    AttachmentReference m_arDepthStencilAttachment;
    Array<AttachmentReference> m_vInputAttachments;
    Array<AttachmentReference> m_vResolveAttachments;
    Array<uint32> m_vPreserveAttachments;
    Array<SubpassDependency> m_vDependencies;
};

struct RenderpassData {
    Array<AttachmentData> m_vAttachments;
    Array<RenderSubpassData> m_vSubpasses;
};