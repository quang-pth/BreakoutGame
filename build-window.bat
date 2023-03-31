cls
@echo off

if not exist build mkdir build

rem generate cmake files
cmake -O . -B ./build -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=ON

rem copy assets & .dll files to output dir
robocopy "./Resources"  "./build/bin/Debug/assets" /E
robocopy "./External/bin/"  "./build/bin/Debug/" /E

rem compile project
cd build && cmake --build . 

echo compilation finished!