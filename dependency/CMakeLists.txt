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
    find_package(nlohmann_json 3.2 QUIET PATHS "${JSON_PATH}") # TODO: probably don't need to set this JSON_PATH

    if (NOT nlohmann_json_FOUND)
        message(STATUS "NL_JSON is ON, cannot find nlohmann_json (nlohmann_json_DIR=\"${JSON_PATH}\")")
        set(FETCHCONTENT_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/nlohmann_json")
        FetchContent_Declare(
            nlohmann_json
            GIT_REPOSITORY "https://github.com/nlohmann/json.git"
            GIT_TAG v3.11.3
        )

        FetchContent_MakeAvailable(nlohmann_json)
        set(nlohmann_json_DIR "${CMAKE_CURRENT_SOURCE_DIR}/nlohmann_json/nlohmann_json-build" PARENT_SCOPE)
    else ()
        set(nlohmann_json_DIR "${JSON_PATH}" PARENT_SCOPE)
        message(STATUS "NL_JSON is ON, found nlohmann_json (nlohmann_json_DIR=\"${JSON_PATH}\")")
    endif ()

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
endif ()
