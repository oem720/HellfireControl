
#include <ShaderCompiler/Compilers/Compiler.hpp>

uint32_t GetRuntimeArrayStride(const spirv_cross::Compiler& _cComp, const spirv_cross::Resource& _rRes) {
	const spirv_cross::SPIRType& stType = _cComp.get_type(_rRes.base_type_id);
	const spirv_cross::SPIRType& stLastMemberType = _cComp.get_type(stType.member_types[stType.member_types.size() - 1]);

	bool bIsArray = !stLastMemberType.array.empty();
	bool bIsUnsized = bIsArray && stLastMemberType.array.size() == 1 && (stLastMemberType.array[0] == 0 || !stLastMemberType.array_size_literal[0]);

	if (!bIsArray || !bIsUnsized) {
		return 0;
	}

	return _cComp.type_struct_member_array_stride(stType, stType.member_types.size() - 1);;
}

std::vector<HCShaderVar> ShaderCompiler::ReflectSPIRV(const std::vector<uint32_t>& _vCodeBlob) {
	Console::DebugInfo("Gathering CPU-exposed shader variables...");

	spirv_cross::Compiler cComp(const_cast<uint32_t*>(_vCodeBlob.data()), _vCodeBlob.size());

	//std::unordered_set<spirv_cross::VariableID> active = cComp.get_active_interface_variables();
	spirv_cross::ShaderResources srRes = cComp.get_shader_resources();
	//cComp.set_enabled_interface_variables(std::move(active));

	return ParseShaderVars(cComp, srRes);
}

std::vector<uint32_t> ShaderCompiler::OptimizeSPIRV(const std::vector<uint32_t>& _vCodeBlob) {
	Console::DebugInfo("Attemping to optimize final SPIR-V output...");

	spvtools::Optimizer oOpt(SPV_ENV_VULKAN_1_4);

	oOpt.RegisterPass(spvtools::CreateStripDebugInfoPass()); //Need to explicitly strip the debug info from the shader. Maybe add a way to disable this?
	oOpt.RegisterPerformancePasses();

	std::vector<uint32_t> vOptimizedBlob;

	if (!oOpt.Run(_vCodeBlob.data(), _vCodeBlob.size(), &vOptimizedBlob)) {
		Console::DebugWarn("SPIR-V optimization failed, using original SPIR-V blob");
		vOptimizedBlob = _vCodeBlob;
	}

	Console::DebugSuccess("SPIR-V optimization complete. Final code size: " + std::to_string(vOptimizedBlob.size() * sizeof(uint32_t)) + " bytes");

	return vOptimizedBlob;
}

std::vector<HCShaderVar> ShaderCompiler::ParseShaderVars(const spirv_cross::Compiler& _cComp, const spirv_cross::ShaderResources& _srRes) {
	std::vector<HCShaderVar> vShaderVars;

	//Uniform / Storage Buffers
	{
		for (const auto& aBuffer : _srRes.uniform_buffers) {
			vShaderVars.push_back({
				.m_svtType = VAR_UNIFORM_BUFFER,
				.m_strVarName = _cComp.get_name(aBuffer.id),
				.m_pParameters = std::make_shared<BufferParameters>(
					_cComp.get_decoration(aBuffer.id, spv::DecorationBinding),
					_cComp.get_decoration(aBuffer.id, spv::DecorationDescriptorSet),
					static_cast<uint32_t>(_cComp.get_declared_struct_size(_cComp.get_type(aBuffer.base_type_id))),
					GetRuntimeArrayStride(_cComp, aBuffer)
				)
				});
		}

		for (const auto& aBuffer : _srRes.storage_buffers) {
			vShaderVars.push_back({
				.m_svtType = VAR_STORAGE_BUFFER,
				.m_strVarName = _cComp.get_name(aBuffer.id),
				.m_pParameters = std::make_shared<BufferParameters>(
					_cComp.get_decoration(aBuffer.id, spv::DecorationBinding),
					_cComp.get_decoration(aBuffer.id, spv::DecorationDescriptorSet),
					static_cast<uint32_t>(_cComp.get_declared_struct_size(_cComp.get_type(aBuffer.base_type_id))),
					GetRuntimeArrayStride(_cComp, aBuffer)
				)
				});
		}
	}

	//Push Constants
	{
		for (const auto& aPushConstant : _srRes.push_constant_buffers) {
			vShaderVars.push_back({
				.m_svtType = VAR_PUSH_CONSTANT_BUFFER,
				.m_strVarName = _cComp.get_name(aPushConstant.id),
				.m_pParameters = std::make_shared<PushConstantParameters>(
					_cComp.get_decoration(aPushConstant.id, spv::DecorationOffset),
					static_cast<uint32_t>(_cComp.get_declared_struct_size(_cComp.get_type(aPushConstant.base_type_id)))
				)
			});
		}
	}

	//Storage / Separate Images
	{
		for(const auto& aImage : _srRes.storage_images) {
			spirv_cross::SPIRType stType = _cComp.get_type(aImage.type_id);

			if (stType.image.dim == spv::DimBuffer) {
				vShaderVars.push_back({
					.m_svtType = VAR_STORAGE_TEXEL_BUFFER,
					.m_strVarName = _cComp.get_name(aImage.id),
					.m_pParameters = std::make_shared<TexelBufferParameters>(
						_cComp.get_decoration(aImage.id, spv::DecorationBinding),
						_cComp.get_decoration(aImage.id, spv::DecorationDescriptorSet),
						static_cast<uint32_t>(stType.image.format)
					)
				});
			}
			else {
				const spirv_cross::SPIRType& stType = _cComp.get_type(aImage.type_id);

				uint8_t u8Flags =
					(stType.array.empty() ? 0 : 1) |
					(stType.image.ms ? 0 : (1 << 1));

				vShaderVars.push_back({
					.m_svtType = VAR_IMAGE_2D,
					.m_strVarName = _cComp.get_name(aImage.id),
					.m_pParameters = std::make_shared<ImageParameters>(
						_cComp.get_decoration(aImage.id, spv::DecorationBinding),
						_cComp.get_decoration(aImage.id, spv::DecorationDescriptorSet),
						u8Flags,
						stType.array.empty() ? 0 : stType.array[0],
						stType.image.dim,
						stType.image.format
					)
				});
			}
		}

		for (const auto& aImage : _srRes.separate_images) {
			spirv_cross::SPIRType stType = _cComp.get_type(aImage.type_id);

			if (stType.image.dim == spv::DimBuffer) {
				vShaderVars.push_back({
					.m_svtType = VAR_UNIFORM_TEXEL_BUFFER,
					.m_strVarName = _cComp.get_name(aImage.id),
					.m_pParameters = std::make_shared<TexelBufferParameters>(
						_cComp.get_decoration(aImage.id, spv::DecorationBinding),
						_cComp.get_decoration(aImage.id, spv::DecorationDescriptorSet),
						static_cast<uint32_t>(stType.image.format)
					)
				});
			}
			else {
				const spirv_cross::SPIRType& stType = _cComp.get_type(aImage.type_id);

				uint8_t u8Flags =
					(stType.array.empty() ? 0 : 1) |
					(stType.image.ms ? 0 : (1 << 1));

				vShaderVars.push_back({
					.m_svtType = VAR_TEXTURE_2D,
					.m_strVarName = _cComp.get_name(aImage.id),
					.m_pParameters = std::make_shared<ImageParameters>(
						_cComp.get_decoration(aImage.id, spv::DecorationBinding),
						_cComp.get_decoration(aImage.id, spv::DecorationDescriptorSet),
						u8Flags,
						stType.array.empty() ? 0 : stType.array[0],
						stType.image.dim,
						stType.image.format
					)
					});
			}
		}
	}

	//Samplers
	{
		for (const auto& aSampler : _srRes.sampled_images) {
			vShaderVars.push_back({
				.m_svtType = VAR_COMBINED_IMAGE_SAMPLER,
				.m_strVarName = _cComp.get_name(aSampler.id),
				.m_pParameters = std::make_shared<SamplerParameters>(

				)
			});
		}

		for (const auto& aSampler : _srRes.separate_samplers) {
			vShaderVars.push_back({
				.m_svtType = VAR_SAMPLER,
				.m_strVarName = _cComp.get_name(aSampler.id),
				.m_pParameters = std::make_shared<SamplerParameters>(

				)
			});
		}
	}

	//Inputs
	{
		for (const auto& aInput : _srRes.stage_inputs) {
			vShaderVars.push_back({
				.m_svtType = VAR_STAGE_INPUTS,
				.m_strVarName = _cComp.get_name(aInput.id),
				.m_pParameters = std::make_shared<SamplerParameters>(

				)
			});
		}

		for (const auto& aSubpassInput : _srRes.subpass_inputs) {
			vShaderVars.push_back({
				.m_svtType = VAR_SUBPASS_INPUT,
				.m_strVarName = _cComp.get_name(aSubpassInput.id),
				.m_pParameters = std::make_shared<SamplerParameters>(

				)
			});
		}
	}

	return vShaderVars;
}