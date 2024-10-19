
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
target_compile_definitions(empty PUBLIC USE_SHADER_PATH USE_SHADER_EXTENSION)

#create sysbol link
set(src_data_dir ${CMAKE_SOURCE_DIR}/data)
set(dst_data_dir ${bin_dir}/data)

add_custom_command(
    TARGET empty
    POST_BUILD COMMAND ${CMAKE_COMMAND}
    -E create_symlink ${src_data_dir} ${dst_data_dir}
    DEPENDS ${dst_data_dir}
    COMMENT "create a symbolic link ${dst_data_dir}"
)




