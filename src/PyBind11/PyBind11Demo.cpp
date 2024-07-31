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

PYBIND11_EMBEDDED_MODULE(pybind11_libyt, m) {
    using namespace pybind11::literals; // to bring in the `_a` literal
    m.attr("hierarchy") = pybind11::dict("spam"_a=pybind11::none());
    m.def("add", [](int i, int j) {
        return i + j;
    });
}

int PyBind11CallTestScript() {
    std::cout << "====================" << std::endl;
    pybind11::exec("import sys; print(sys.version)");
    pybind11::exec("import test_script; test_script.test_func()");
    pybind11::exec("print(dir())");
    pybind11::exec("print(locals())");
    std::cout << "====================" << std::endl;
    auto pybind11_libyt = pybind11::module_::import("pybind11_libyt");
    pybind11::exec("print(dir())"); // does not show pybind11_libyt
    std::cout << "====================" << std::endl;
    pybind11::exec("import pybind11_libyt");
    pybind11::exec("print(dir())"); // showing pybind11_libyt
    std::cout << "====================" << std::endl;
    pybind11::exec("print(dir(pybind11_libyt))");
    pybind11::exec("print(pybind11_libyt.hierarchy)");
    auto hier = pybind11_libyt.attr("hierarchy");
    hier["spam"] = 1;
    pybind11::exec("print(pybind11_libyt.hierarchy)");
    pybind11::object result = pybind11_libyt.attr("add")(1, 2);
    std::cout << "call pybind11_libyt.add(1,2) = " << result.cast<int>() << std::endl;
    return 0;
}

#endif