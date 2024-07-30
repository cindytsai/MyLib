if (USE_PYBIND11)
    find_package(pybind11 REQUIRED)
    message(STATUS "Found PyBind11 = \"${pybind11_INCLUDE_DIRS}\"")
endif()

add_library(PyBind11 PyBind11Demo.cpp)

if (USE_PYBIND11)
    target_compile_definitions(PyBind11 PUBLIC USE_PYBIND11)
    target_link_libraries(PyBind11 PUBLIC pybind11::embed)
endif ()