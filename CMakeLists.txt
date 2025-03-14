cmake_minimum_required(VERSION 3.11) 
project(CarProjectraylib C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.5)
set(raylib_DIR "C:/dev/GitHub/raylib/cmake")
include_directories("C:/dev/CPP/CarProjectRaylib/include")
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED

add_executable(CarProjectRaylib src/main.cpp)

add_library(raylib STATIC IMPORTED)
set_target_properties(raylib PROPERTIES IMPORTED_LOCATION "C:/dev/GitHub/raylib/build/raylib/raylib.lib")
add_library(imgui STATIC IMPORTED)
set_target_properties(imgui PROPERTIES IMPORTED_LOCATION "C:/dev/GitHub/imguiLib/build/imguiLib.lib")
target_link_libraries(CarProjectRaylib PRIVATE raylib imgui winmm)

