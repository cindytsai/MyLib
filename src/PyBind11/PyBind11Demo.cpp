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

PYBIND11_EMBEDDED_MODULE(fast_calc, m) {
    // `m` is a `py::module_` which is used to bind functions and classes
    m.def("add", [](int i, int j) {
        return i + j;
    });
}

int PyBind11CallTestScript() {
    std::cout << "====================" << std::endl;
    pybind11::exec("import sys;");
    pybind11::exec("import test_script; test_script.test_func()");
    pybind11::exec("print(dir())");
    pybind11::exec("print(locals())");
    std::cout << "====================" << std::endl;
    auto fast_calc = pybind11::module_::import("fast_calc");
    auto result = fast_calc.attr("add")(1, 2).cast<int>();
    std::cout << result << std::endl; // should be 3
    std::cout << "====================" << std::endl;
    return 0;
}

#endif