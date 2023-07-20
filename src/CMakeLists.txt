### MyLib COMPILATION ###
add_library(MyLib SHARED library.cpp)

# properties
set_target_properties(MyLib PROPERTIES
        VERSION ${PROJECT_VERSION}                             # version
        SOVERSION ${PROJECT_VERSION_MAJOR}                     # soversion (.so.x.y.z)
        PUBLIC_HEADER ${PROJECT_SOURCE_DIR}/include/library.h  # Seperate APIs from private header
        POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS})        # build PIC

# options
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

# include dir
target_include_directories(MyLib PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${MPI_PATH}/include
        ${PYTHON_PATH}/include)

# link lib
target_link_directories(MyLib PRIVATE
        ${MPI_PATH}/lib
        ${PYTHON_PATH}/lib)
target_link_libraries(MyLib PRIVATE
        mpi
        python${PYTHON_VERSION})


### MyLib INSTALLATION RULE ###
include(GNUInstallDirs)
install(TARGETS MyLib
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/MyLib.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
