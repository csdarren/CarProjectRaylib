"# Car Infotainment System" 

Built with CMake and Ninja.
Ninja must be set as an environmental variable, otherwise an additional argument must be added to your cmake build command, which is: 
-DCMAKE_MAKE_PROGRAM="full\path\to\ninja.exe"

Must change paths in CMakeLists.txt to adapt to OS / include directory for library files. I compiled raylib + imgui myself into .lib (.a on linux) for quicker compiling.