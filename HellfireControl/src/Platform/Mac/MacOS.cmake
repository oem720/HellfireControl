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
endif()

# Copyright
if(APPLE)
    # Dynamically updates copyright in info.plist
    execute_process(
        COMMAND plutil -replace NSHumanReadableCopyright -string ${HC_COPYRIGHT} ${PLIST}
        OUTPUT_VARIABLE COMMAND_OUTPUT
        RESULT_VARIABLE COMMAND_RESULT
    )
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