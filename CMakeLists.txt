# Not really sure what minimum required is yet.
cmake_minimum_required(VERSION 3.13)

# Project
project(BreakBuild C)
set(CMAKE_C_STANDARD 99)

# Build options
option(BreakBuild_UseVCPKG "Use the VCPKG libraries instead of the linux package manager." OFF)

# Breakout Source
set(Breakout_CompileAsLibrary ON)
add_subdirectory(Breakout)

# Libraries
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)

# Create Executable
add_executable(BreakBuild "BreakBuild.c" "R_BBRenderer_GL11.c")

# Breakout Source
target_link_libraries(BreakBuild PRIVATE Breakout)

# Link Libraries
if(${BreakBuild_UseVCPKG})
	# VCPKG, probably Windows
	target_link_libraries(BreakBuild PRIVATE SDL2::SDL2 SDL2::SDL2main)
	target_link_libraries(BreakBuild PRIVATE GLEW::GLEW)
else()
	# Linux (Tested on Debian and Arch) package manager
	target_link_libraries(BreakBuild PRIVATE SDL2)
	target_link_libraries(BreakBuild PRIVATE GLEW)
endif()
