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
## Includes                                            ##
#########################################################

include(src/Platform/Windows/Windows.cmake)

include(src/Platform/Mac/MacOS.cmake)

include(src/Platform/Linux/Linux.cmake)

include(src/Platform/Vulkan/Vulkan.cmake)

include(src/Platform/OpenGL/OpenGL.cmake)

target_include_directories(HellfireCore PUBLIC src)