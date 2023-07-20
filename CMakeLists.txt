cmake_minimum_required(VERSION 3.15)

### PROJECT Info ###
project(MyLib VERSION 0.1 DESCRIPTION "My library that uses Python, NumPy, OpenMPI, and readline")

option(BUILD_SHARED_LIBS "Building using shared libraries" ON)

### COMPILATION ###
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src)      # for library
add_subdirectory(example)  # for example exe

configure_file(MyLib.pc.in MyLib.pc @ONLY)
