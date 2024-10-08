if (USE_PYBIND11)
    find_package(Python COMPONENTS Interpreter Development NumPy REQUIRED)
    find_package(pybind11 REQUIRED)
    message(STATUS "Found PyBind11 = \"${pybind11_INCLUDE_DIRS}\"")
endif()


add_library(PyBind11 PyBind11Demo.cpp)

if (USE_PYBIND11)
    target_compile_definitions(PyBind11 PUBLIC USE_PYBIND11)
    target_include_directories(PyBind11 PUBLIC ${PROJECT_SOURCE_DIR}/src)
    target_link_libraries(PyBind11 PUBLIC pybind11::embed Python::NumPy)
    configure_file(test_script.py ${PROJECT_BINARY_DIR}/example/cpp_example/test_script.py COPYONLY)
endif ()

if (SUPPORT_TIMER)
    target_compile_definitions(PyBind11 PUBLIC SUPPORT_TIMER)
    target_link_libraries(PyBind11 PUBLIC Timer)
endif ()

if (USE_VALGRIND)
    find_program(VALGRIND_EXECUTABLE valgrind)
    target_compile_definitions(PyBind11 PUBLIC USE_VALGRIND)
    if (VALGRIND_EXECUTABLE)
        message(STATUS "Found Valgrind = \"${VALGRIND_EXECUTABLE}\"")
    else ()
        message(FATAL_ERROR "Valgrind not found")
    endif ()
endif ()
