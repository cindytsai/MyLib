#ifdef USE_PYBIND11

#include "pybind11/embed.h"
#include <iostream>

#include "PyBind11Demo.h"

int PyBind11Initialize() {
    pybind11::initialize_interpreter();
    return 0;
}

int PyBind11Finalize() {
    pybind11::finalize_interpreter();
    return 0;
}

int CallPyBind11Demo() {
    std::cout << "====================" << std::endl;
    pybind11::exec("import sys; sys.path.insert(0, '.'); print(sys.path)");
    pybind11::exec("import test_script; test_func()");
    std::cout << "====================" << std::endl;
    return 0;
}

#endif