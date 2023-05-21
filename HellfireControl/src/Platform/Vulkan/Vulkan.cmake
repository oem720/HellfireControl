BLOCK()
set(PLATFORM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/Vulkan)

if(APPLE)
    find_library(VULKAN_LIBRARY MoltenVK)
else()
    find_package(Vulkan REQUIRED)
endif()

if(VULKAN_LIBRARY)
    target_link_libraries(HellfireCore PRIVATE ${VULKAN_LIBRARY})
elseif(Vulkan_FOUND)
    target_link_libraries(HellfireCore PRIVATE Vulkan::Vulkan)
elseif(REQUIRES_VULKAN)
    message(FATAL_ERROR "Could not find Vulkan or MoltenVK library")
endif()

ENDBLOCK()