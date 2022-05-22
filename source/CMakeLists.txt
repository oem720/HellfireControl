cmake_minimum_required(VERSION 3.10)

project(HCEngine)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(
	math_source_list
	"HCMath/HCVector.h"
	"HCMath/HCVector.cpp"
)

set(
	source_list
	"Main.cpp"
	${math_source_list}
)

add_executable(HCEngine ${source_list})

foreach(source IN LISTS source_list)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()