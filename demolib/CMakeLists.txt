
add_ov_library(demolib)
ov_library_includes(demolib fb)

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(demolib PRIVATE -lm)
endif()
