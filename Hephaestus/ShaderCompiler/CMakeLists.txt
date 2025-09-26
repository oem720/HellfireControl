project(HellfireControl)

create_project(ShaderCompiler EXEC)

link_core(ShaderCompiler)

link_vulkan_sdk(ShaderCompiler)

move_working_directory_to_project_root(ShaderCompiler)