cmake_minimum_required(VERSION 3.10...3.19)

# NOTE: Bump VERSION as needed
project("Astroblast"
		VERSION 0.1
		DESCRIPTION "A re-imagining of the Astro3D game using the panda3d game engine"
        LANGUAGES C CXX)

# enforce C standard and disallow non-portable compiler extensions
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# TODO: make this step platform-dependent
include_directories(
	"/usr/include"
	"/usr/local/include")

# TODO: make this step platform-dependent
link_directories(
    "/usr/lib"
	"/usr/lib64"
	"/usr/local/lib")

# make sure targets end up in specific places for easier distribution
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/apps")
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")

# add source code subdirs
add_subdirectory("src")

# link-time optimization (LTO)
include(CheckIPOSupported)
check_ipo_supported(RESULT LTO_SUPPORTED)

if(LTO_SUPPORTED)
	set(INTERPROCEDURAL_OPTIMIZATION ON)
else()
	message(STATUS "LTO not supported on this platform.")
endif()