project(HellfireControl)

file(GLOB_RECURSE TORCHLIGHT_SOURCE_FILES src/Torchlight/*.hpp src/Torchlight/*.h src/Torchlight/*.cpp)

add_executable(Torchlight ${TORCHLIGHT_SOURCE_FILES})

target_compile_definitions(Torchlight PUBLIC _CRT_SECURE_NO_WARNINGS)
target_compile_definitions(Torchlight PUBLIC NOMINMAX)
target_compile_definitions(Torchlight PUBLIC HC_PROJECT_DIR="${HC_PROJECT_DIR}")

if(CMAKE_GENERATOR MATCHES "Visual Studio")
    foreach(_source IN ITEMS ${TORCHLIGHT_SOURCE_FILES})
        if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
        else()
            set(_source_rel "${_source}")
        endif()
        get_filename_component(_source_path "${_source_rel}" PATH)
	string(REPLACE "src" "" _source_path_msvc "${_source_path}")
	string(REPLACE "Torchlight" "" _source_path_msvc "${_source_path_msvc}")
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path_msvc}")
        source_group("${_source_path_msvc}" FILES "${_source}")
    endforeach()

    set_property(TARGET Torchlight PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

endif()

target_include_directories(Torchlight PUBLIC src)
target_include_directories(Torchlight PUBLIC ../HellfireControl/src)

if(WIN32)
	target_include_directories(Torchlight PUBLIC $ENV{VULKAN_SDK}/Include/)
	target_link_directories(Torchlight PUBLIC $ENV{VULKAN_SDK}/Lib/)
	target_link_libraries(Torchlight PUBLIC vulkan-1.lib)
endif(WIN32)

target_link_libraries(Torchlight PUBLIC HellfireCore)
