Car Infotainment System 

Built with CMake and Ninja.
Ninja must be set as an environmental variable, otherwise an additional argument must be added to your cmake build command, which is: 
-DCMAKE_MAKE_PROGRAM="full\path\to\ninja.exe"

Reference working build compiler configs with cmake. CMAKE + NINJA + LLVM CLANG WITH GNU-LIKE MSVC LINKER. (Get LLVM, Install, Get Visual Studio, Install, should work right out the box)


cmake -B build -G Ninja