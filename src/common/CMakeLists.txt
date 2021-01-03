add_library(ABCommon SHARED)

target_sources(ABCommon 
    PRIVATE common.cpp)
target_compile_definitions(ABCommon 
    PRIVATE "-DBOOST_LOG_DYN_LINK"
)
target_link_libraries(ABCommon pthread boost_log)
