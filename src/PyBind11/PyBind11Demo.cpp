#ifdef USE_PYBIND11

#include "DataTypes/YTParameters.h"
#include "DataTypes/YTField.h"
#include "pybind11/embed.h"
#include <iostream>

#include "PyBind11Demo.h"

int PyBind11Initialize(const char *inline_script) {
    pybind11::initialize_interpreter();
    std::cout << "[PyBind11Initialize] Using Python " << std::endl;
    pybind11::exec("import sys; print(sys.version)");
    pybind11::exec("import " + std::string(inline_script));
    pybind11::exec("import libyt");
    std::cout << "[PyBind11Initialize] import " << inline_script << " and libyt" << std::endl;
    return 0;
}

int PyBind11Finalize() {
    pybind11::finalize_interpreter();
    return 0;
}

PYBIND11_EMBEDDED_MODULE(libyt, m) { // TODO: remember to change to libyt
    using namespace pybind11::literals; // to bring in the `_a` literal
    m.attr("demo") = pybind11::dict("spam"_a = pybind11::none());
    m.attr("param_yt") = pybind11::dict();
    m.attr("param_user") = pybind11::dict();
    m.attr("libyt_info") = pybind11::dict("version"_a = "0.0.1");

    m.def("add", [](int i, int j) {
        return i + j;
    });
    m.def("derived_func", []() {
    });
}

int PyBind11SetUserParameterInt(const char *key, int value) {
    std::cout << "[PyBind11] Setting user parameter" << std::endl;

    auto pybind11_libyt = pybind11::module_::import("libyt");
    pybind11::dict param_user = pybind11_libyt.attr("param_user");

    param_user[key] = value;

    pybind11::exec("import pprint; pprint.pprint(libyt.param_user)");

    return 0;
}

int PyBind11SetParameters(struct yt_param_yt *yt_param_ptr) {
    std::cout << "[PyBind11] Setting parameter" << std::endl;

    auto pybind11_libyt = pybind11::module_::import("libyt");
    pybind11::dict param_yt = pybind11_libyt.attr("param_yt");

    param_yt["frontend"] = yt_param_ptr->frontend; // string
    param_yt["fig_basename"] = yt_param_ptr->fig_basename; // string
    param_yt["length_unit"] = yt_param_ptr->length_unit; // double
    param_yt["mass_unit"] = yt_param_ptr->mass_unit; // double
    param_yt["time_unit"] = yt_param_ptr->time_unit; // double
    param_yt["magnetic_unit"] = yt_param_ptr->magnetic_unit; // double
    param_yt["velocity_unit"] = yt_param_ptr->velocity_unit; // double

    param_yt["current_time"] = yt_param_ptr->current_time; // double
    param_yt["dimensionality"] = yt_param_ptr->dimensionality; // int
    param_yt["refine_by"] = yt_param_ptr->refine_by; // int
    param_yt["num_grids"] = yt_param_ptr->num_grids; // long
    param_yt["cosmological_simulation"] = yt_param_ptr->cosmological_simulation; // int
    param_yt["current_redshift"] = yt_param_ptr->current_redshift; // double
    param_yt["omega_lambda"] = yt_param_ptr->omega_lambda; // double
    param_yt["omega_matter"] = yt_param_ptr->omega_matter; // double
    param_yt["hubble_constant"] = yt_param_ptr->hubble_constant; // double
    param_yt["num_grids_local"] = yt_param_ptr->num_grids_local; // int
    param_yt["num_fields"] = yt_param_ptr->num_fields; // int
    param_yt["index_offset"] = yt_param_ptr->index_offset; // int

    param_yt["domain_dimensions"] = pybind11::make_tuple(yt_param_ptr->domain_dimensions[0],
                                                         yt_param_ptr->domain_dimensions[1],
                                                         yt_param_ptr->domain_dimensions[2]);
    param_yt["domain_left_edge"] = pybind11::make_tuple(yt_param_ptr->domain_left_edge[0],
                                                        yt_param_ptr->domain_left_edge[1],
                                                        yt_param_ptr->domain_left_edge[2]);
    param_yt["domain_right_edge"] = pybind11::make_tuple(yt_param_ptr->domain_right_edge[0],
                                                         yt_param_ptr->domain_right_edge[1],
                                                         yt_param_ptr->domain_right_edge[2]);
    param_yt["periodicity"] = pybind11::make_tuple(yt_param_ptr->periodicity[0],
                                                   yt_param_ptr->periodicity[1],
                                                   yt_param_ptr->periodicity[2]);

    pybind11::exec("import pprint; pprint.pprint(libyt.param_yt)");

    return 0;
}

int PyBind11SetFields(struct yt_field *yt_field_ptr, int len) {
    std::cout << "[PyBind11] Setting fields " << std::endl;

    auto pybind11_libyt = pybind11::module_::import("libyt");
    pybind11::dict param_yt = pybind11_libyt.attr("param_yt");

    pybind11::dict field_list = pybind11::dict();
    param_yt["field_list"] = field_list;

    for (int i = 0; i < len; i++) {
        field_list[yt_field_ptr[i].field_name] = pybind11::dict();
        field_list[yt_field_ptr[i].field_name]["attribute"] = pybind11::make_tuple(yt_field_ptr[i].field_unit,
                                                                                   pybind11::list(),
                                                                                   yt_field_ptr[i].field_display_name);
        field_list[yt_field_ptr[i].field_name]["field_type"] = yt_field_ptr[i].field_type;
        field_list[yt_field_ptr[i].field_name]["ghost_cell"] = pybind11::make_tuple(yt_field_ptr[i].field_ghost_cell[0],
                                                                                    yt_field_ptr[i].field_ghost_cell[1],
                                                                                    yt_field_ptr[i].field_ghost_cell[2],
                                                                                    yt_field_ptr[i].field_ghost_cell[3],
                                                                                    yt_field_ptr[i].field_ghost_cell[4],
                                                                                    yt_field_ptr[i].field_ghost_cell[5]);
        field_list[yt_field_ptr[i].field_name]["contiguous_in_x"] = pybind11::bool_(yt_field_ptr[i].contiguous_in_x);
    }

    pybind11::exec("import pprint; pprint.pprint(libyt.param_yt)");

    return 0;
}

int PyBind11Run(const char *inline_script, const char *function) {
    std::cout << "[PyBind11] Running " << function << std::endl;

    pybind11::exec(std::string(inline_script) + "." + std::string(function) + "()");

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