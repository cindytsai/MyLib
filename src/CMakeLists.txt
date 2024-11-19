###### Print Info ######################################################################################################
function(print_option option_name)
    if (${option_name})
        message(STATUS "${option_name} is ON")
    else ()
        message(STATUS "${option_name} is OFF")
    endif ()
endfunction()

print_option(USE_BOO)
print_option(USE_PYTHON)
print_option(USE_MPI)
print_option(USE_READLINE)
print_option(USE_NLJSON)
print_option(USE_PYBIND11)
print_option(USE_DUCKDB)
print_option(SUPPORT_TIMER)
print_option(BUILD_SHARED_LIBS)

###### Compile Option ###################################################################################################
# C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

###### Sub Dir ########################################################
add_subdirectory(Python)
add_subdirectory(Utilities)
add_subdirectory(Comm)
add_subdirectory(LibraryAPI)
add_subdirectory(PyBind11)
add_subdirectory(DuckDB)