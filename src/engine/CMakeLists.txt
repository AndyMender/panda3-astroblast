add_library(ABEngine SHARED)

target_sources(ABEngine 
    PRIVATE engine.cpp)
# target_compile_definitions(ABEngine )
target_link_libraries(ABEngine
    ABCommon
)
