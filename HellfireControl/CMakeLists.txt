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

target_include_directories(HellfireCore PUBLIC src)