include(FetchContent)

if (USE_READLINE)

    find_path(Readline_ROOT_DIR
            NAMES include/readline/readline.h
            HINTS ${READLINE_PATH}
    )

    find_path(Readline_INCLUDE_DIR
            NAMES readline/readline.h
            HINTS ${Readline_ROOT_DIR}/include
    )

    find_library(Readline_LIBRARY
            NAMES readline
            HINTS ${Readline_ROOT_DIR}/lib
    )

    if (Readline_INCLUDE_DIR AND Readline_LIBRARY)
        if (Readline_ROOT_DIR STREQUAL READLINE_PATH)
            set(ENV{PKG_CONFIG_PATH} "${Readline_ROOT_DIR}/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")
        endif ()
        execute_process(COMMAND pkg-config --libs readline --static OUTPUT_VARIABLE Readline_LIBFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
        set(Readline_LIBFLAGS ${Readline_LIBFLAGS} PARENT_SCOPE)
        message(STATUS "Found readline: ${Readline_LIBRARY} (link flags: ${Readline_LIBFLAGS})")
    else ()
        message(FATAL_ERROR "Unable to find readline, please visit https://tiswww.case.edu/php/chet/readline/rltop.html for more information..." )
    endif ()

endif () # if (USE_READLINE)

if (USE_NLJSON)
    ## fetch version
    set(LIBYT_NLOHMANN_JSON_FETCH_VERSION    3.11.3 )

    ## required version
    set(LIBYT_NLOHMANN_JSON_REQUIRED_VERSION 3.2.0 )

    ## get dependencies and populate
    find_package(nlohmann_json ${LIBYT_NLOHMANN_JSON_REQUIRED_VERSION} QUIET)
    if (NOT nlohmann_json_FOUND)
        message(STATUS "Unable to find nlohmann_json, getting dependency...")
        set(FETCHCONTENT_BASE_DIR "${PROJECT_SOURCE_DIR}/vendor/nlohmann_json")
        FetchContent_Declare(
                nlohmann_json
                GIT_REPOSITORY "https://github.com/nlohmann/json.git"
                GIT_TAG "v${LIBYT_NLOHMANN_JSON_FETCH_VERSION}"
                GIT_SHALLOW TRUE
        )
        FetchContent_GetProperties(nlohmann_json)
        if (NOT nlohmann_json_POPULATED)
            FetchContent_Populate(nlohmann_json)
            option(JSON_Install ON)
            add_subdirectory(${nlohmann_json_SOURCE_DIR} ${nlohmann_json_BINARY_DIR} EXCLUDE_FROM_ALL)
        endif ()
    else ()
        message(STATUS "Found nlohmann_json: ${nlohmann_json_DIR} (found version \"${nlohmann_json_VERSION}\")")
    endif ()

endif () # if (USE_NLJSON)
