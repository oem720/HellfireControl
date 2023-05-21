BLOCK()
set(PLATFORM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/Linux)

if(REQUIRES_VULKAN AND UNIX AND NOT APPLE)
    execute_process(
        COMMAND pkg-config --exists vulkan
        RESULT_VARIABLE VULKAN_SDK_INSTALLED
    )

    if(VULKAN_SDK_INSTALLED)
        message("Vulkan SDK is already installed")
    else()
        message("Vulkan SDK is not installed. Would you like to auto install it? (y/N)")
        set(RESPONSE "" CACHE STRING "Developer's response")
        if(${RESPONSE} STREQUAL "y" OR ${RESPONSE} STREQUAL "Y")
            execute_process(
                COMMAND ${PLATFORM_DIR}/install_vulkan.sh ${PLATFORM_DIR}/get_latest_vulkan_tarball.py
            )
        endif()
    endif()
endif()

ENDBLOCK()