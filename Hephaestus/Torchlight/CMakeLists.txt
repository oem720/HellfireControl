project(HellfireControl)

create_project(Torchlight EXEC)

link_core(Torchlight)

link_vulkan_sdk(Torchlight)

move_working_directory_to_project_root(Torchlight)