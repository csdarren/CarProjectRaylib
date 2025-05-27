cmake_minimum_required(VERSION 3.11) 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(main C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.5)
set(raylib_DIR "${CMAKE_SOURCE_DIR}/include/libs") # Set path for raylib supplied cmake files. (Copied from raylib cmake repo folder)
include_directories("${CMAKE_SOURCE_DIR}/include")

add_executable(main src/main.cpp)

add_library(raylib STATIC IMPORTED)
add_library(imgui STATIC IMPORTED)

if (WIN32)
	set_target_properties(raylib PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/include/libs/raylib.lib")
	set_target_properties(imgui PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/include/libs/imgui.lib")
	target_link_libraries(main PRIVATE raylib imgui winmm)
endif()

if (UNIX)
	set_target_properties(raylib PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/include/libs/libraylib.a")
	set_target_properties(imgui PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/include/libs/libimguiLib.a")
	target_link_libraries(main PRIVATE raylib imgui)
endif()

