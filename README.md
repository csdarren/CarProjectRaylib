Car Infotainment System 

Built with CMake and Ninja.
ninja folder must be set as an environment variable, or placed in build folder

Reference working build compiler configs with cmake. CMAKE + NINJA + LLVM CLANG WITH GNU-LIKE MSVC LINKER. (Get LLVM, Install, Get Visual Studio, Install, should work right out the box)


cmake -B build -G Ninja

***** LINUX ERRORS *****

Windows may have been broken when implementing linux changes in cmake file to change library based on platform

X11 Errors may occur on linux. To solve this issue, you need the X11 Dev packages. On Debian Distros, use sudo apt install on the following libs:
libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev

Must install OpenGL linux lib in order to build raylib library file (.a) 
libgl-dev
