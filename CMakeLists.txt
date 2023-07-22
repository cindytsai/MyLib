cmake_minimum_required(VERSION 3.15)

### PROJECT Info ###
project(MyLib VERSION 0.1 DESCRIPTION "My library that uses Python, NumPy, OpenMPI, and readline")

# Set option
option(SERIAL            "Compile library for serial process" OFF)
option(INTERACTIVE_MODE  "Use interactive mode"               ON )
option(SUPPORT_TIMER     "Support timer"                      OFF)
option(USE_BOO           "Use -DUSE_BOO"                      OFF)
option(BUILD_SHARED_LIBS "Building using shared libraries"    ON )  # MyLib is built into shared lib for now.

# Set path
set(MPI_PATH       "")
set(PYTHON_PATH    "")
set(PYTHON_VERSION "")
set(READLINE_PATH  "")

# debug
file(GENERATE OUTPUT debug_genexpr CONTENT
"$<$<BOOL:${INTERACTIVE_MODE}>:Timer.cpp>;
 $<$<NOT:$<STREQUAL:${READLINE_PATH},>>:ReadlinePathSet>
 $<$<STREQUAL:${READLINE_PATH},>:ReadlinePathSet>")

### COMPILATION ###
add_library(mylib_compiler_flags INTERFACE)
target_compile_features(mylib_compiler_flags INTERFACE cxx_std_11)


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
set(CPACK_PACKAGE_VERSION_MAJOR "${MyLib_VERSION_MAJOR}")              # major version
set(CPACK_PACKAGE_VERSION_MINOR "${MyLib_VERSION_MINOR}")              # minor version
set(CPACK_SOURCE_GENERATOR "TGZ")                                      # packed format

include(CPack)
