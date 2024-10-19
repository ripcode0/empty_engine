set(stb_url "https://raw.githubusercontent.com/nothings/stb/master/stb_image.h")
set(stb_path ${CMAKE_SOURCE_DIR}/external/include/stb)

if(NOT EXISTS ${stb_path}/stb_image.h)
    message(STATUS "[external] stb image downloading...")
    file(DOWNLOAD ${stb_url} ${stb_path}/stb_image.h)
else()
    message(STATUS "[external] stb image founded.")
endif()