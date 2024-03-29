include(FetchContent)


#if (NL_JSON)
#    # find package in dependency folder or user provided folder
#    if ("${JSON_PATH}" STREQUAL "")
#        set(JSON_PATH "${CMAKE_CURRENT_SOURCE_DIR}/nlohmann_json/share/cmake/nlohmann_json")
#    endif ()
#    find_package(nlohmann_json QUIET PATHS "${JSON_PATH}")
#
#    # if unable to find the package, install the package and update the path; otherwise, just update the path
#    if (NOT nlohmann_json_FOUND)
#        message(STATUS "NL_JSON is ON, cannot find nlohmann_json (nlohmann_json_DIR=\"${JSON_PATH}\")")
#        externalproject_add(
#            nlohmann_json
#            GIT_REPOSITORY "https://github.com/nlohmann/json.git"
#            GIT_TAG v3.11.3
#            CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/nlohmann_json
#            STEP_TARGETS build
#        )
#
#        set(nlohmann_json_DIR "${CMAKE_CURRENT_SOURCE_DIR}/nlohmann_json/share/cmake/nlohmann_json" PARENT_SCOPE)
#        message(STATUS "nlohmann_json will be installed when building project (nlohmann_json_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/nlohmann_json/share/cmake/nlohmann_json\")")
#    else ()
#        set(nlohmann_json_DIR "${JSON_PATH}" PARENT_SCOPE)
#        message(STATUS "NL_JSON is ON, found nlohmann_json (nlohmann_json_DIR=\"${nlohmann_json_DIR}\")")
#    endif ()
#endif ()

if (NL_JSON)
    ## JSON ########################################################
    # find package in dependency folder or user provided folder
#    find_package(nlohmann_json 3.2 QUIET)
#
#    if (NOT nlohmann_json_FOUND)
#        message(STATUS "NL_JSON is ON, cannot find nlohmann_json (nlohmann_json_DIR=\"${nlohmann_json_DIR}\")")
#        set(FETCHCONTENT_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/nlohmann_json")
#        FetchContent_Declare(
#            nlohmann_json
#            GIT_REPOSITORY "https://github.com/nlohmann/json.git"
#            GIT_TAG v3.11.3
#        )
#
#        FetchContent_MakeAvailable(nlohmann_json)
#        set(nlohmann_json_DIR "${CMAKE_CURRENT_SOURCE_DIR}/nlohmann_json/nlohmann_json-build" PARENT_SCOPE)
#    else ()
#        message(STATUS "NL_JSON is ON, found nlohmann_json (nlohmann_json_DIR=\"${nlohmann_json_DIR}\")")
#    endif ()

    ## XTL ########################################################
    find_package(xtl 0.7 QUIET)

    if (NOT xtl_FOUND)
        message(STATUS "NL_JSON is ON, cannot find xtl (xtl_DIR=\"${xtl_DIR}\")")
        set(FETCHCONTENT_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/xtl")
        FetchContent_Declare(
            xtl
            GIT_REPOSITORY "https://github.com/xtensor-stack/xtl.git"
            GIT_TAG 0.7.7
        )

        FetchContent_MakeAvailable(xtl)
        set(xtl_DIR "${CMAKE_CURRENT_SOURCE_DIR}/xtl/xtl-build" PARENT_SCOPE)
    else ()
        message(STATUS "NL_JSON is ON, found xtl (xtl_DIR=\"${xtl_DIR}\")")
    endif ()

    ## XEUS ##########################################################
#    find_package(xeus 3.0 QUIET)  # TODO: START HERE...
#
#    if (NOT xeus_FOUND)
#        message(STATUS "NL_JSON is ON, cannot find xeus (xeus_DIR=\"${xeus_DIR}\")")
#        set(FETCHCONTENT_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/xeus")
#        FetchContent_Declare(
#            xeus
#            GIT_REPOSITORY "https://github.com/jupyter-xeus/xeus.git"
#            GIT_TAG 3.2.0
#        )
#
#        FetchContent_GetProperties(xeus)
#        if (NOT xeus_POPULATED)
#            FetchContent_Populate(xeus)
#            set(nlohmann_json_DIR "${CMAKE_CURRENT_SOURCE_DIR}/nlohmann_json/nlohmann_json-build")
#            add_subdirectory(${xeus_SOURCE_DIR} ${xeus_BINARY_DIR})
#        endif ()
#
#        set(xeus_DIR "${CMAKE_CURRENT_SOURCE_DIR}/xeus/xeus-build" PARENT_SCOPE)
#    else ()
#        message(STATUS "NL_JSON is ON, found xeus (xeus_DIR=\"${xeus_DIR}\")")
#    endif ()

endif ()
