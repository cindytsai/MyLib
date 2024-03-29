###### Target ##########################################################################################################
add_library(MyLib SHARED library.cpp)

###### Define, Include, Link ###########################################################################################
target_include_directories(MyLib PRIVATE "..")
target_link_libraries(MyLib PRIVATE MPICore PythonCore Logger)
if (NL_JSON)
    find_package(xtl 0.7 REQUIRED)
    find_package(nlohmann_json 3.2 REQUIRED)
    target_compile_definitions(MyLib PUBLIC NL_JSON)
    target_link_libraries(MyLib PRIVATE nlohmann_json::nlohmann_json xtl)
endif ()


###### Properties ######################################################################################################
set(MyLib_PUBLIC_HEADER "library.h")
set_target_properties(MyLib PROPERTIES
        VERSION ${PROJECT_VERSION}                             # version
        SOVERSION ${PROJECT_VERSION_MAJOR}                     # soversion (.so.x.y.z)
        PUBLIC_HEADER "${MyLib_PUBLIC_HEADER}"                 # Separate APIs from private header
        POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS})        # build PIC

###### INSTALLATION RULE ###############################################################################################
include(GNUInstallDirs)
install(TARGETS MyLib
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/MyLib.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)