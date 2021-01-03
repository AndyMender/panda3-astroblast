# shared objects needed by all game targets
# TODO: What does panda3 need?
include_directories("/usr/include/eigen3")
link_directories("/usr/lib/panda3d")
link_libraries(pthread p3framework panda pandafx pandaexpress p3dtoolconfig p3dtool p3direct)

# add directories for specific targets
add_subdirectory("common")
add_subdirectory("engine")

# define main target
add_executable("${PROJECT_NAME}")
target_sources("${PROJECT_NAME}" PRIVATE main.cpp)
target_link_libraries("${PROJECT_NAME}"
    boost_program_options
    ABCommon
)
