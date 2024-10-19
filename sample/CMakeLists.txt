#empty
file(GLOB_RECURSE srcs *.h *.cpp)

#message("srcs : ${srcs}")

add_executable(sample ${srcs})

target_include_directories(sample PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${inc_dir})
target_link_directories(sample PUBLIC ${lib_dir})
target_link_libraries(sample PUBLIC empty)

set_target_properties(sample PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${bin_dir}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${bin_dir}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${bin_dir}
    PDB_OUTPUT_DIRECTORY ${bin_dir}
    PDB_OUTPUT_DIRECTORY_DEBUG ${bin_dir}
    PDB_OUTPUT_DIRECTORY_RELEASE ${bin_dir}
    VS_DEBUGGER_WORKING_DIRECTORY ${bin_dir} #working directory for VS
)

