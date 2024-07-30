#ifdef USE_PYBIND11

#include "pybind11/embed.h"
#include <iostream>

#include "PyBind11Demo.h"


int CallPyBind11Demo() {
    std::cout << "====================" << std::endl;
    pybind11::initialize_interpreter();
    {
        pybind11::exec("import sys; print(sys.version)");
    }
    pybind11::finalize_interpreter();
    std::cout << "====================" << std::endl;
    return 0;
}

#endif