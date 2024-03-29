###### Target ##########################################################################################################
add_library(MyLib SHARED library.cpp)

###### Define, Include, Link ###########################################################################################
target_include_directories(MyLib PRIVATE "..")
target_link_libraries(MyLib PRIVATE MPICore PythonCore Logger)
if (NL_JSON)
    ## NLOHMANN_JSON ###################################################################################################
    find_package(nlohmann_json 3.2 QUIET)

    if (NOT nlohmann_json_FOUND)
        message(STATUS "NL_JSON is ON, cannot find nlohmann_json (nlohmann_json_DIR=\"${nlohmann_json_DIR}\")")
        set(FETCHCONTENT_BASE_DIR "${PROJECT_SOURCE_DIR}/dependency/nlohmann_json")
        FetchContent_Declare(
            nlohmann_json
            GIT_REPOSITORY "https://github.com/nlohmann/json.git"
            GIT_TAG v3.11.3
        )

        FetchContent_MakeAvailable(nlohmann_json)
    else ()
        message(STATUS "NL_JSON is ON, found nlohmann_json (nlohmann_json_DIR=\"${nlohmann_json_DIR}\")")
    endif ()
    target_compile_definitions(MyLib PUBLIC NL_JSON)
    target_link_libraries(MyLib PRIVATE nlohmann_json::nlohmann_json)

    ## ZEROMQ ##########################################################################################################
    find_package(ZeroMQ 4.2 QUIET)

    if (NOT ZeroMQ_FOUND)
        # try using pkg-config to find zermq
        find_package(PkgConfig REQUIRED)  # TODO: possibly get pkg-config through cmake if the system does not have it.
        pkg_check_modules(PC_ZeroMQ QUIET libzmq>=4.2)

        if (NOT PC_ZeroMQ_FOUND)
            message(STATUS "NL_JSON is ON, cannot find ZeroMQ libzmq (ZeroMQ_DIR=\"${ZeroMQ_DIR}\")")
            set(FETCHCONTENT_BASE_DIR "${PROJECT_SOURCE_DIR}/dependency/libzmq")
            FetchContent_Declare(
                libzmq
                GIT_REPOSITORY "https://github.com/zeromq/libzmq.git"
                GIT_TAG v4.3.5
            )
            FetchContent_MakeAvailable(libzmq)
            # TODO: can download, but how to populate
        else ()
            message(STATUS "NL_JSON is ON, found ZeroMQ libzmq-${PC_ZeroMQ_VERSION} (\"${PC_ZeroMQ_LINK_LIBRARIES}\")")
            find_path(
                ZeroMQ_INCLUDE_DIR
                NAMES zmq.hpp
                PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
            )
            find_library(
                ZeroMQ_LIBRARY
                NAMES zmq
                PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
            )
            # TODO: populate zeromq dirs
        endif ()
    else () # found ZeroMQ through find_package
        message(STATUS "NL_JSON is ON, found ZeroMQ (ZeroMQ_DIR=\"${ZeroMQ_DIR}\")")
    endif () # if (NOT ZeroMQ_FOUND) found through find_package


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