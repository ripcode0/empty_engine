
file(GLOB_RECURSE srcs *.h *.cpp)

add_library(empty STATIC ${srcs})


set_target_properties(empty PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/lib
)

target_include_directories(empty PUBLIC ${inc_dir})
target_link_directories(empty PUBLIC ${lib_dir})
target_link_libraries(empty PUBLIC wglad)




