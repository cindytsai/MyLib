cmake_minimum_required(VERSION 3.15)

###### PROJECT Info ####################################################################################################
project(MyLib VERSION 0.1 DESCRIPTION "My library that uses Python, NumPy, OpenMPI, and readline")

# Set option
option(SERIAL_MODE       "Compile library for serial process" OFF)
option(INTERACTIVE_MODE  "Use interactive mode"               ON )
option(SUPPORT_TIMER     "Support timer"                      OFF)
option(USE_BOO           "Use -DUSE_BOO"                      OFF)
option(NL_JSON           "Use -DNL_JSON"                      OFF)
option(BUILD_SHARED_LIBS "Building using shared libraries"    ON )  # MyLib is built into shared lib for now.

# Set path
set(READLINE_PATH   "" CACHE PATH "readline path")
set(Python_ROOT_DIR "" CACHE PATH "path root dir")
set(JSON_PATH       "" CACHE PATH "nlohmann_json path")

if (NOT SERIAL_MODE)
    set(MPI_HOME    "" CACHE PATH "mpi path")
endif ()

###### DEBUG Playground ################################################################################################
file(GENERATE OUTPUT debug_genexpr CONTENT
"$<$<BOOL:${INTERACTIVE_MODE}>:Timer.cpp>;
 $<$<NOT:$<STREQUAL:${READLINE_PATH},>>:ReadlinePathSet>
 $<$<STREQUAL:${READLINE_PATH},>:ReadlinePathSet>")

###### Directory #######################################################################################################
add_subdirectory(dependency)               # download dependency
add_subdirectory(src)                      # for library
add_subdirectory(example)                  # for example exe

###### Configuration Files #############################################################################################
configure_file(MyLib.pc.in MyLib.pc @ONLY) # for pkgconfig

###### Test ############################################################################################################
# Test can only be at top level CMakeLists.txt
enable_testing()

add_test(NAME ProgramRuns COMMAND example)
set_tests_properties(ProgramRuns PROPERTIES PASS_REGULAR_EXPRESSION "Hello, World!")

###### PACKAGING #######################################################################################################
# Only packaging library works
include(InstallRequiredSystemLibraries)
set(MYPROJECT_SRC "${CMAKE_CURRENT_SOURCE_DIR}")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE") # set license
set(CPACK_PACKAGE_VERSION_MAJOR "${MyLib_VERSION_MAJOR}")              # major version
set(CPACK_PACKAGE_VERSION_MINOR "${MyLib_VERSION_MINOR}")              # minor version
set(CPACK_SOURCE_GENERATOR "TGZ")                                      # packed format

include(CPack)
