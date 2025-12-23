
#include <HellfireControl/Asset/Converters/Shader/Compiler.hpp>

Map<uint32, String> ShaderCompiler::m_mImageFormatNames = {
	{spv::ImageFormatUnknown, "UNKNOWN"},
	{spv::ImageFormatRgba32f, "RGBA32F"},
	{spv::ImageFormatRgba16f, "RGBA16F"},
	{spv::ImageFormatR32f, "R32F"},
	{spv::ImageFormatRgba8, "RGBA8"},
	{spv::ImageFormatRgba8Snorm, "RGBA8 SNORM"},
	{spv::ImageFormatRg32f, "RG32F"},
	{spv::ImageFormatRg16f, "RG16F"},
	{spv::ImageFormatR11fG11fB10f, "R11FG11FB10F"},
	{spv::ImageFormatR16f, "R16F"},
	{spv::ImageFormatRgba16, "RGBA16F"},
	{spv::ImageFormatRgb10A2, "RGB10A2"},
	{spv::ImageFormatRg16, "RG16"},
	{spv::ImageFormatRg8, "RG8"},
	{spv::ImageFormatR16, "R16"},
	{spv::ImageFormatR8, "R8"},
	{spv::ImageFormatRgba16Snorm, "RGBA16 SNORM"},
	{spv::ImageFormatRg16Snorm, "RG16 SNORM" },
	{spv::ImageFormatRg8Snorm, "RG8 SNORM"},
	{spv::ImageFormatR16Snorm, "R16 SNORM"},
	{spv::ImageFormatR8Snorm, "R8 SNORM"},
	{spv::ImageFormatRgba32i, "RGBA32I"},
	{spv::ImageFormatRgba16i, "RGBA16I"},
	{spv::ImageFormatRgba8i, "RGBA8I"},
	{spv::ImageFormatR32i, "R32I"},
	{spv::ImageFormatRg32i, "RG32I"},
	{spv::ImageFormatRg16i, "RG16I"},
	{spv::ImageFormatRg8i, "RG8I"},
	{spv::ImageFormatR16i, "R16I"},
	{spv::ImageFormatR8i, "R8I"},
	{spv::ImageFormatRgba32ui, "RGBA32UI"},
	{spv::ImageFormatRgba16ui, "RGBA16UI"},
	{spv::ImageFormatRgba8ui, "RGBA8UI"},
	{spv::ImageFormatR32ui, "R32UI"},
	{spv::ImageFormatRgb10a2ui, "RGB10A2UI"},
	{spv::ImageFormatRg32ui, "RG32UI"},
	{spv::ImageFormatRg16ui, "RG16UI"},
	{spv::ImageFormatRg8ui, "RG8UI"},
	{spv::ImageFormatR16ui, "R16UI"},
	{spv::ImageFormatR8ui, "R8UI"},
	{spv::ImageFormatR64ui, "R64UI"},
	{spv::ImageFormatR64i, "R64I"},
	{spv::ImageFormatMax, "ERROR"}
};

Map<uint32, String> ShaderCompiler::m_mImageDimensions = {
	{spv::Dim1D, "1D"},
	{spv::Dim2D, "2D"},
	{spv::Dim3D, "3D"},
	{spv::DimCube, "Cube Map"},
	{spv::DimRect, "Rect"},
	{spv::DimBuffer, "Buffer"},
	{spv::DimSubpassData, "Subpass"}, 
	{spv::DimTileImageDataEXT, "Tile Image Data"},
	{spv::DimMax, "ERROR"}
};

Map<uint16, String> ShaderCompiler::m_mTypeNames = {
	{IO_INVALID, "INVALID"},
	{IO_BOOL, "Boolean"},
	{IO_SIGNED_BYTE, "Signed Byte"},
	{IO_UNSIGNED_BYTE, "Unsigned Byte"},
	{IO_SIGNED_SHORT, "Signed Short"},
	{IO_UNSIGNED_SHORT, "Unsigned Short"},
	{IO_SIGNED_INT, "Signed Integer"},
	{IO_UNSIGNED_INT, "Unsigned Integer"},
	{IO_HALF_FLOAT, "Half-precision Float"},
	{IO_FLOAT, "Float"},
	{IO_DOUBLE_FLOAT, "Double-precision Float"}
};

Map<uint32, String> ShaderCompiler::m_mBuiltinNames = {
	{spv::BuiltInPosition, "Position"},
	{spv::BuiltInPointSize, "Point Size"},
	{spv::BuiltInClipDistance, "Clip Distance"},
	{spv::BuiltInCullDistance, "Cull Distance"},
	{spv::BuiltInVertexId, "Vertex ID"},
	{spv::BuiltInInstanceId, "Instance ID"},
	{spv::BuiltInPrimitiveId, "Primitive ID"},
	{spv::BuiltInInvocationId, "Invocation ID"},
	{spv::BuiltInLayer, "Layer"},
	{spv::BuiltInViewportIndex, "Viewport Index"},
	{spv::BuiltInTessLevelOuter, "Tessellation Level Outer"},
	{spv::BuiltInTessLevelInner, "Tessellation Level Inner"},
	{spv::BuiltInTessCoord, "Tessellation Coordinate"},
	{spv::BuiltInPatchVertices, "Patch Vertices"},
	{spv::BuiltInFragCoord, "Fragment Coordinate"},
	{spv::BuiltInPointCoord, "Point Coordinate"},
	{spv::BuiltInFrontFacing, "Front Facing"},
	{spv::BuiltInSampleId, "Sample ID"},
	{spv::BuiltInSamplePosition, "Sample Position"},
	{spv::BuiltInSampleMask, "Sample Mask"},
	{spv::BuiltInFragDepth, "Fragment Depth"},
	{spv::BuiltInHelperInvocation, "Helper Invocation"},
	{spv::BuiltInNumWorkgroups, "Number of Work Groups"},
	{spv::BuiltInWorkgroupSize, "Work Group Size"},
	{spv::BuiltInWorkgroupId, "Work Group ID"},
	{spv::BuiltInLocalInvocationId, "Local Invocation ID"},
	{spv::BuiltInGlobalInvocationId, "Global Invocation ID"},
	{spv::BuiltInLocalInvocationIndex, "Local Invocation Index"},
	{spv::BuiltInWorkDim, "Work Dimension"},
	{spv::BuiltInGlobalSize, "Global Size"},
	{spv::BuiltInEnqueuedWorkgroupSize, "Enqueued Work Group Size"},
	{spv::BuiltInGlobalOffset, "Global Offset"},
	{spv::BuiltInGlobalLinearId, "Global Linear ID"},
	{spv::BuiltInSubgroupSize, "Subgroup Size"},
	{spv::BuiltInSubgroupMaxSize, "Subgroup Maximum Size"},
	{spv::BuiltInNumSubgroups, "Number of Subgroups"},
	{spv::BuiltInNumEnqueuedSubgroups, "Number of Enqueued Subgroups"},
	{spv::BuiltInSubgroupId, "Subgroup ID"},
	{spv::BuiltInSubgroupLocalInvocationId, "Subgroup Local Invocation ID"},
	{spv::BuiltInVertexIndex, "Vertex Index"},
	{spv::BuiltInInstanceIndex, "Instance Index"},
	{spv::BuiltInCoreIDARM, "Core ID"},
	{spv::BuiltInCoreCountARM, "Core Count"},
	{spv::BuiltInCoreMaxIDARM, "Core Maximum ID"},
	{spv::BuiltInWarpIDARM, "Warp ID"},
	{spv::BuiltInWarpMaxIDARM, "Warp Maximum ID"},
	{spv::BuiltInSubgroupEqMask, "Subgroup Equal Mask"},
	{spv::BuiltInSubgroupGeMask, "Subgroup Greater or Equal Mask"},
	{spv::BuiltInSubgroupGtMask, "Subgroup Greater Mask"},
	{spv::BuiltInSubgroupLeMask, "Subgroup Less or Equal Mask"},
	{spv::BuiltInSubgroupLtMask, "Subgroup Less Mask"},
	{spv::BuiltInBaseVertex, "Base Vertex"},
	{spv::BuiltInBaseInstance, "Base Instance"},
	{spv::BuiltInDrawIndex, "Draw Index"},
	{spv::BuiltInPrimitiveShadingRateKHR, "Primitive Shading Rate"},
	{spv::BuiltInDeviceIndex, "Device Index"},
	{spv::BuiltInViewIndex, "View Index"},
	{spv::BuiltInShadingRateKHR, "Shading Rate"},
	{spv::BuiltInBaryCoordNoPerspAMD, "Barycentric Coordinate No Perspective"},
	{spv::BuiltInBaryCoordNoPerspCentroidAMD, "Barycentric Coordinate No Perspective Centroid"},
	{spv::BuiltInBaryCoordNoPerspSampleAMD, "Barycentric Coordinate No Perspective Sample"},
	{spv::BuiltInBaryCoordSmoothAMD, "Barycentric Coordinate Smooth"},
	{spv::BuiltInBaryCoordSmoothCentroidAMD, "Barycentric Coordinate Smooth Centroid"},
	{spv::BuiltInBaryCoordSmoothSampleAMD, "Barycentric Coordinate Smooth Sample"},
	{spv::BuiltInBaryCoordPullModelAMD, "Barycentric Coordinate Pull Model"},
	{spv::BuiltInFragStencilRefEXT, "Fragment Stencil Reference"},
	{spv::BuiltInRemainingRecursionLevelsAMDX, "Remaining Recursion Levels"},
	{spv::BuiltInShaderIndexAMDX, "Shader Index"},
	{spv::BuiltInViewportMaskNV, "Viewport Mask"},
	{spv::BuiltInSecondaryPositionNV, "Secondary Position"},
	{spv::BuiltInSecondaryViewportMaskNV, "Secondary Viewport Mask"},
	{spv::BuiltInPositionPerViewNV, "Position Per View"},
	{spv::BuiltInViewportMaskPerViewNV, "Viewport Mask Per View"},
	{spv::BuiltInFullyCoveredEXT, "Fully Covered"},
	{spv::BuiltInTaskCountNV, "Task Count"},
	{spv::BuiltInPrimitiveCountNV, "Primitive Count"},
	{spv::BuiltInPrimitiveIndicesNV, "Primitive Indices"},
	{spv::BuiltInClipDistancePerViewNV, "Clip Distance Per View"},
	{spv::BuiltInCullDistancePerViewNV, "Cull Distance Per View"},
	{spv::BuiltInLayerPerViewNV, "Layer Per View"},
	{spv::BuiltInMeshViewCountNV, "Mesh View Count"},
	{spv::BuiltInMeshViewIndicesNV, "Mesh View Indices"},
	{spv::BuiltInBaryCoordKHR, "Barycentric Coordinate"},
	{spv::BuiltInBaryCoordNoPerspKHR, "Barycentric Coordinate No Perspective"},
	{spv::BuiltInFragSizeEXT, "Fragment Size"},
	{spv::BuiltInFragInvocationCountEXT, "Fragment Invocation Count"},
	{spv::BuiltInPrimitivePointIndicesEXT, "Primitive Point Indices"},
	{spv::BuiltInPrimitiveLineIndicesEXT, "Primitive Line Indices"},
	{spv::BuiltInPrimitiveTriangleIndicesEXT, "Primitive Triangle Indices"},
	{spv::BuiltInCullPrimitiveEXT, "Cull Primitive"},
	{spv::BuiltInLaunchIdKHR, "Launch ID"},
	{spv::BuiltInLaunchSizeKHR, "Launch Size"},
	{spv::BuiltInWorldRayOriginKHR, "World Ray Origin"},
	{spv::BuiltInWorldRayDirectionKHR, "World Ray Direction"},
	{spv::BuiltInObjectRayOriginKHR, "Object Ray Origin"},
	{spv::BuiltInObjectRayDirectionKHR, "Object Ray Direction"},
	{spv::BuiltInRayTminKHR, "Ray T Minimum"},
	{spv::BuiltInRayTmaxKHR, "Ray T Maximum"},
	{spv::BuiltInInstanceCustomIndexKHR, "Instance Custom Index"},
	{spv::BuiltInObjectToWorldKHR, "Object To World"},
	{spv::BuiltInWorldToObjectKHR, "World To Object"},
	{spv::BuiltInHitTNV, "Hit T"},
	{spv::BuiltInHitKindKHR, "Hit Kind"},
	{spv::BuiltInCurrentRayTimeNV, "Current Ray Time"},
	{spv::BuiltInHitTriangleVertexPositionsKHR, "Hit Triangle Vertex Positions"},
	{spv::BuiltInHitMicroTriangleVertexPositionsNV, "Hit Micro Triangle Vertex Positions"},
	{spv::BuiltInHitMicroTriangleVertexBarycentricsNV, "Hit Micro Triangle Vertex Barycentrics"},
	{spv::BuiltInIncomingRayFlagsKHR, "Incoming Ray Flags"},
	{spv::BuiltInRayGeometryIndexKHR, "Ray Geometry Index"},
	{spv::BuiltInHitIsSphereNV, "Hit Is Sphere"},
	{spv::BuiltInHitIsLSSNV, "Hit Is LSS"},
	{spv::BuiltInHitSpherePositionNV, "Hit Sphere Position"},
	{spv::BuiltInWarpsPerSMNV, "Warps Per SM"},
	{spv::BuiltInSMCountNV, "SM Count"},
	{spv::BuiltInWarpIDNV, "Warp ID"},
	{spv::BuiltInSMIDNV, "SM ID"},
	{spv::BuiltInHitLSSPositionsNV, "Hit LSS Positions"},
	{spv::BuiltInHitKindFrontFacingMicroTriangleNV, "Hit Kind Front Facing Micro Triangle"},
	{spv::BuiltInHitKindBackFacingMicroTriangleNV, "Hit Kind Back Facing Micro Triangle"},
	{spv::BuiltInHitSphereRadiusNV, "Hit Sphere Radius"},
	{spv::BuiltInHitLSSRadiiNV, "Hit LSS Radii"},
	{spv::BuiltInClusterIDNV, "Cluster ID"},
	{spv::BuiltInCullMaskKHR, "Cull Mask"},
	{spv::BuiltInMax, "ERROR"},
};

uint32 GetRuntimeArrayStride(const spirv_cross::Compiler& _cComp, const spirv_cross::Resource& _rRes) {
	const spirv_cross::SPIRType& stType = _cComp.get_type(_rRes.base_type_id);
	const spirv_cross::SPIRType& stLastMemberType = _cComp.get_type(stType.member_types[stType.member_types.size() - 1]);

	bool bIsArray = !stLastMemberType.array.empty();
	bool bIsUnsized = bIsArray && stLastMemberType.array.size() == 1 && (stLastMemberType.array[0] == 0 || !stLastMemberType.array_size_literal[0]);

	if (!bIsArray || !bIsUnsized) {
		return 0;
	}

	return _cComp.type_struct_member_array_stride(stType, stType.member_types.size() - 1);;
}

uint16 TranslateBaseTypeToFlag(const spirv_cross::SPIRType::BaseType _btType) {
	switch (_btType) {
	case spirv_cross::SPIRType::BaseType::Boolean: return IO_BOOL;
	case spirv_cross::SPIRType::BaseType::SByte: return IO_SIGNED_BYTE;
	case spirv_cross::SPIRType::BaseType::UByte: return IO_UNSIGNED_BYTE;
	case spirv_cross::SPIRType::BaseType::Short: return IO_SIGNED_SHORT;
	case spirv_cross::SPIRType::BaseType::UShort: return IO_UNSIGNED_SHORT;
	case spirv_cross::SPIRType::BaseType::Int: return IO_SIGNED_INT;
	case spirv_cross::SPIRType::BaseType::UInt: return IO_UNSIGNED_INT;
	case spirv_cross::SPIRType::BaseType::Half: return IO_HALF_FLOAT;
	case spirv_cross::SPIRType::BaseType::Float: return IO_FLOAT;
	case spirv_cross::SPIRType::BaseType::Double: return IO_DOUBLE_FLOAT;
	default: return IO_INVALID;
	}
}

uint32 SizeofBaseType(const spirv_cross::SPIRType::BaseType _btType) {
	switch (_btType) {
	case spirv_cross::SPIRType::BaseType::SByte:
	case spirv_cross::SPIRType::BaseType::UByte:
		return 1;
	case spirv_cross::SPIRType::BaseType::Short:
	case spirv_cross::SPIRType::BaseType::UShort:
	case spirv_cross::SPIRType::BaseType::Half:
		return 2;
	case spirv_cross::SPIRType::BaseType::Boolean:
	case spirv_cross::SPIRType::BaseType::Int:
	case spirv_cross::SPIRType::BaseType::UInt:
	case spirv_cross::SPIRType::BaseType::Float:
		return 4;
	case spirv_cross::SPIRType::BaseType::Double:
		return 8;
	default: return 0;
	}
}

String ConstructInterpolationString(uint16 _u16Flag) {
	String strInterpolatedString;

	if ((_u16Flag & INTERP_SMOOTH) == 0) strInterpolatedString += "Smooth ";
	if (_u16Flag & INTERP_FLAT) strInterpolatedString += strInterpolatedString.empty() ? "Flat " : "| Flat ";
	if (_u16Flag & INTERP_NO_PERSPECTIVE) strInterpolatedString += strInterpolatedString.empty() ? "No Perspective " : "| No Perspective ";
	if (_u16Flag & INTERP_CENTROID) strInterpolatedString += strInterpolatedString.empty() ? "Centroid " : "| Centroid ";
	if (_u16Flag & INTERP_SAMPLE) strInterpolatedString += strInterpolatedString.empty() ? "Sample " : "| Sample ";

	return strInterpolatedString;
}

HCShaderVarTable ShaderCompiler::HCShaderVarTableReflectSPIRV(const Array<uint32>& _vCodeBlob) {
	Console::DebugInfo("Gathering CPU-exposed shader variables...");

	spirv_cross::Compiler cComp(const_cast<uint32*>(_vCodeBlob.data()), _vCodeBlob.size());

	std::unordered_set<spirv_cross::VariableID> active = cComp.get_active_interface_variables();
	spirv_cross::ShaderResources srRes = cComp.get_shader_resources();
	cComp.set_enabled_interface_variables(std::move(active));

	Map<String, HCShaderVar> vVars = ParseShaderVars(cComp, srRes);

	HCShaderVarTable svtTable = {};

	for (const auto& aPair : vVars) {
		svtTable.m_vLabels.push_back({
			.m_strVarName = aPair.first,
			.m_u32Index = static_cast<uint32>(svtTable.m_vVars.size())
		});

		svtTable.m_vVars.push_back(aPair.second);
	}

	return svtTable;
}

Array<uint32> ShaderCompiler::OptimizeSPIRV(const Array<uint32>& _vCodeBlob) {
	Console::DebugInfo("Attemping to optimize final SPIR-V output...");

	spvtools::Optimizer oOpt(SPV_ENV_VULKAN_1_4);

	oOpt.RegisterPass(spvtools::CreateStripDebugInfoPass()); //Need to explicitly strip the debug info from the shader. Maybe add a way to disable this?
	oOpt.RegisterPerformancePasses();

	Array<uint32> vOptimizedBlob;

	if (!oOpt.Run(_vCodeBlob.data(), _vCodeBlob.size(), &vOptimizedBlob)) {
		Console::DebugWarn("SPIR-V optimization failed, using original SPIR-V blob");
		vOptimizedBlob = _vCodeBlob;
	}

	Console::DebugSuccess("SPIR-V optimization complete. Final code size: " + std::to_string(vOptimizedBlob.size() * sizeof(uint32)) + " bytes");

	return vOptimizedBlob;
}

Map<String, HCShaderVar> ShaderCompiler::ParseShaderVars(const spirv_cross::Compiler& _cComp, const spirv_cross::ShaderResources& _srRes) {
	Map<String, HCShaderVar> mShaderVars;

	//Uniform / Storage Buffers
	{
		for (const auto& aBuffer : _srRes.uniform_buffers) {
			HCShaderVar svUniform = {
				.m_u16Type = VAR_UNIFORM_BUFFER,
				.m_u16Flags = 0,
				.m_arrData = {
					_cComp.get_decoration(aBuffer.id, spv::DecorationBinding),
					_cComp.get_decoration(aBuffer.id, spv::DecorationDescriptorSet),
					static_cast<uint32>(_cComp.get_declared_struct_size(_cComp.get_type(aBuffer.base_type_id))),
					GetRuntimeArrayStride(_cComp, aBuffer)
				}
			};

			String strName = _cComp.get_name(aBuffer.id);
		
			Console::DebugInfo("Found Uniform Buffer: \"" + strName + "\". Parameters:\n"
				+ "\tBinding: " + std::to_string(svUniform.m_arrData[0]) + "\n"
				+ "\tDescriptor Set: " + std::to_string(svUniform.m_arrData[1]) + "\n"
				+ "\tStatic Size: " + std::to_string(svUniform.m_arrData[2]) + " bytes\n"
				+ "\tRuntime Array Stride: " + std::to_string(svUniform.m_arrData[3]) + " bytes"
			);
		
			mShaderVars[strName] = svUniform;
		}

		for (const auto& aBuffer : _srRes.storage_buffers) {
			HCShaderVar svStorage = {
				.m_u16Type = VAR_STORAGE_BUFFER,
				.m_u16Flags = 0,
				.m_arrData = {
					_cComp.get_decoration(aBuffer.id, spv::DecorationBinding),
					_cComp.get_decoration(aBuffer.id, spv::DecorationDescriptorSet),
					static_cast<uint32>(_cComp.get_declared_struct_size(_cComp.get_type(aBuffer.base_type_id))),
					GetRuntimeArrayStride(_cComp, aBuffer)
				}
			};

			String strName = _cComp.get_name(aBuffer.id);
		
			Console::DebugInfo("Found Storage Buffer: \"" + strName + "\". Parameters:\n"
				+ "\tBinding: " + std::to_string(svStorage.m_arrData[0]) + "\n"
				+ "\tDescriptor Set: " + std::to_string(svStorage.m_arrData[1]) + "\n"
				+ "\tStatic Size: " + std::to_string(svStorage.m_arrData[2]) + " bytes\n"
				+ "\tRuntime Array Stride: " + std::to_string(svStorage.m_arrData[3]) + " bytes"
			);
		
			mShaderVars[strName] = svStorage;
		}
	}

	//Push Constants
	{
		for (const auto& aPushConstant : _srRes.push_constant_buffers) {
			HCShaderVar svPushConstant = {
				.m_u16Type = VAR_PUSH_CONSTANT_BUFFER,
				.m_u16Flags = 0,
				.m_arrData = {
					_cComp.get_decoration(aPushConstant.id, spv::DecorationOffset),
					static_cast<uint32>(_cComp.get_declared_struct_size(_cComp.get_type(aPushConstant.base_type_id)))
				}
			};

			String strName = _cComp.get_name(aPushConstant.id);

			Console::DebugInfo("Found Push Constant Buffer: \"" + strName + "\". Parameters:\n"
				+ "\tOffset: " + std::to_string(svPushConstant.m_arrData[0]) + "\n"
				+ "\tSize: " + std::to_string(svPushConstant.m_arrData[1]) + " bytes"
			);

			mShaderVars[strName] = svPushConstant;
		}
	}

	//Storage / Separate Images
	{
		for (const auto& aImage : _srRes.storage_images) {
			spirv_cross::SPIRType stType = _cComp.get_type(aImage.type_id);

			uint16 u16Flags = (stType.array.empty() ? 0 : 1);

			HCShaderVar svImageVar;

			String strName = _cComp.get_name(aImage.id);

			if (stType.image.dim == spv::DimBuffer) {
				svImageVar = {
					.m_u16Type = VAR_STORAGE_TEXEL_BUFFER,
					.m_u16Flags = u16Flags,
					.m_arrData = {
						_cComp.get_decoration(aImage.id, spv::DecorationBinding),
						_cComp.get_decoration(aImage.id, spv::DecorationDescriptorSet),
						stType.array.empty() ? 0 : stType.array[0],
						static_cast<uint32>(stType.image.format)
					}
				};

				Console::DebugInfo("Found Storage Texel Buffer: \"" + strName + "\". Parameters:\n"
					+ "\tBinding: " + std::to_string(svImageVar.m_arrData[0]) + "\n"
					+ "\tDescriptor Set: " + std::to_string(svImageVar.m_arrData[1]) + "\n"
					+ "\tIs Array: " + (svImageVar.m_u16Flags & 1 ? "true" : "false") + "\n"
					+ "\tIs Unsized Array: " + ((svImageVar.m_u16Flags & 1) && svImageVar.m_arrData[2] == 0 ? "true" : "false") + "\n"
					+ "\tArray Size (if not runtime): " + std::to_string(svImageVar.m_arrData[2]) + "\n"
					+ "\tFormat: " + m_mImageFormatNames[svImageVar.m_arrData[3]]
				);
			}
			else {
				const spirv_cross::SPIRType& stType = _cComp.get_type(aImage.type_id);

				uint16 u16Flags = (stType.array.empty() ? 0 : 1) | (stType.image.ms ? 0 : (1 << 1));

				svImageVar = {
					.m_u16Type = VAR_IMAGE_2D,
					.m_u16Flags = u16Flags,
					.m_arrData = {
						_cComp.get_decoration(aImage.id, spv::DecorationBinding),
						_cComp.get_decoration(aImage.id, spv::DecorationDescriptorSet),
						stType.array.empty() ? 0 : stType.array[0],
						static_cast<uint32>(stType.image.dim),
						static_cast<uint32>(stType.image.format)
					}
				};

				Console::DebugInfo("Found Image 2D: \"" + strName + "\". Parameters:\n"
					+ "\tBinding: " + std::to_string(svImageVar.m_arrData[0]) + "\n"
					+ "\tDescriptor Set: " + std::to_string(svImageVar.m_arrData[1]) + "\n"
					+ "\tIs Array: " + (svImageVar.m_u16Flags & 1 ? "true" : "false") + "\n"
					+ "\tIs Unsized Array: " + ((svImageVar.m_u16Flags & 1) && svImageVar.m_arrData[2] == 0 ? "true" : "false") + "\n"
					+ "\tIs Multisampled: " + (svImageVar.m_u16Flags & 2 ? "true" : "false") + "\n"
					+ "\tArray Size (if not runtime): " + std::to_string(svImageVar.m_arrData[2]) + "\n"
					+ "\tDimensions: " + m_mImageDimensions[svImageVar.m_arrData[3]] + "\n"
					+ "\tFormat: " + m_mImageFormatNames[svImageVar.m_arrData[4]]
				);
			}
			
			mShaderVars[strName] = svImageVar;
		}

		for (const auto& aImage : _srRes.separate_images) {
			spirv_cross::SPIRType stType = _cComp.get_type(aImage.type_id);

			uint16 u16Flags = (stType.array.empty() ? 0 : 1);

			HCShaderVar svImageVar;

			String strName = _cComp.get_name(aImage.id);

			if (stType.image.dim == spv::DimBuffer) {
				svImageVar = {
					.m_u16Type = VAR_UNIFORM_TEXEL_BUFFER,
					.m_u16Flags = u16Flags,
					.m_arrData = {
						_cComp.get_decoration(aImage.id, spv::DecorationBinding),
						_cComp.get_decoration(aImage.id, spv::DecorationDescriptorSet),
						stType.array.empty() ? 0 : stType.array[0],
						static_cast<uint32>(stType.image.format)
					}
				};

				Console::DebugInfo("Found Uniform Texel Buffer: \"" + strName + "\". Parameters:\n"
					+ "\tBinding: " + std::to_string(svImageVar.m_arrData[0]) + "\n"
					+ "\tDescriptor Set: " + std::to_string(svImageVar.m_arrData[1]) + "\n"
					+ "\tIs Array: " + (svImageVar.m_u16Flags & 1 ? "true" : "false") + "\n"
					+ "\tIs Unsized Array: " + ((svImageVar.m_u16Flags & 1) && svImageVar.m_arrData[2] == 0 ? "true" : "false") + "\n"
					+ "\tArray Size (if not runtime): " + std::to_string(svImageVar.m_arrData[2]) + "\n"
					+ "\tFormat: " + m_mImageFormatNames[svImageVar.m_arrData[3]]
				);
			}
			else {
				const spirv_cross::SPIRType& stType = _cComp.get_type(aImage.type_id);

				uint16 u16Flags = (stType.array.empty() ? 0 : 1) | (stType.image.ms ? 0 : (1 << 1));

				svImageVar = {
					.m_u16Type = VAR_TEXTURE_2D,
					.m_u16Flags = u16Flags,
					.m_arrData = {
						_cComp.get_decoration(aImage.id, spv::DecorationBinding),
						_cComp.get_decoration(aImage.id, spv::DecorationDescriptorSet),
						stType.array.empty() ? 0 : stType.array[0],
						static_cast<uint32>(stType.image.dim),
						static_cast<uint32>(stType.image.format)
					}
				};

				Console::DebugInfo("Found Texture 2D: \"" + strName + "\". Parameters:\n"
					+ "\tBinding: " + std::to_string(svImageVar.m_arrData[0]) + "\n"
					+ "\tDescriptor Set: " + std::to_string(svImageVar.m_arrData[1]) + "\n"
					+ "\tIs Array: " + (svImageVar.m_u16Flags & 1 ? "true" : "false") + "\n"
					+ "\tIs Unsized Array: " + ((svImageVar.m_u16Flags & 1) && svImageVar.m_arrData[2] == 0 ? "true" : "false") + "\n"
					+ "\tIs Multisampled: " + (svImageVar.m_u16Flags & 2 ? "true" : "false") + "\n"
					+ "\tArray Size (if not runtime): " + std::to_string(svImageVar.m_arrData[2]) + "\n"
					+ "\tDimensions: " + m_mImageDimensions[svImageVar.m_arrData[3]] + "\n"
					+ "\tFormat: " + m_mImageFormatNames[svImageVar.m_arrData[4]]
				);
			}
			
			mShaderVars[strName] = svImageVar;
		}
	}

	//Samplers
	{
		for (const auto& aSampler : _srRes.separate_samplers) {
			const spirv_cross::SPIRType& stType = _cComp.get_type(aSampler.type_id);

			uint16 u16Flags = !stType.array.empty();

			HCShaderVar svSampler = {
				.m_u16Type = VAR_SAMPLER,
				.m_u16Flags = u16Flags,
				.m_arrData = {
					_cComp.get_decoration(aSampler.id, spv::DecorationBinding),
					_cComp.get_decoration(aSampler.id, spv::DecorationDescriptorSet),
					stType.array.empty() ? 0 : stType.array[0]
				}
			};

			String strName = _cComp.get_name(aSampler.id);

			Console::DebugInfo("Found Sampler: \"" + strName + "\". Parameters:\n"
				+ "\tBinding: " + std::to_string(svSampler.m_arrData[0]) + "\n"
				+ "\tDescriptor Set: " + std::to_string(svSampler.m_arrData[1]) + "\n"
				+ "\tIs Array: " + (svSampler.m_u16Flags & 1 ? "true" : "false") + "\n"
				+ "\tIs Unsized Array: " + ((svSampler.m_u16Flags & 1) && svSampler.m_arrData[2] == 0 ? "true" : "false") + "\n"
				+ "\tArray Size (if not runtime): " + std::to_string(svSampler.m_arrData[2])
			);

			mShaderVars[strName] = svSampler;
		}

		for (const auto& aSampler : _srRes.sampled_images) {
			const spirv_cross::SPIRType& stType = _cComp.get_type(aSampler.type_id);

			uint16 u16Flags = !stType.array.empty();

			HCShaderVar svCombinedSampler = {
				.m_u16Type = VAR_COMBINED_IMAGE_SAMPLER,
				.m_u16Flags = u16Flags,
				.m_arrData = {
					_cComp.get_decoration(aSampler.id, spv::DecorationBinding),
					_cComp.get_decoration(aSampler.id, spv::DecorationDescriptorSet),
					stType.array.empty() ? 0 : stType.array[0],
					static_cast<uint32>(stType.image.dim),
					static_cast<uint32>(stType.image.format)
				}
			};

			String strName = _cComp.get_name(aSampler.id);

			Console::DebugInfo("Found Combined Image Sampler: \"" + strName + "\". Parameters:\n"
				+ "\tBinding: " + std::to_string(svCombinedSampler.m_arrData[0]) + "\n"
				+ "\tDescriptor Set: " + std::to_string(svCombinedSampler.m_arrData[1]) + "\n"
				+ "\tIs Array: " + (svCombinedSampler.m_u16Flags & 1 ? "true" : "false") + "\n"
				+ "\tIs Unsized Array: " + ((svCombinedSampler.m_u16Flags & 1) && svCombinedSampler.m_arrData[2] == 0 ? "true" : "false") + "\n"
				+ "\tArray Size (if not runtime): " + std::to_string(svCombinedSampler.m_arrData[2]) + "\n"
				+ "\tDimensions: " + m_mImageDimensions[svCombinedSampler.m_arrData[3]] + "\n"
				+ "\tFormat: " + m_mImageFormatNames[svCombinedSampler.m_arrData[4]]
			);
			
			mShaderVars[strName] = svCombinedSampler;
		}
	}

	//Inputs
	{
		for (const auto& aInput : _srRes.stage_inputs) {
			const spirv_cross::SPIRType& stType = _cComp.get_type(aInput.type_id);

			uint16 u16Flags = !stType.array.empty() | TranslateBaseTypeToFlag(stType.basetype);

			u16Flags |= _cComp.has_decoration(aInput.id, spv::DecorationFlat) ? INTERP_FLAT : 0;
			u16Flags |= _cComp.has_decoration(aInput.id, spv::DecorationNoPerspective) ? INTERP_NO_PERSPECTIVE : 0;
			u16Flags |= _cComp.has_decoration(aInput.id, spv::DecorationCentroid) ? INTERP_CENTROID : 0;
			u16Flags |= _cComp.has_decoration(aInput.id, spv::DecorationSample) ? INTERP_SAMPLE : 0;

			HCShaderVar svInput = {
				.m_u16Type = VAR_STAGE_INPUT,
				.m_u16Flags = u16Flags,
				.m_arrData = {
					_cComp.get_decoration(aInput.id, spv::DecorationLocation),
					_cComp.get_decoration(aInput.id, spv::DecorationBinding),
					stType.array.empty() ? 0 : stType.array[0],
					stType.vecsize,
					stType.columns
				}
			};

			String strName = _cComp.get_name(aInput.id);

			Console::DebugInfo("Found Input: \"" + strName + "\". Parameters:\n"
				+ "\tLocation: " + std::to_string(svInput.m_arrData[0]) + "\n"
				+ "\tBinding: " + std::to_string(svInput.m_arrData[1]) + "\n"
				+ "\tIs Array: " + (svInput.m_u16Flags & 1 ? "true" : "false") + "\n"
				+ "\tIs Unsized Array: " + ((svInput.m_u16Flags & 1) && svInput.m_arrData[2] == 0 ? "true" : "false") + "\n"
				+ "\tArray Size (if not runtime): " + std::to_string(svInput.m_arrData[2]) + "\n"
				+ "\tComponent Type: " + m_mTypeNames[svInput.m_u16Flags & IO_MAX] + "\n"
				+ "\tVector width: " + std::to_string(svInput.m_arrData[3]) + "\n"
				+ "\tColumn count: " + std::to_string(svInput.m_arrData[4]) + "\n"
				+ "\tInterpolation method: " + ConstructInterpolationString(svInput.m_u16Flags)
			);

			mShaderVars[strName] = svInput;
		}

		for (const auto& aInput : _srRes.builtin_inputs) {
			const spirv_cross::SPIRType& stType = _cComp.get_type(aInput.resource.type_id);

			HCShaderVar svBuiltinInput = {
				.m_u16Type = VAR_BUILTIN_STAGE_INPUT,
				.m_u16Flags = TranslateBaseTypeToFlag(stType.basetype),
				.m_arrData = {
					static_cast<uint32>(aInput.builtin),
					stType.vecsize,
					stType.columns
				}
			};

			if (svBuiltinInput.m_u16Flags == IO_INVALID) continue;

			String strName = _cComp.get_name(aInput.resource.id);

			Console::DebugInfo("Found Built-in Input: \"" + strName + "\". Parameters:\n"
				+ "\tBuilt-in: " + m_mBuiltinNames[svBuiltinInput.m_arrData[0]] + "\n"
				+ "\tComponent Type: " + m_mTypeNames[svBuiltinInput.m_u16Flags] + "\n"
				+ "\tVector width: " + std::to_string(svBuiltinInput.m_arrData[1]) + "\n"
				+ "\tColumn count: " + std::to_string(svBuiltinInput.m_arrData[2])
			);

			mShaderVars[strName] = svBuiltinInput;
		}

		for (const auto& aSubpassInput : _srRes.subpass_inputs) {
			const spirv_cross::SPIRType& stType = _cComp.get_type(aSubpassInput.type_id);

			HCShaderVar svSubpassInput = {
				.m_u16Type = VAR_SUBPASS_INPUT,
				.m_u16Flags = 0,
				.m_arrData = {
					_cComp.get_decoration(aSubpassInput.id, spv::DecorationBinding),
					_cComp.get_decoration(aSubpassInput.id, spv::DecorationDescriptorSet),
					_cComp.get_decoration(aSubpassInput.id, spv::DecorationInputAttachmentIndex),
					static_cast<uint32>(stType.image.dim),
					static_cast<uint32>(stType.image.format)
				}
			};

			String strName = _cComp.get_name(aSubpassInput.id);

			Console::DebugInfo("Found Subpass Input: \"" + strName + "\". Parameters:\n"
				+ "\tBinding: " + std::to_string(svSubpassInput.m_arrData[0]) + "\n"
				+ "\tDescriptor Set: " + std::to_string(svSubpassInput.m_arrData[1]) + "\n"
				+ "\tInput Attachment Index: " + std::to_string(svSubpassInput.m_arrData[2]) + "\n"
				+ "\tDimension: " + m_mImageDimensions[svSubpassInput.m_arrData[3]] + "\n"
				+ "\tFormat: " + m_mImageFormatNames[svSubpassInput.m_arrData[4]]
			);

			mShaderVars[strName] = svSubpassInput;
		}
	}

	//Outputs
	{
		for (const auto& aOutput : _srRes.stage_outputs) {
			const spirv_cross::SPIRType& stType = _cComp.get_type(aOutput.type_id);

			uint16 u16Flags = !stType.array.empty() | TranslateBaseTypeToFlag(stType.basetype);

			u16Flags |= _cComp.has_decoration(aOutput.id, spv::DecorationFlat) ? INTERP_FLAT : 0;
			u16Flags |= _cComp.has_decoration(aOutput.id, spv::DecorationNoPerspective) ? INTERP_NO_PERSPECTIVE : 0;
			u16Flags |= _cComp.has_decoration(aOutput.id, spv::DecorationCentroid) ? INTERP_CENTROID : 0;
			u16Flags |= _cComp.has_decoration(aOutput.id, spv::DecorationSample) ? INTERP_SAMPLE : 0;

			HCShaderVar svOutput = {
				.m_u16Type = VAR_STAGE_OUTPUT,
				.m_u16Flags = u16Flags,
				.m_arrData = {
					_cComp.get_decoration(aOutput.id, spv::DecorationLocation),
					_cComp.get_decoration(aOutput.id, spv::DecorationBinding),
					stType.array.empty() ? 0 : stType.array[0],
					stType.vecsize,
					stType.columns
				}
			};

			String strName = _cComp.get_name(aOutput.id);

			Console::DebugInfo("Found Output: \"" + strName + "\". Parameters:\n"
				+ "\tLocation: " + std::to_string(svOutput.m_arrData[0]) + "\n"
				+ "\tBinding: " + std::to_string(svOutput.m_arrData[1]) + "\n"
				+ "\tIs Array: " + (svOutput.m_u16Flags & 1 ? "true" : "false") + "\n"
				+ "\tIs Unsized Array: " + ((svOutput.m_u16Flags & 1) && svOutput.m_arrData[2] == 0 ? "true" : "false") + "\n"
				+ "\tArray Size (if not runtime): " + std::to_string(svOutput.m_arrData[2]) + "\n"
				+ "\tComponent Type: " + m_mTypeNames[svOutput.m_u16Flags & IO_MAX] + "\n"
				+ "\tVector width: " + std::to_string(svOutput.m_arrData[3]) + "\n"
				+ "\tColumn count: " + std::to_string(svOutput.m_arrData[4]) + "\n"
				+ "\tInterpolation method: " + ConstructInterpolationString(svOutput.m_u16Flags)
			);

			mShaderVars[strName] = svOutput;
		}

		for (const auto& aOutput : _srRes.builtin_outputs) {
			const spirv_cross::SPIRType& stType = _cComp.get_type(aOutput.resource.type_id);

			HCShaderVar svBuiltinOutput = {
				.m_u16Type = VAR_BUILTIN_STAGE_INPUT,
				.m_u16Flags = TranslateBaseTypeToFlag(stType.basetype),
				.m_arrData = {
					static_cast<uint32>(aOutput.builtin),
					stType.vecsize,
					stType.columns
				}
			};

			if (svBuiltinOutput.m_u16Flags == IO_INVALID) continue;

			String strName = _cComp.get_name(aOutput.resource.id);

			Console::DebugInfo("Found Built-in Output: \"" + strName + "\". Parameters:\n"
				+ "\tBuilt-in: " + m_mBuiltinNames[svBuiltinOutput.m_arrData[0]] + "\n"
				+ "\tComponent Type: " + m_mTypeNames[svBuiltinOutput.m_u16Flags] + "\n"
				+ "\tVector width: " + std::to_string(svBuiltinOutput.m_arrData[1]) + "\n"
				+ "\tColumn count: " + std::to_string(svBuiltinOutput.m_arrData[2])
			);

			mShaderVars[strName] = svBuiltinOutput;
		}
	}

	//Misc
	{
		for (const auto& aAcceleration : _srRes.acceleration_structures) {
			const spirv_cross::SPIRType& stType = _cComp.get_type(aAcceleration.type_id);

			uint16 u16Flags = !stType.array.empty();

			HCShaderVar svAcceleration = {
				.m_u16Type = VAR_ACCELERATION_STRUCTURE,
				.m_u16Flags = u16Flags,
				.m_arrData = {
					_cComp.get_decoration(aAcceleration.id, spv::DecorationBinding),
					_cComp.get_decoration(aAcceleration.id, spv::DecorationDescriptorSet),
					u16Flags == 0 ? 0 : stType.array[0]
				}
			};

			String strName = _cComp.get_name(aAcceleration.id);

			Console::DebugInfo("Found Acceleration Structure: \"" + strName + "\". Parameters:\n"
				+ "\tBinding: " + std::to_string(svAcceleration.m_arrData[0]) + "\n"
				+ "\tSet: " + std::to_string(svAcceleration.m_arrData[1]) + "\n"
				+ "\tIs Array: " + (svAcceleration.m_u16Flags ? "true" : "false") + "\n"
				+ "\tArray Size: " + std::to_string(svAcceleration.m_arrData[2])
			);

			mShaderVars[strName] = svAcceleration;
		}
		//These two are the same. This is mostly because I don't fully understand either structure, so until I learn their true differences, I won't change this.
		//Blame AI.
		for (const auto& aShaderBuffer : _srRes.shader_record_buffers) {
			const spirv_cross::SPIRType& stType = _cComp.get_type(aShaderBuffer.type_id);

			uint16 u16Flags = !stType.array.empty();

			HCShaderVar svRecordBuffer = {
				.m_u16Type = VAR_SHADER_RECORD_BUFFER,
				.m_u16Flags = u16Flags,
				.m_arrData = {
					_cComp.get_decoration(aShaderBuffer.id, spv::DecorationBinding),
					_cComp.get_decoration(aShaderBuffer.id, spv::DecorationDescriptorSet),
					u16Flags == 0 ? 0 : stType.array[0]
				}
			};

			String strName = _cComp.get_name(aShaderBuffer.id);

			Console::DebugInfo("Found Shader Record Buffer: \"" + strName + "\". Parameters:\n"
				+ "\tBinding: " + std::to_string(svRecordBuffer.m_arrData[0]) + "\n"
				+ "\tSet: " + std::to_string(svRecordBuffer.m_arrData[1]) + "\n"
				+ "\tIs Array: " + (svRecordBuffer.m_u16Flags ? "true" : "false") + "\n"
				+ "\tArray Size: " + std::to_string(svRecordBuffer.m_arrData[2])
			);

			mShaderVars[strName] = svRecordBuffer;
		}

		for (const auto& aAtomicCounter : _srRes.atomic_counters) {
			HCShaderVar svAtomicCounter = {
				.m_u16Type = VAR_ATOMIC_COUNTER,
				.m_u16Flags = TranslateBaseTypeToFlag(_cComp.get_type(aAtomicCounter.type_id).basetype),
				.m_arrData = {
					_cComp.get_decoration(aAtomicCounter.id, spv::DecorationBinding),
					_cComp.get_decoration(aAtomicCounter.id, spv::DecorationDescriptorSet),
					_cComp.get_decoration(aAtomicCounter.id, spv::DecorationOffset)
				}
			};

			String strName = _cComp.get_name(aAtomicCounter.id);

			Console::DebugInfo("Found Atomic Counter: \"" + strName + "\". Parameters:\n"
				+ "\tBinding: " + std::to_string(svAtomicCounter.m_arrData[0]) + "\n"
				+ "\tSet: " + std::to_string(svAtomicCounter.m_arrData[1]) + "\n"
				+ "\tBase Type: " + m_mTypeNames[svAtomicCounter.m_u16Flags] + "\n"
				+ "\tOffset: " + std::to_string(svAtomicCounter.m_arrData[2])
			);

			mShaderVars[strName] = svAtomicCounter;
		}

		for (const auto& aGLBuffer : _srRes.gl_plain_uniforms) {
			const spirv_cross::SPIRType& stType = _cComp.get_type(aGLBuffer.type_id);

			uint32 u32Size = 0;

			if (stType.basetype == spirv_cross::SPIRType::BaseType::Struct) {
				u32Size = _cComp.get_declared_struct_size(stType);
			}
			else {
				u32Size = SizeofBaseType(stType.basetype) * stType.vecsize * stType.columns;
				
				if (!stType.array.empty()) {
					for (const auto& aLength : stType.array) {
						u32Size *= aLength;
					}
				}
			}

			HCShaderVar svPlainUniform = {
				.m_u16Type = VAR_GL_PLAIN_UNIFORM,
				.m_u16Flags = 0,
				.m_arrData = {
					_cComp.get_decoration(aGLBuffer.id, spv::DecorationLocation),
					u32Size
				}
			};

			String strName = _cComp.get_name(aGLBuffer.id);

			Console::DebugInfo("Found Atomic Counter: \"" + strName + "\". Parameters:\n"
				+ "\tLocation: " + std::to_string(svPlainUniform.m_arrData[0]) + "\n"
				+ "\tSize: " + std::to_string(svPlainUniform.m_arrData[1])
			);

			mShaderVars[strName] = svPlainUniform;
		}
	}

	Console::DebugSuccess("Successfully gathered shader resources. Final count: " + std::to_string(mShaderVars.size()) + " entries");

	return mShaderVars;
}