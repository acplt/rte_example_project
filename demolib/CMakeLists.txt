
add_ov_library(demolib)
ov_library_includes(demolib fb)

if(UNIX)
    target_link_libraries(demolib -lm)
endif()
