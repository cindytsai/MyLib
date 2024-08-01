#ifdef USE_PYBIND11

#include "DataTypes/YTParameters.h"
#include "pybind11/embed.h"
#include <iostream>

#include "PyBind11Demo.h"

int PyBind11Initialize(const char *inline_script) {
    pybind11::initialize_interpreter();
    std::cout << "[PyBind11Initialize] Using Python " << std::endl;
    pybind11::exec("import sys; print(sys.version)");
    pybind11::exec("import " + std::string(inline_script));
    pybind11::exec("import pybind11_libyt");
    std::cout << "[PyBind11Initialize] import " << inline_script << " and pybind11_libyt" << std::endl;
    return 0;
}

int PyBind11Finalize() {
    pybind11::finalize_interpreter();
    return 0;
}

PYBIND11_EMBEDDED_MODULE(pybind11_libyt, m) {
    using namespace pybind11::literals; // to bring in the `_a` literal
    m.attr("demo") = pybind11::dict("spam"_a = pybind11::none());
    m.attr("param_yt") = pybind11::dict();
    m.def("add", [](int i, int j) {
        return i + j;
    });
    m.def("derived_func", []() {
    });
}

int PyBind11SetParameters(struct yt_param_yt *yt_param_ptr) {
    std::cout << "[PyBind11] Setting parameter" << std::endl;

    auto pybind11_libyt = pybind11::module_::import("pybind11_libyt");
    pybind11::dict hier = pybind11_libyt.attr("param_yt");

    hier["frontend"] = 1;

    pybind11::exec("print(pybind11_libyt.param_yt)");

    return 0;
}

int PyBind11CallTestScript() {
    /*
     * Call in example.cpp only
     */
    std::cout << "====================" << std::endl;
    auto pybind11_libyt = pybind11::module_::import("pybind11_libyt");
    pybind11::exec("print(dir())"); // does not show pybind11_libyt
    std::cout << "====================" << std::endl;
    pybind11::exec("import pybind11_libyt");
    pybind11::exec("print(dir())"); // showing pybind11_libyt
    std::cout << "====================" << std::endl;
    pybind11::exec("print(dir(pybind11_libyt))");
    pybind11::exec("print(pybind11_libyt.demo)");
    pybind11::dict demo = pybind11_libyt.attr("demo");
    demo["spam"] = 1;
    pybind11::exec("print(pybind11_libyt.demo)");
    pybind11::object result = pybind11_libyt.attr("add")(1, 2);
    std::cout << "call pybind11_libyt.add(1,2) = " << result.cast<int>() << std::endl;

    return 0;
}

#endif