cmake_minimum_required(VERSION 3.5)

project (PossibleOptions)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++11")
set (source_dir "${PROJECT_SOURCE_DIR}/src/")

file (GLOB sorce_files "${source_dir}/*.cpp")

add_executable (PossibleOptions ${sorce_files})
