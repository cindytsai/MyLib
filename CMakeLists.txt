cmake_minimum_required(VERSION 3.15)

### PROJECT Info ###
project(MyLib VERSION 0.1 DESCRIPTION "My library that uses Python, NumPy, OpenMPI, and readline")

option(BUILD_SHARED_LIBS "Building using shared libraries" ON)

### COMPILATION ###

add_subdirectory(src)                      # for library

add_subdirectory(example)                  # for example exe

configure_file(MyLib.pc.in MyLib.pc @ONLY) # for pkgconfig

### Test ###
# Test can only be at top level CMakeLists.txt
enable_testing()

add_test(NAME ProgramRuns COMMAND example)
set_tests_properties(ProgramRuns PROPERTIES PASS_REGULAR_EXPRESSION "Hello, World!")

### MyLib PACKAGING ###
# Only packaging library works
include(InstallRequiredSystemLibraries)
set(MYPROJECT_SRC "${CMAKE_CURRENT_SOURCE_DIR}")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE") # set license
set(CPACK_PACKAGE_VERSION_MAJOR "${Cmake_example_VERSION_MAJOR}")      # major version
set(CPACK_PACKAGE_VERSION_MINOR "${Cmake_example_VERSION_MINOR}")      # minor version
set(CPACK_SOURCE_GENERATOR "TGZ")                                      # packed format

include(CPack)