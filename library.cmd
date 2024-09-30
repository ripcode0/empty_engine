@echo off

set download_dir=./download/wglad
set install_dir=./external
set wglad_build_dir=%download_dir%/wglad/build

if exist %download_dir%/CMakeLists.txt (
    echo wglad exist already ...
) else (
    git clone https://github.com/ripcode0/wglad.git %download_dir%
)

cmake -S %download_dir% -B %download_dir%/build
cmake --build %download_dir%/build --config Debug
cmake --install %download_dir%/build --prefix %install_dir%

rmdir /S /Q download