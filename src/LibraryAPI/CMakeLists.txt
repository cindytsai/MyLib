include(FetchContent)
###### Target ##########################################################################################################
add_library(MyLib SHARED library.cpp)

###### Define, Include, Link ###########################################################################################
if (USE_NLJSON)
    target_compile_definitions(MyLib PUBLIC USE_NLJSON)
    target_link_libraries(MyLib PRIVATE nlohmann_json::nlohmann_json)
endif ()
target_include_directories(MyLib PUBLIC "${PROJECT_SOURCE_DIR}/src")
target_link_libraries(MyLib
        PRIVATE MPICore PythonCore Logger PyBind11
)

###### Properties ######################################################################################################
set(MyLib_PUBLIC_HEADER "library.h")
set_target_properties(MyLib PROPERTIES
        VERSION ${PROJECT_VERSION}                             # version
        SOVERSION ${PROJECT_VERSION_MAJOR}                     # soversion (.so.x.y.z)
        PUBLIC_HEADER "${MyLib_PUBLIC_HEADER}"                 # Separate APIs from private header
        POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS}         # build PIC
)

###### INSTALLATION RULE ###############################################################################################
include(GNUInstallDirs)
install(TARGETS MyLib
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/src/DataTypes"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/DataTypes" FILES_MATCHING PATTERN "*.h"
)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/src/Macro"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/Macro" FILES_MATCHING PATTERN "*.h"
)
# TODO: include works properly, but linking isn't working properly.