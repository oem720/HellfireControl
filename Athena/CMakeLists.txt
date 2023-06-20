project(HellfireControl)

file(GLOB_RECURSE ATHENA_SOURCE_FILES src/*.hpp src/*.h src/*.cpp)

add_executable(Athena ${ATHENA_SOURCE_FILES})

target_compile_definitions(Athena PUBLIC _CRT_SECURE_NO_WARNINGS)
target_compile_definitions(Athena PUBLIC NOMINMAX)
target_compile_definitions(Athena PUBLIC HC_PROJECT_DIR="${HC_PROJECT_DIR}")

if(CMAKE_GENERATOR MATCHES "Visual Studio")
    foreach(_source IN ITEMS ${ATHENA_SOURCE_FILES})
        if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
        else()
            set(_source_rel "${_source}")
        endif()
        get_filename_component(_source_path "${_source_rel}" PATH)
	string(REPLACE "src" "" _source_path_msvc "${_source_path}")
	string(REPLACE "Athena" "" _source_path_msvc "${_source_path_msvc}")
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path_msvc}")
        source_group("${_source_path_msvc}" FILES "${_source}")
    endforeach()
endif()

target_include_directories(Athena PUBLIC src)
target_include_directories(Athena PUBLIC ../HellfireControl/src)