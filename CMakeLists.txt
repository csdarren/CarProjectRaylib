cmake_minimum_required(VERSION 3.11) 
project(main C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.5)
set(raylib_DIR "${CMAKE_SOURCE_DIR}/include/lib") # Set path for raylib supplied cmake files. (Copied from raylib cmake repo folder)
include_directories("${CMAKE_SOURCE_DIR}/include")
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED

add_executable(main src/main.cpp)
add_executable(maintest src/maintest.cpp)

add_library(raylib STATIC IMPORTED)
set_target_properties(raylib PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/include/lib/raylib.lib")
add_library(imgui STATIC IMPORTED)
set_target_properties(imgui PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/include/lib/imguiLib.lib")
target_link_libraries(main PRIVATE raylib imgui winmm)
target_link_libraries(maintest PRIVATE raylib imgui winmm)

