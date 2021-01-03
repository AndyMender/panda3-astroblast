# shared objects needed by all game targets
# TODO: What does panda3 need?
# link_libraries(pthread)

# add directories for specific targets
add_subdirectory("common")

# define main target
add_executable("${PROJECT_NAME}")
target_sources("${PROJECT_NAME}" PRIVATE main.cpp)
target_link_libraries("${PROJECT_NAME}"
    ABCommon
    pthread 
    boost_program_options
)
