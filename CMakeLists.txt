cmake_minimum_required(VERSION 3.13)

project(ov_test C)

# Disable default build of unrequired libraries
# (Must be done before including the subdirectory with these libraries.)
# Example:
SET(BUILD_OV_LIBRARY_UDPbind OFF CACHE BOOL "")
SET(BUILD_OV_LIBRARY_SSChelper OFF CACHE BOOL "")


# Include ov core
add_subdirectory(rte)

# Include ov helper functions and definitions
get_target_property(RTE_CMAKE_DIR ov RTE_CMAKE_DIR)
include(${RTE_CMAKE_DIR}/ov_functions.cmake)
include(${RTE_CMAKE_DIR}/ov_definitions.cmake)

# Include library packages
add_subdirectory(rte_fblib)
add_subdirectory(rte_misc)
add_subdirectory(rte_field)

# Include libraries of this project
# Example:
add_subdirectory(demolib)

ov_finish_project()
