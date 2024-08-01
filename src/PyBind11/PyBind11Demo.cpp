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

PYBIND11_EMBEDDED_MODULE(pybind11_libyt, m) { // TODO: remember to change to pybind11_libyt
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

    hier["frontend"] = yt_param_ptr->frontend; // string
    hier["fig_basename"] = yt_param_ptr->fig_basename; // string
    hier["length_unit"] = yt_param_ptr->length_unit; // double
    hier["mass_unit"] = yt_param_ptr->mass_unit; // double
    hier["time_unit"] = yt_param_ptr->time_unit; // double
    hier["magnetic_unit"] = yt_param_ptr->magnetic_unit; // double
    hier["velocity_unit"] = yt_param_ptr->velocity_unit; // double

    hier["current_time"] = yt_param_ptr->current_time; // double
    hier["dimensionality"] = yt_param_ptr->dimensionality; // int
    hier["refine_by"] = yt_param_ptr->refine_by; // int
    hier["num_grids"] = yt_param_ptr->num_grids; // long
    hier["cosmological_simulation"] = yt_param_ptr->cosmological_simulation; // int
    hier["current_redshift"] = yt_param_ptr->current_redshift; // double
    hier["omega_lambda"] = yt_param_ptr->omega_lambda; // double
    hier["omega_matter"] = yt_param_ptr->omega_matter; // double
    hier["hubble_constant"] = yt_param_ptr->hubble_constant; // double
    hier["num_grids_local"] = yt_param_ptr->num_grids_local; // int
    hier["num_fields"] = yt_param_ptr->num_fields; // int

    hier["domain_dimensions"] = pybind11::make_tuple(yt_param_ptr->domain_dimensions[0],
                                                     yt_param_ptr->domain_dimensions[1],
                                                     yt_param_ptr->domain_dimensions[2]);
    hier["domain_left_edge"] = pybind11::make_tuple(yt_param_ptr->domain_left_edge[0],
                                                    yt_param_ptr->domain_left_edge[1],
                                                    yt_param_ptr->domain_left_edge[2]);
    hier["domain_right_edge"] = pybind11::make_tuple(yt_param_ptr->domain_right_edge[0],
                                                     yt_param_ptr->domain_right_edge[1],
                                                     yt_param_ptr->domain_right_edge[2]);
    hier["periodicity"] = pybind11::make_tuple(yt_param_ptr->periodicity[0],
                                              yt_param_ptr->periodicity[1],
                                              yt_param_ptr->periodicity[2]);

    pybind11::exec("import pprint; pprint.pprint(pybind11_libyt.param_yt)");

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