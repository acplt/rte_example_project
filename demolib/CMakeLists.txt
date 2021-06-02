
add_ov_library(demolib)
ov_library_includes(demolib fb)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(demolib PRIVATE -lm)
endif()
