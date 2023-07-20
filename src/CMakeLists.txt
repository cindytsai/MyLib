### MyLib COMPILATION ###
add_library(MyLib SHARED library.cpp)

# properties
set_target_properties(MyLib PROPERTIES
        VERSION ${PROJECT_VERSION}                             # version
        SOVERSION ${PROJECT_VERSION_MAJOR}                     # soversion (.so.x.y.z)
        PUBLIC_HEADER ${PROJECT_SOURCE_DIR}/include/library.h  # Seperate APIs from private header
        POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS})        # build PIC

# include dir
target_include_directories(MyLib PRIVATE
        ${PROJECT_SOURCE_DIR}/include)

### MyLib INSTALLATION RULE ###
include(GNUInstallDirs)
install(TARGETS MyLib
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/MyLib.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
