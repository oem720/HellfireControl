project(HellfireControl)

create_project(ShaderCompiler EXEC)

link_core(ShaderCompiler)

link_vulkan_sdk(ShaderCompiler)

link_vulkan_shader_comp(ShaderCompiler)