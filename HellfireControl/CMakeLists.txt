project(HellfireControl)

file(GLOB_RECURSE HELLFIRE_SOURCE_FILES src/*.hpp src/*.h src/*.cpp src/*.m src/*.mm)

add_library(HellfireCore STATIC ${HELLFIRE_SOURCE_FILES})

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
## Windows specific build settings                     ##
#########################################################

if(CMAKE_GENERATOR MATCHES "Visual Studio")
    foreach(_source IN ITEMS ${HELLFIRE_SOURCE_FILES})
        if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
        else()
            set(_source_rel "${_source}")
        endif()
        get_filename_component(_source_path "${_source_rel}" PATH)
	string(REPLACE "src" "" _source_path_msvc "${_source_path}")
	string(REPLACE "HellfireControl" "" _source_path_msvc "${_source_path_msvc}")
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path_msvc}")
        source_group("${_source_path_msvc}" FILES "${_source}")
    endforeach()

    set_target_properties(HellfireCore PROPERTIES VS_COPYRIGHT ${HC_COPYRIGHT})
endif()

#########################################################
## MacOS specific build settings                       ##
#########################################################

BLOCK() # New scope for MacOS specific variables
set(PLIST ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/Mac/info.plist)
#execute_process(COMMAND bash -c "echo ${PLIST}") # echoes path for testing
if(CMAKE_GENERATOR MATCHES "Xcode")
    # Generator matches Xcode, set compiler macro
    add_compile_definitions(XCODE_BUILD)
    # Set info.plist for Xcode project
    set_target_properties(HellfireCore PROPERTIES
        XCODE_ATTRIBUTE_INFOPLIST_FILE ${PLIST}
    )
endif()
if(APPLE)
    # Dynamically updates copyright in info.plist
    execute_process(
        COMMAND plutil -replace NSHumanReadableCopyright -string ${HC_COPYRIGHT} ${PLIST}
        OUTPUT_VARIABLE COMMAND_OUTPUT
        RESULT_VARIABLE COMMAND_RESULT
    )
endif()
ENDBLOCK() # PLIST, COMMAND_OUTPUT, COMMAND_RESULT discarded
# Compiler macros depending on CPU architecture for edge cases
if (APPLE AND CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|i386)")
    # Use `#if(n)def APPLE_X86` when targeting a Mac with Intel CPU
    add_compile_definitions(APPLE_X86)
elseif (APPLE AND CMAKE_SYSTEM_PROCESSOR MATCHES "^(arm64)")
    # Use `#if(n)def APPLE_ARM64` when targeting an Apple Silicon Mac
    add_compile_definitions(APPLE_ARM64)
endif()


#########################################################
## Linux specific build settings                       ##
#########################################################


#########################################################
## Vulkan inclusion                                    ##
#########################################################

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

target_include_directories(HellfireCore PUBLIC src)