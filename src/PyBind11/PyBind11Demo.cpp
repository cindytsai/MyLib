#ifdef USE_PYBIND11

#include "DataTypes/YTParameters.h"
#include "DataTypes/YTField.h"
#include "DataTypes/YTGrid.h"
#include "pybind11/embed.h"
#include "pybind11/numpy.h"
#include <iostream>
#ifdef USE_VALGRIND
#include <valgrind/valgrind.h>
#endif

#define INIT_GLOBAL
#include "PyBind11Demo.h"
#undef INIT_GLOBAL

int PyBind11Initialize() {
#ifdef SUPPORT_TIMER
    timer_control.CreateFile("MyLibTimeProfile.json", 0);
    SET_TIMER(__PRETTY_FUNCTION__, &timer_control);
#endif

    pybind11::initialize_interpreter();
    std::cout << "[PyBind11Initialize] Using Python " << std::endl;
    pybind11::exec("import sys; print(sys.version)");
    return 0;
}

int PyBind11Import(const char *inline_script) {
#ifdef SUPPORT_TIMER
    SET_TIMER(__PRETTY_FUNCTION__, &timer_control);
#endif
    pybind11::exec("import " + std::string(inline_script));
    pybind11::exec("import libyt");
    std::cout << "[PyBind11Initialize] import " << inline_script << " and libyt" << std::endl;
    return 0;
}

int PyBind11Finalize() {
#ifdef SUPPORT_TIMER
    SET_TIMER(__PRETTY_FUNCTION__, &timer_control);
#endif
    pybind11::finalize_interpreter();
    return 0;
}

pybind11::array derived_func(long gid, const char* fname) {
#ifdef SUPPORT_TIMER
    SET_TIMER(__PRETTY_FUNCTION__, &timer_control);
#endif
    std::cout << "[PyBind11] derived_func" << std::endl;

    int *grid_dim = &grid_dimensions[gid * 3];
    int field_index = -1;
    void (*derived_func)(const int, const long*, const char*, struct yt_data*) = nullptr;
    for (int f = 0; f < global_num_fields; f++) {
        if (strcmp(global_field_list[f].field_name, fname) == 0) {
            field_index = f;
            derived_func = global_field_list[f].derived_func;
            break;
        }
    }

    // TODO: fixed for double for now, and also fixed to contiguous_in_x = True
    auto array = pybind11::array_t<double>({grid_dim[2], grid_dim[1], grid_dim[0]},
                                           {sizeof(double),
                                            sizeof(double) * grid_dim[1],
                                            sizeof(double) * grid_dim[1] * grid_dim[2]});

    struct yt_data *data_array = new struct yt_data [1];
    data_array[0].data_ptr = static_cast<void*>(array.mutable_data());
    data_array[0].data_dimensions[0] = grid_dim[2];
    data_array[0].data_dimensions[1] = grid_dim[1];
    data_array[0].data_dimensions[2] = grid_dim[0];

    derived_func(1, &gid, fname, data_array);

    delete [] data_array;

    return static_cast<pybind11::array>(array);
}

PYBIND11_EMBEDDED_MODULE(libyt, m) {
#ifdef SUPPORT_TIMER
    SET_TIMER(__PRETTY_FUNCTION__, &timer_control);
#endif
    using namespace pybind11::literals; // to bring in the `_a` literal
    m.attr("demo") = pybind11::dict("spam"_a = pybind11::none());
    m.attr("param_yt") = pybind11::dict();
    m.attr("param_user") = pybind11::dict();
    m.attr("hierarchy") = pybind11::dict();
    m.attr("grid_data") = pybind11::dict();
    m.attr("libyt_info") = pybind11::dict();

    m.attr("libyt_info")["version"] = pybind11::make_tuple(0, 1, 0);
    m.attr("libyt_info")["SERIAL_MODE"] = pybind11::bool_(true);
    m.attr("libyt_info")["INTERACTIVE_MODE"] = pybind11::bool_(false);
    m.attr("libyt_info")["JUPYTER_KERNEL"] = pybind11::bool_(false);
#ifdef SUPPORT_TIMER
    m.attr("libyt_info")["SUPPORT_TIMER"] = pybind11::bool_(true);
#else
    m.attr("libyt_info")["SUPPORT_TIMER"] = pybind11::bool_(false);
#endif


    m.def("add", [](int i, int j) {
        return i + j;
    });
    m.def("derived_func", &derived_func, pybind11::return_value_policy::take_ownership);
}

int PyBind11SetUserParameterInt(const char *key, int value) {
#ifdef SUPPORT_TIMER
    SET_TIMER(__PRETTY_FUNCTION__, &timer_control);
#endif
    std::cout << "[PyBind11] Setting user parameter" << std::endl;

    auto pybind11_libyt = pybind11::module_::import("libyt");
    pybind11::dict param_user = pybind11_libyt.attr("param_user");

    param_user[key] = value;

//    pybind11::exec("import pprint; pprint.pprint(libyt.param_user)");

    return 0;
}

int PyBind11SetUserParameterDouble(const char *key, double value) {
#ifdef SUPPORT_TIMER
    SET_TIMER(__PRETTY_FUNCTION__, &timer_control);
#endif
    std::cout << "[PyBind11] Setting user parameter" << std::endl;

    auto pybind11_libyt = pybind11::module_::import("libyt");
    pybind11::dict param_user = pybind11_libyt.attr("param_user");

    param_user[key] = value;

//    pybind11::exec("import pprint; pprint.pprint(libyt.param_user)");

    return 0;
}

int PyBind11SetParameters(struct yt_param_yt *yt_param_ptr) {
#ifdef SUPPORT_TIMER
    SET_TIMER(__PRETTY_FUNCTION__, &timer_control);
#endif
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

//    pybind11::exec("import pprint; pprint.pprint(libyt.param_yt)");

    return 0;
}

int PyBind11SetFields(struct yt_field *yt_field_ptr, int len) {
#ifdef SUPPORT_TIMER
    SET_TIMER(__PRETTY_FUNCTION__, &timer_control);
#endif
    std::cout << "[PyBind11] Setting fields " << std::endl;

    global_field_list = yt_field_ptr;
    global_num_fields = len;

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

//    pybind11::exec("import pprint; pprint.pprint(libyt.param_yt)");

    return 0;
}

int PyBind11InitHier(int num_grids, struct yt_grid **grids_local) {
#ifdef SUPPORT_TIMER
    SET_TIMER(__PRETTY_FUNCTION__, &timer_control);
#endif
    std::cout << "[PyBind11] Setting hierarchy " << std::endl;

    auto pybind11_libyt = pybind11::module_::import("libyt");
    pybind11::dict hier = pybind11_libyt.attr("hierarchy");
    int num_fields = pybind11_libyt.attr("param_yt")["num_fields"].cast<int>();

    // allocate array
    grid_left_edge = new double[num_grids * 3];
    grid_right_edge = new double[num_grids * 3];
    grid_dimensions = new int[num_grids * 3];
    grid_levels = new int[num_grids];
    grid_parent_id = new long[num_grids];
    proc_num = new int[num_grids];

    // bind to hierarchy
    hier["grid_left_edge"] = pybind11::memoryview::from_buffer(
            grid_left_edge,                       // buffer pointer
            {num_grids, 3},                       // shape (rows, cols)
            {sizeof(double) * 3, sizeof(double)}  // strides in bytes
    );
    hier["grid_right_edge"] = pybind11::memoryview::from_buffer(
            grid_right_edge,
            {num_grids, 3},
            {sizeof(double) * 3, sizeof(double)}
    );
    hier["grid_dimensions"] = pybind11::memoryview::from_buffer(
            grid_dimensions,
            {num_grids, 3},
            {sizeof(int) * 3, sizeof(int)}
    );
    hier["grid_levels"] = pybind11::memoryview::from_buffer(
            grid_levels,
            {num_grids, 1},
            {sizeof(int), sizeof(int)}
    );
    hier["grid_parent_id"] = pybind11::memoryview::from_buffer(
            grid_parent_id,
            {num_grids, 1},
            {sizeof(long), sizeof(long)}
    );
    hier["proc_num"] = pybind11::memoryview::from_buffer(
            proc_num,
            {num_grids, 1},
            {sizeof(int), sizeof(int)}
    );

//    pybind11::exec("print(libyt.hierarchy)");
//    pybind11::exec("import numpy as np; print(np.array(libyt.hierarchy['grid_left_edge'], copy=False).flags)");
//    pybind11::exec("import numpy as np; print(type(np.array(libyt.hierarchy['grid_left_edge'], copy=False)))");
//    pybind11::exec("print(np.array(libyt.hierarchy['grid_left_edge']).shape)");

    // allocate grids_local to mimic libyt, which is bad
    global_grids_local = new struct yt_grid[num_grids];
    for (int g = 0; g < num_grids; g++) {
        global_grids_local[g].field_data = new struct yt_data[num_fields];
    }

    *grids_local = global_grids_local;

    return 0;
}

int PyBind11Commit() {
#ifdef SUPPORT_TIMER
    SET_TIMER(__PRETTY_FUNCTION__, &timer_control);
#endif
    std::cout << "[PyBind11] Commit" << std::endl;

    auto pybind11_libyt = pybind11::module_::import("libyt");

    // bind grids_local to hierarchy
    // TODO: how does libyt do it, we should also mimic it here.
    //       I think it initialize the local grids and then free it after commit, and this is bad
    long num_grids = pybind11_libyt.attr("param_yt")["num_grids"].cast<long>();
    int num_fields = pybind11_libyt.attr("param_yt")["num_fields"].cast<int>();
    pybind11::dict grid_data = pybind11_libyt.attr("grid_data");

    for (long g = 0; g < num_grids; g++) {
        // set hierarchy grid by grid
        for (int d = 0; d < 3; d++) {
            grid_dimensions[g * 3 + d] = global_grids_local[g].grid_dimensions[d];
            grid_left_edge[g * 3 + d] = global_grids_local[g].left_edge[d];
            grid_right_edge[g * 3 + d] = global_grids_local[g].right_edge[d];
        }
        grid_parent_id[g] = global_grids_local[g].parent_id;
        grid_levels[g] = global_grids_local[g].level;
        proc_num[g] = global_grids_local[g].proc_num;

        // bind buffer field by field
        for (int v = 0; v < num_fields; v++) {
            if (global_grids_local[g].field_data[v].data_ptr != nullptr) {

                pybind11::dict field_data;

                if (!grid_data.contains(pybind11::int_(g))) {
                    field_data = pybind11::dict();
                    grid_data[pybind11::int_(g)] = field_data;
                } else {
                    field_data = grid_data[pybind11::int_(g)];
                }

                // TODO: should also work on checking contiguous_in_x and wrapping data mechanisms
                field_data[global_field_list[v].field_name] = pybind11::memoryview::from_buffer(
                        (double*) global_grids_local[g].field_data[v].data_ptr,
                        {grid_dimensions[g * 3 + 0], grid_dimensions[g * 3 + 1], grid_dimensions[g * 3 + 2]},
                        {sizeof(double), sizeof(double) * grid_dimensions[g * 3 + 0],
                         sizeof(double) * grid_dimensions[g * 3 + 0] * grid_dimensions[g * 3 + 1]},
                         true // read-only
                );
            }
        }
    }

    // delete global_grids_local
    for (long g = 0; g < num_grids; g++) {
        delete[] global_grids_local[g].field_data;
    }
    delete[] global_grids_local;

//    pybind11::exec("print(libyt.grid_data.keys())");
//    pybind11::exec("print(dir(libyt.grid_data[8783]['CCTwos']))");
//    pybind11::exec("print(libyt.grid_data[8783]['CCTwos'].readonly)");
//    pybind11::exec("print(libyt.grid_data[8783]['CCTwos'][0,0,0])");
//    pybind11::exec("print(np.array(libyt.grid_data[8783]['CCTwos'], copy=False).flags)");

    return 0;
}

int PyBind11Run(const char *inline_script, const char *function) {
#ifdef SUPPORT_TIMER
    SET_TIMER(__PRETTY_FUNCTION__, &timer_control);
#endif
    std::cout << "[PyBind11] Running " << function << std::endl;

    pybind11::exec(std::string(inline_script) + "." + std::string(function) + "()");

    return 0;
}

int PyBind11Free() {
#ifdef SUPPORT_TIMER
    SET_TIMER(__PRETTY_FUNCTION__, &timer_control);
#endif
    std::cout << "[PyBind11] Free" << std::endl;

    // delete Python objects
    auto pybind11_libyt = pybind11::module_::import("libyt");
    pybind11::dict param_yt = pybind11_libyt.attr("param_yt");
    pybind11::dict param_user = pybind11_libyt.attr("param_user");
    pybind11::dict hierarchy = pybind11_libyt.attr("hierarchy");
    pybind11::dict grid_data = pybind11_libyt.attr("grid_data");

    param_yt.clear();
    param_user.clear();
    hierarchy.clear();
    grid_data.clear();

    // delete arrays allocated by the library
    delete[] grid_left_edge;
    delete[] grid_right_edge;
    delete[] grid_dimensions;
    delete[] grid_parent_id;
    delete[] grid_levels;
    delete[] proc_num;

    return 0;
}

PYBIND11_EMBEDDED_MODULE(pybind11_libyt, m) {
    using namespace pybind11::literals; // to bring in the `_a` literal
    m.attr("demo") = pybind11::dict("spam"_a = pybind11::none());
    m.attr("param_yt") = pybind11::dict();
    m.attr("param_user") = pybind11::dict();
    m.attr("libyt_info") = pybind11::dict("version"_a = "0.0.1");

    m.def("add", [](int i, int j) {
        return i + j;
    });
    m.def("func", []() {
    });
}

int PyBind11CallTestScript() {
    /*
     * Call in example.cpp only, not in gamer mock
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

    // Bind to array with determined shape and size
    uint8_t buffer[] = {
            0, 1, 2, 3,
            4, 5, 6, 7
    };
    demo["array"] = pybind11::memoryview::from_buffer(
            buffer,                                    // buffer pointer
            {2, 4},                                  // shape (rows, cols)
            {sizeof(uint8_t) * 4, sizeof(uint8_t)}   // strides in bytes
    );

    pybind11::exec("import numpy as np; print(np.array(pybind11_libyt.demo['array'], copy=False))");

    int *array = new int[10];

    for (int i = 0; i < 10; i++) {
        array[i] = i;
    }

//    demo["memoryview"] = pybind11::memoryview::from_memory(array, sizeof(uint32_t) * 10); // doesn't work
    demo["memoryview"] = pybind11::memoryview::from_buffer(
            array,                                  // buffer pointer
            {10},                                   // shape
            {sizeof(int)}                           // strides in bytes
    );

    pybind11::exec("import numpy as np; print('python =', np.array(pybind11_libyt.demo['memoryview']))");

    for (int i = 0; i < 10; i++) {
        array[i] = i * 100;
    }

    pybind11::exec("import numpy as np; print('python =', np.array(pybind11_libyt.demo['memoryview']))");
    pybind11::exec("import numpy as np; print(np.array(pybind11_libyt.demo['memoryview'], copy=False).flags)");

    pybind11::exec("pybind11_libyt.demo['memoryview'][0] = -1000");
    pybind11::exec("import numpy as np; print('python =', np.array(pybind11_libyt.demo['memoryview']))");
    std::cout << "cpp = ";
    for (int i = 0; i < 10; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    delete[] array;
    pybind11::exec("print('---------------------')");



    pybind11::exec("print('---------------------')");
    pybind11::object result = pybind11_libyt.attr("add")(1, 2);
    std::cout << "call pybind11_libyt.add(1,2) = " << result.cast<int>() << std::endl;

    return 0;
}

int PyBind11CallNumPyTestScript() {

    auto pybind11_libyt = pybind11::module_::import("pybind11_libyt");
    pybind11::dict demo = pybind11_libyt.attr("demo");
    pybind11::exec("import pybind11_libyt");


//    // bind to array with dynamic size
//    double *double_array = new double [100000];
//    for (int i = 0; i < 100000; i++) {
//        double_array[i] = i + 0.1;
//    }
//
//    // this won't free the memory at the very end, even though the key-value pair is deleted.
//    auto numpy_array_bind = pybind11::array_t<double>({100000, 1}, {sizeof(double), sizeof(double)}, double_array);
//    auto numpy_array_bind_view = numpy_array_bind.mutable_data();
//    demo["numpy_array_bind"] = numpy_array_bind;
//
//    PyRun_SimpleString("print(dir())");

    // I'm not sure if this makes a copy because ...
//    pybind11::exec("print(pybind11_libyt.demo['numpy_array_bind'][0, 0])"); // this prints 0.1
//    double_array[0] = 1000; // this won't work
//    numpy_array_bind_view[0] = 1000; // this works
//
//    pybind11::exec("print(pybind11_libyt.demo['numpy_array_bind'][0, 0])"); // this still prints 0.1 even though it is changed.
//
//    std::cout << "[FLAG] double_array ptr = " << static_cast<void*>(double_array) << std::endl;
//    std::cout << "[FLAG] get from pybind11 = " << static_cast<void*>(numpy_array_bind.mutable_data()) << std::endl;
//
//    pybind11::exec("print(pybind11_libyt.demo['numpy_array_bind'].shape)");
//    pybind11::exec("print(pybind11_libyt.demo['numpy_array_bind'].flags)");
//    pybind11::exec("print(type(pybind11_libyt.demo['numpy_array_bind']))");
//    pybind11::exec("del pybind11_libyt.demo['numpy_array_bind']"); // it won't free double_array

    pybind11::exec("print('---------------------')");

    // ref: https://stackoverflow.com/questions/44659924/returning-numpy-arrays-via-pybind11?rq=4
    // using the second new method
    auto numpy_array = pybind11::array_t<double>({100000, 1}, {sizeof(double), sizeof(double)});
    demo["numpy_array"] = numpy_array;
    auto numpy_array_data = numpy_array.mutable_data();
    numpy_array_data[0] = -2000;

    pybind11::exec("print(pybind11_libyt.demo['numpy_array'][0, 0])");
    pybind11::exec("print(pybind11_libyt.demo['numpy_array'].shape)");
    pybind11::exec("print(pybind11_libyt.demo['numpy_array'].flags)");
    pybind11::exec("print(type(pybind11_libyt.demo['numpy_array']))");


    return 0;
}

int PyBind11CallNumPyDel(const char *key) {

    pybind11::exec("del pybind11_libyt.demo['numpy_array']"); // this frees array allocated by pybind11

    return 0;
}

#endif