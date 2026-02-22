
#include <HellfireControl/UI/UI.hpp>

#include <HellfireControl/Asset/AssetManager.hpp>

#include <HellfireControl/Render/RenderManager.hpp>
#include <HellfireControl/Render/Renderer.hpp>

void UIManager::Init() {
	AssetManager* pamAssetManager = AssetManager::GetInstance();
	RenderManager* prmRenderManager = RenderManager::GetInstance();

	HCUID shdVertId = pamAssetManager->LoadAssetFromPath("./Assets/Shaders/Builtin/test_vert.hcshd");
	HCUID shdFragId = pamAssetManager->LoadAssetFromPath("./Assets/Shaders/Builtin/test_frag.hcshd");

	Shared<Shader> pVertShaderAsset = std::dynamic_pointer_cast<Shader>(pamAssetManager->GetAsset(shdVertId));
	Shared<Shader> pFragShaderAsset = std::dynamic_pointer_cast<Shader>(pamAssetManager->GetAsset(shdFragId));

	if (pVertShaderAsset == nullptr || pFragShaderAsset == nullptr) {
		throw std::runtime_error("Invalid shader assets!");
	}

	m_pUIRenderer = std::make_shared<Renderer>(
		CACHE_FRAME | OUTPUT_FRAME,
		Array<RendererTag>{},
		RenderpassData {
			.m_vAttachments = {
				AttachmentData {
					.m_ifFormat = FORMAT_SWAPCHAIN_DETERMINED,
					.m_u32SampleCount = ATTACHMENT_SAMPLE_COUNT_1_BIT,
					.m_aloLoadOp = ATTACHMENT_LOAD_OP_CLEAR,
					.m_asoStoreOp = ATTACHMENT_STORE_OP_STORE,
					.m_aloStencilLoadOp = ATTACHMENT_LOAD_OP_DONT_CARE,
					.m_asoStencilStoreOp = ATTACHMENT_STORE_OP_DONT_CARE,
					.m_ilInitialLayout = IMAGE_LAYOUT_UNDEFINED,
					.m_ilFinalLayout = IMAGE_LAYOUT_PRESENT_SRC,
					.m_cvClearValue = { .m_v4Color = Vec4F() }
				},
				AttachmentData {
					.m_ifFormat = FORMAT_DEPTH_DETERMINED,
					.m_u32SampleCount = ATTACHMENT_SAMPLE_COUNT_1_BIT,
					.m_aloLoadOp = ATTACHMENT_LOAD_OP_CLEAR,
					.m_asoStoreOp = ATTACHMENT_STORE_OP_DONT_CARE,
					.m_aloStencilLoadOp = ATTACHMENT_LOAD_OP_DONT_CARE,
					.m_asoStencilStoreOp = ATTACHMENT_STORE_OP_DONT_CARE,
					.m_ilInitialLayout = IMAGE_LAYOUT_UNDEFINED,
					.m_ilFinalLayout = IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
					.m_cvClearValue = { .m_fDepth = 1.0f }
				}
			},
			.m_vSubpasses = {
				RenderSubpassData {
					.m_u32Flags = 0,
					.m_pbpBindPoint = PIPELINE_BIND_POINT_GRAPHICS,
					.m_vShaderPipelines = {
						ShaderPipelineData {
							.m_vShaderStages = { pVertShaderAsset, pFragShaderAsset },
							.m_ptPipelineType = PIPELINE_TYPE_GRAPHICS,
							.m_cmCullMode = CULL_MODE_BACK,
							.m_woFrontFace = WINDING_ORDER_CLOCKWISE,
							.m_pmPolygonMode = POLYGON_MODE_FILL,
							.m_coDepthCompareOp = COMPARE_OPERATOR_LESS,
							.m_ptTopology = PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
							.m_sosStencilFront = {},
							.m_sosStencilBack = {},
							.m_bEnableDepthTest = true,
							.m_bEnableDepthWrite = true,
							.m_bEnableStencilTest = false,
							.m_fMinDepthBounds = 1.0f,
							.m_fMaxDepthBounds = 0.0f,
							.m_u32SampleCount = 1,
							.m_vBlendAttachments = {
								BlendAttachmentState {
									.m_bEnableBlend = false,
									.m_bfSrcColorBlendFactor = BLEND_FACTOR_ONE,
									.m_bfDstColorBlendFactor = BLEND_FACTOR_ZERO,
									.m_boColorBlendOp = BLEND_OP_ADD,
									.m_bfSrcAlphaBlendFactor = BLEND_FACTOR_ONE,
									.m_bfDstAlphaBlendFactor = BLEND_FACTOR_ZERO,
									.m_boAlphaBlendOp = BLEND_OP_ADD,
									.m_u32ColorWriteMask = COLOR_COMPONENT_R_BIT | COLOR_COMPONENT_G_BIT | COLOR_COMPONENT_B_BIT | COLOR_COMPONENT_A_BIT
								}
							},
							.m_vDynamicStates = { DYNAMIC_STATE_VIEWPORT, DYNAMIC_STATE_SCISSOR },
						}
					},
					.m_vColorAttachments = {
						AttachmentReference {
							.m_u32AttachmentNdx = 0,
							.m_ilLayout = IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
						}
					},
					.m_arDepthStencilAttachment = {
						.m_u32AttachmentNdx = 1,
						.m_ilLayout = IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
					},
					.m_vInputAttachments = {},
					.m_vResolveAttachments = {},
					.m_vPreserveAttachments = {},
					.m_vDependencies = {
						SubpassDependency {
							.m_u32SrcSubpass = EXTERNAL_SUBPASS,
							.m_u32DstSubpass = 0,
							.m_u32SrcStageMask = PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
							.m_u32DstStageMask = PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
							.m_u32SrcAccessMask = ACCESS_NONE,
							.m_u32DstAccessMask = ACCESS_COLOR_ATTACHMENT_WRITE_BIT | ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
							.m_u32DependencyFlags = 0
						},
					}
				}
			}
		}
	);

	prmRenderManager->AddRenderer(DefaultRendererTags::RENDERER_UI, m_pUIRenderer);
}

void UIManager::Cleanup() {
	Singleton<UIManager>::DestroyInstance();
}