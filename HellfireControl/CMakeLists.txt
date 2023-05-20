project(HellfireControl)

file(GLOB_RECURSE HELLFIRE_SOURCE_FILES src/*.hpp src/*.h src/*.cpp)

add_library(HellfireCore STATIC ${HELLFIRE_SOURCE_FILES})

target_compile_definitions(HellfireCore PUBLIC _CRT_SECURE_NO_WARNINGS)
target_compile_definitions(HellfireCore PUBLIC NOMINMAX)
target_compile_definitions(HellfireCore PUBLIC HC_PROJECT_DIR="${HC_PROJECT_DIR}")

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
endif()

if(CMAKE_GENERATOR MATCHES "Xcode")
    # Generator matches Xcode, set compiler macro
    add_definitions(-DXCODE_BUILD)
    # Use `#if(n)def XCODE_BUILD` in areas where Xcode specific code should be used

    # Compiler macros depending on CPU architecture for edge cases
    if (APPLE AND CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|i386)")
        # Use `#if(n)def APPLE_X86` when targeting a Mac with Intel CPU
        add_definitions(-DAPPLE_X86)
    elseif (APPLE AND CMAKE_SYSTEM_PROCESSOR MATCHES "^(arm64)")
        # Use `#if(n)def APPLE_ARM64` when targeting an Apple Silicon Mac
        add_definitions(-DAPPLE_ARM64)
    endif()
endif()

target_include_directories(HellfireCore PUBLIC src)