cmake_minimum_required(VERSION 3.12)

project(ov_test C)

# Include ov core
add_subdirectory(rte)

# Include ov helper functions and definitions
get_target_property(RTE_CMAKE_DIR ov RTE_CMAKE_DIR)
include(${RTE_CMAKE_DIR}/ov_functions.cmake)
include(${RTE_CMAKE_DIR}/ov_definitions.cmake)

# Disable default build of unrequired libraries
# Example:
SET(BUILD_OV_LIBRARY_UDPbind OFF CACHE BOOL "")
SET(BUILD_OV_LIBRARY_SSChelper OFF CACHE BOOL "")

# Include library packages
add_subdirectory(rte_fblib)
add_subdirectory(rte_misc)
add_subdirectory(rte_field)

# Include libraries of this project
# Example:
add_subdirectory(demolib)
