cmake_minimum_required(VERSION 3.28)

cmake_policy(SET CMP0175 NEW)

project(empty-engine VERSION 0.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

set(bin_dir ${CMAKE_SOURCE_DIR}/bin)

set(lib_dir ${CMAKE_SOURCE_DIR}/lib
            ${CMAKE_SOURCE_DIR}/external/lib)

set(inc_dir ${CMAKE_SOURCE_DIR}/empty
            ${CMAKE_SOURCE_DIR}/external/include)

include(3rdparty.cmake)

add_subdirectory(empty)

add_subdirectory(sample)


