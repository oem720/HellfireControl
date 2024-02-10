project(HellfireControl)

function(get_files_with_extensions dir extensions result_var)
    file(GLOB_RECURSE files "${dir}/*.*")
    set(result_files "")
    foreach(file ${files})
        get_filename_component(ext ${file} EXT)
        string(REPLACE "." "" ext ${ext})
        if (ext IN_LIST extensions)
            list(APPEND result_files ${file})
        endif()
    endforeach()
    set(${result_var} "${result_files}" PARENT_SCOPE)
endfunction()

set(extensions "cpp" "h" "hpp" "m" "mm")
get_files_with_extensions("src/HellfireControl" "${extensions}" HELLFIRE_SOURCE_FILES)
file(GLOB HELLFIREPLATFORM_COMMON_SOURCE_FILES "src/Platform/*.hpp")
get_files_with_extensions("src/Platform/Vulkan" "${extensions}" HELLFIREPLATFORM_VULKAN_SOURCE_FILES)
get_files_with_extensions("src/Platform/OpenGL" "${extensions}" HELLFIREPLATFORM_OPENGL_SOURCE_FILES)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    get_files_with_extensions("src/Platform/Mac" "${extensions}" HELLFIREPLATFORM_SOURCE_FILES)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    get_files_with_extensions("src/Platform/Windows" "${extensions}" HELLFIREPLATFORM_SOURCE_FILES)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    get_files_with_extensions("src/Platform/Linux" "${extensions}" HELLFIREPLATFORM_SOURCE_FILES)
else()
    message(FATAL_ERROR "Unsupported OS: ${CMAKE_SYSTEM_NAME}")
endif()

add_library(HellfireCore STATIC
        ${HELLFIRE_SOURCE_FILES}
        ${HELLFIREPLATFORM_VULKAN_SOURCE_FILES}
        ${HELLFIREPLATFORM_OPENGL_SOURCE_FILES}
        ${HELLFIREPLATFORM_SOURCE_FILES}
)

#########################################################
## Compiler definitions                                ##
#########################################################

target_compile_definitions(HellfireCore PUBLIC _CRT_SECURE_NO_WARNINGS)
target_compile_definitions(HellfireCore PUBLIC NOMINMAX)
target_compile_definitions(HellfireCore PUBLIC HC_PROJECT_DIR="${HC_PROJECT_DIR}")

#########################################################
## Variables                                           ##
#########################################################

string(TIMESTAMP CURRENT_YEAR "%Y")
set(HC_COPYRIGHT "Copyright (c) ${CURRENT_YEAR} Owen Meyers. All rights reserved.")
set(REQUIRES_VULKAN FALSE) # Change to TRUE once ready to include Vulkan

#########################################################
## Includes                                            ##
#########################################################

include(src/Platform/Windows/Windows.cmake)

include(src/Platform/Mac/MacOS.cmake)

include(src/Platform/Linux/Linux.cmake)

include(src/Platform/Vulkan/Vulkan.cmake)

include(src/Platform/OpenGL/OpenGL.cmake)

target_include_directories(HellfireCore PUBLIC src)

target_precompile_headers(HellfireCore PRIVATE src/HellfireControl/Core/Common.hpp)