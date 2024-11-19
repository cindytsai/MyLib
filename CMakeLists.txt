cmake_minimum_required(VERSION 3.15)

###### PROJECT Info ####################################################################################################
project(MyLib VERSION 0.1 DESCRIPTION "Testing template library setup")

# Set option
option(USE_BOO           "Use -DUSE_BOO (test option)"        OFF)
option(USE_PYTHON        "Use Python >= 3.7"                  OFF)
option(USE_MPI           "Use MPI"                            OFF)
option(USE_READLINE      "Use readline"                       OFF)
option(USE_NLJSON        "Use nlohmann_json"                  OFF)
option(USE_PYBIND11      "Use pybind11"                       OFF)
option(USE_DUCKDB        "Use DuckDB"                         OFF)
option(SUPPORT_TIMER     "Support time profile"               OFF)
option(BUILD_SHARED_LIBS "Building using shared libraries"    ON )  # MyLib is built into shared lib for now.

# Set path
set(PYTHON_PATH        "" CACHE PATH "Path to Python installation prefix (-DUSE_PYTHON=ON)")
set(MPI_PATH           "" CACHE PATH "Path to MPI installation prefix (-DUSE_MPI=ON)")
set(READLINE_PATH      "" CACHE PATH "Path to Readline installation prefix (-DUSE_READLINE=ON)")
set(PYBIND11_PATH      "" CACHE PATH "Path to pybind11Config.cmake (-DUSE_PYBIND11=ON)")
set(NLJSON_PATH        "" CACHE PATH "Path to nlohmann_json prefix (-DUSE_NLJSON=ON)")

###### DEBUG Playground ################################################################################################
file(GENERATE OUTPUT debug_genexpr CONTENT
"$<$<BOOL:${INTERACTIVE_MODE}>:Timer.cpp>;
 $<$<NOT:$<STREQUAL:${READLINE_PATH},>>:ReadlinePathSet>
 $<$<STREQUAL:${READLINE_PATH},>:ReadlinePathSet>")

###### Mapping paths and dependencies ##################################################################################
if (USE_MPI)
    set(MPI_HOME ${MPI_PATH})
endif ()

if (USE_PYTHON)
    set(Python_ROOT_DIR ${PYTHON_PATH})
endif ()

if (USE_NLJSON)
    set(nlohmann_json_DIR ${NLJSON_PATH})
endif ()

if (USE_PYBIND11)
    set(pybind11_DIR ${PYBIND11_PATH})
endif ()

###### Compilation ####################################################################################################
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

###### Directory #######################################################################################################
add_subdirectory(vendor)                   # download dependency
add_subdirectory(src)                      # for library
add_subdirectory(example)                  # for example exe

###### Configuration Files #############################################################################################
# Ignore for now
#configure_file(MyLib.pc.in MyLib.pc @ONLY) # for pkgconfig

###### Test ############################################################################################################
# TODO: googletest

###### PACKAGING #######################################################################################################
# Ignore for now
