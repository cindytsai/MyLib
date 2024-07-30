if (USE_PYTHON)
    find_package(Python 3.7 COMPONENTS Development NumPy REQUIRED)
    message(STATUS "Found Python = \"${PYTHON_PATH}\"")
endif ()

add_library(PythonCore PythonCore.cpp)

if (USE_PYTHON)
    if (USE_BOO)
        target_compile_definitions(PythonCore PUBLIC USE_BOO)
    endif ()

    target_compile_definitions(PythonCore PUBLIC USE_PYTHON)
    target_include_directories(PythonCore PUBLIC ${Python_INCLUDE_DIRS})
    target_link_libraries(PythonCore PUBLIC ${Python_LIBRARIES})
endif ()

## Install ######################3
if (USE_PYTHON)
    install(TARGETS PythonCore DESTINATION lib)
endif ()
