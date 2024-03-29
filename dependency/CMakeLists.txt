include(ExternalProject)

if (NL_JSON AND "${JSON_PATH}" STREQUAL "")
    set(nlohmann_json_DIR "${CMAKE_CURRENT_SOURCE_DIR}/nlohmann_json/share/cmake/nlohmann_json")
    find_package(nlohmann_json QUIET)
    if (NOT nlohmann_json_FOUND)
        message(STATUS "NL_JSON is ON, cannot find nlohmann_json (JSON_PATH=\"${JSON_PATH}\")")
        externalproject_add(
            nlohmann_json
            GIT_REPOSITORY "https://github.com/nlohmann/json.git"
            GIT_TAG v3.11.3
            CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/nlohmann_json
        )
    else ()
        message(STATUS "NL_JSON is ON, found nlohmann_json (JSON_PATH=\"${nlohmann_json_DIR}\")")
    endif ()
endif ()

