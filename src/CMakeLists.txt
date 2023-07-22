### MyLib COMPILATION ###
add_library(MyLib SHARED library.cpp)

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

# define
if (USE_BOO)
    target_compile_definitions(MyLib PRIVATE USE_BOO)
endif ()

# include dir
target_include_directories(MyLib PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${MPI_PATH}/include
        ${PYTHON_PATH}/include/python${PYTHON_VERSION})

# link lib
target_link_directories(MyLib PRIVATE
        ${MPI_PATH}/lib
        ${PYTHON_PATH}/lib)
target_link_libraries(MyLib PRIVATE
        mpi
        python${PYTHON_VERSION})

# properties
set(MyLib_PUBLIC_HEADER "${PROJECT_SOURCE_DIR}/include/library.h;"
                        "${PROJECT_SOURCE_DIR}/include/temp.h")
set_target_properties(MyLib PROPERTIES
        VERSION ${PROJECT_VERSION}                             # version
        SOVERSION ${PROJECT_VERSION_MAJOR}                     # soversion (.so.x.y.z)
        PUBLIC_HEADER "${MyLib_PUBLIC_HEADER}"                 # Seperate APIs from private header
        POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS})        # build PIC

### MyLib INSTALLATION RULE ###
include(GNUInstallDirs)
install(TARGETS MyLib
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/MyLib.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
