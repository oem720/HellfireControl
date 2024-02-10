BLOCK() # New scope for MacOS specific variables
set(PLATFORM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/Mac)
set(PLIST ${PLATFORM_DIR}/info.plist)

#execute_process(COMMAND bash -c "echo ${PLIST}") # echoes path for testing

if(CMAKE_GENERATOR MATCHES "Xcode")
    # Generator matches Xcode, set compiler macro
    add_compile_definitions(XCODE_BUILD)
    # Set info.plist for Xcode project
    set_target_properties(HellfireCore PROPERTIES
        XCODE_ATTRIBUTE_INFOPLIST_FILE ${PLIST}
    )
    set_source_files_properties(${PLATFORM_DIR}/Resources/macOS.xcassets PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    set_source_files_properties(${PLATFORM_DIR}/Resources/Main.storyboard PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
endif()

# Copyright
if(APPLE)
    # Dynamically updates copyright in info.plist
    execute_process(
        COMMAND plutil -replace NSHumanReadableCopyright -string ${HC_COPYRIGHT} ${PLIST}
        OUTPUT_VARIABLE COMMAND_OUTPUT
        RESULT_VARIABLE COMMAND_RESULT
    )
    execute_process(
        COMMAND ${PLATFORM_DIR}/create_module_map.sh ${CMAKE_CURRENT_SOURCE_DIR}
    )
endif()

# Compile Swift sources
if(APPLE AND CMAKE_GENERATOR MATCHES "Ninja")
    target_compile_options(HellfireCore PRIVATE -enable-experimental-cxx-interop)
    target_compile_options(HellfireCore PUBLIC -I ${CMAKE_CURRENT_SOURCE_DIR}/src/HellfireControl)
    target_include_directories(HellfireCore PUBLIC src/HellfireControl)
    set_target_properties(HellfireCore PROPERTIES
            Swift_LANGUAGE_VERSION 5
            Swift_MODULE_DEPENDS HellfireControl)
    target_include_directories(HellfireCore PRIVATE ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
    find_library(COCOA_LIBRARY Cocoa)
    find_library(COREFOUNDATION_LIBRARY CoreFoundation)
    target_link_libraries(HellfireCore PRIVATE ${COCOA_LIBRARY} ${COREFOUNDATION_LIBRARY})
#    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -v)
endif()

ENDBLOCK() # PLATFORM_DIR, PLIST, COMMAND_OUTPUT, COMMAND_RESULT discarded

# Compiler macros depending on CPU architecture for edge cases
if (APPLE AND CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|i386)")
    # Use `#if(n)def APPLE_X86` when targeting a Mac with Intel CPU
    add_compile_definitions(APPLE_X86)
elseif (APPLE AND CMAKE_SYSTEM_PROCESSOR MATCHES "^(arm64)")
    # Use `#if(n)def APPLE_ARM64` when targeting an Apple Silicon Mac
    add_compile_definitions(APPLE_ARM64)
endif()

if(REQUIRES_VULKAN AND APPLE)
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
                COMMAND ${PLATFORM_DIR}/install_vulkan.sh ${PLATFORM_DIR}/get_latest_vulkan_dmg.py
            )
        endif()
    endif()
endif()