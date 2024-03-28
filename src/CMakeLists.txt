###### Print Info ######################################################################################################
function(print_option option_name)
    if (${option_name})
        message(STATUS "${option_name} is ON")
    else ()
        message(STATUS "${option_name} is OFF")
    endif ()
endfunction()

print_option(SERIAL)
print_option(INTERACTIVE_MODE)
print_option(SUPPORT_TIMER)
print_option(BUILD_SHARED_LIBS)
print_option(USE_BOO)

###### Compile Option ###################################################################################################
# C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

###### Sub Dir ########################################################
add_subdirectory(Python)
add_subdirectory(Utilities)
add_subdirectory(Comm)
add_subdirectory(LibraryAPI)
