/*
Using pybind11 to build a dummy libyt in gamer mock simulation.
Consider only cell-centered field and ignore particle data and derived data.
*/

#include "library.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#ifdef USE_VALGRIND
#include <valgrind/valgrind.h>
#endif

#define GRID_SIZE 16

void DerivedFunc(const int grid_list_len, const long* grid_list, const char* field_name, struct yt_data* data_array) {
    char filename [1000];
    for (int g = 0; g < grid_list_len; g++) {
        std::ifstream grid_data;
        sprintf(filename, "/home/cindytsai/Documents/MyNotes/DevLog-libyt/Issues/memory-leakage/Data/DensGrids/Grid_%ld_Dens.txt", grid_list[g]);
        grid_data.open(filename);
        if (!grid_data.is_open()) {
            std::cout << "Cannot open file " << filename << std::endl;
            exit(1);
        }
        for (int k = 0; k < data_array[g].data_dimensions[0]; k++) {
            for (int j = 0; j < data_array[g].data_dimensions[1]; j++) {
                for (int i = 0; i < data_array[g].data_dimensions[2]; i++) {
                    long idx = k * data_array[g].data_dimensions[1] * data_array[g].data_dimensions[2] + j * data_array[g].data_dimensions[2] + i;
                    grid_data >> ((double*)data_array[g].data_ptr)[idx];
                }
            }
        }
        grid_data.close();
    }
}

int main (int argc, char *argv[]){

    /* Cpp version */
    std::cout << "C++ version: " << __cplusplus << std::endl;
    PrintCXXVersion();

    /* Parameters for testing */
    int iter = 100;
    int  grid_size = GRID_SIZE;
    int  num_grids = 8784; // cannot alter arbitrary.
    int  num_grids_local, start_id, end_id;
    std::string inline_script = std::string("inline_script");

#ifdef USE_VALGRIND
    char valgrind_cmd[1000];
#endif

    start_id = 0;
    end_id = num_grids;
    num_grids_local = num_grids;

    // read in hierarchy in this part
    int *id, *parent_id, *level;
    double *left_edge1, *left_edge2, *left_edge3;
    double *right_edge1, *right_edge2, *right_edge3;
    int *dim1, *dim2, *dim3;

    id = new int [num_grids_local];
    parent_id = new int [num_grids_local];
    level = new int [num_grids_local];
    left_edge1 = new double [num_grids_local];
    left_edge2 = new double [num_grids_local];
    left_edge3 = new double [num_grids_local];
    right_edge1 = new double [num_grids_local];
    right_edge2 = new double [num_grids_local];
    right_edge3 = new double [num_grids_local];
    dim1 = new int [num_grids_local];
    dim2 = new int [num_grids_local];
    dim3 = new int [num_grids_local];

    int temp_int;
    double temp_double;

    std::ifstream hier;
    hier.open("hier.txt");
    for (int i = 0; i < num_grids; i++) {
        if (start_id <= i && i < end_id) {
            hier >> id[i - start_id];
            hier >> parent_id[i - start_id];
            hier >> level[i - start_id];
            hier >> left_edge1[i - start_id] >> left_edge2[i - start_id] >> left_edge3[i - start_id];
            hier >> right_edge1[i - start_id] >> right_edge2[i - start_id] >> right_edge3[i - start_id];
            hier >> dim1[i - start_id] >> dim2[i - start_id] >> dim3[i - start_id];
        }
        else {
            hier >> temp_int;
            hier >> temp_int;
            hier >> temp_int;
            hier >> temp_double >> temp_double >> temp_double;
            hier >> temp_double >> temp_double >> temp_double;
            hier >> temp_int >> temp_int >> temp_int;
        }
    }
    hier.close();

    /* Generate data set for testing */
    if (Initialize(argc, argv) != LIBRARY_SUCCESS) {
        printf("yt_initialize failed!\n");
    }

    if (Import(inline_script.c_str()) != LIBRARY_SUCCESS) {
        printf("yt_import failed!\n");
    }

    struct yt_param_yt param_yt;
    param_yt.frontend                = "gamer";
    param_yt.fig_basename            = "FigName";
    param_yt.length_unit             = 4.58351746e24;
    param_yt.mass_unit               = 2.57725326e44;
    param_yt.time_unit               = 4.58351746e17;
    param_yt.velocity_unit           = param_yt.length_unit / param_yt.time_unit;

    param_yt.current_time            = 0.0;
    param_yt.dimensionality          = 3;
    param_yt.refine_by               = 2;
    param_yt.num_grids               = num_grids;
    param_yt.domain_dimensions[0]    = 96;
    param_yt.domain_dimensions[1]    = 96;
    param_yt.domain_dimensions[2]    = 96;

    for (int d=0; d<3; d++)
    {
        param_yt.domain_left_edge [d] = 0.0;
        param_yt.domain_right_edge[d] = 0.28794389;
        param_yt.periodicity      [d] = 1;
    }

    param_yt.cosmological_simulation = 0;
    param_yt.current_redshift        = 0.0;
    param_yt.omega_lambda            = 0.0;
    param_yt.omega_matter            = 0.0;
    param_yt.hubble_constant         = 0.0;
    param_yt.num_grids_local         = num_grids_local;

    // for fields and particles
    param_yt.num_fields              = 2;         // cell-centered and derived

    struct yt_field *field_list = new struct yt_field[param_yt.num_fields];

    // for testing data wrapping in libyt
    std::vector<double*> field_data;

     for (int i = 0; i < num_grids_local; i++) {
         double *temp = new double [grid_size * grid_size * grid_size];
         for (int j = 0; j < grid_size * grid_size * grid_size; j++) {
             temp[j] = 2.0;
         }
         field_data.push_back(temp);
     }

    // iteration starts
    for(int t=0; t<iter; t++) {

        /* libyt API yt_set_Parameters */
        PyBind11_SetParameters( &param_yt );

        /* libyt API yt_set_UserParameter */
        PyBind11_SetUserParameterInt("mhd", 0);
        PyBind11_SetUserParameterInt("srhd", 0);
        PyBind11_SetUserParameterInt("opt_unit", 0);
        PyBind11_SetUserParameterDouble("mu", 0.6);

        /* libyt API yt_set_Fields */
        // set derived field
        field_list[0].field_name = "Dens";
        field_list[0].field_type = "derived_func";
        field_list[0].contiguous_in_x = true;
        const char *field_name_alias[] = {"Name Alias 1", "Name Alias 2", "Name Alias 3"};
        field_list[0].field_name_alias = field_name_alias;
        field_list[0].num_field_name_alias = 3;
        field_list[0].derived_func = DerivedFunc;

        // set cell-centered field
        field_list[1].field_name = "CCTwos";
        field_list[1].field_type = "cell-centered";
        field_list[1].contiguous_in_x = true;
        PyBind11_SetFields(field_list, param_yt.num_fields);

        // TODO: how does libyt do this.
        //       I think it initialize the local grids and then free it after commit, and this is bad
        struct yt_grid *grids_local;
        PyBind11_InitHier(num_grids, &grids_local);

        // parent_id, level, left/right edge, grid_dimensions
        for(long lid=0; lid<num_grids_local; lid++){
            // general info
            grids_local[lid].left_edge[0]  = left_edge1[lid];
            grids_local[lid].left_edge[1]  = left_edge2[lid];
            grids_local[lid].left_edge[2]  = left_edge3[lid];

            grids_local[lid].right_edge[0]  = right_edge1[lid];
            grids_local[lid].right_edge[1]  = right_edge2[lid];
            grids_local[lid].right_edge[2]  = right_edge3[lid];

            grids_local[lid].grid_dimensions[0]  = dim1[lid];
            grids_local[lid].grid_dimensions[1]  = dim2[lid];
            grids_local[lid].grid_dimensions[2]  = dim3[lid];

            grids_local[lid].id = id[lid];
            grids_local[lid].parent_id = parent_id[lid];
            grids_local[lid].level = level[lid];

            // append cell-centered field data
             grids_local[lid].field_data[1].data_ptr = field_data[lid];
        }

        /* libyt API commit, call Python function, and free*/
        if (PyBind11_Commit() != LIBRARY_SUCCESS) {
            std::cout << "[error] commit failed" << std::endl;
        }

//        if (PyBind11_Run(inline_script.c_str(), "test_function") != LIBRARY_SUCCESS) {
//            std::cout << "[error] run failed" << std::endl;
//        }

#ifdef USE_VALGRIND
        snprintf(valgrind_cmd, 1000, "detailed_snapshot BeforeFree%d\0", t);
        VALGRIND_MONITOR_COMMAND(valgrind_cmd);
#endif

        if (PyBind11_Free() != LIBRARY_SUCCESS) {
            std::cout << "[error] free failed" << std::endl;
        }

#ifdef USE_VALGRIND
        snprintf(valgrind_cmd, 1000, "detailed_snapshot AfterFree%d\0", t);
        VALGRIND_MONITOR_COMMAND(valgrind_cmd);
#endif

        std::cout << "[FLAG] step = " << t << std::endl;
    }

    /* free dummy data */
    delete [] id;
    delete [] parent_id;
    delete [] level;
    delete [] left_edge1;
    delete [] left_edge2;
    delete [] left_edge3;
    delete [] right_edge1;
    delete [] right_edge2;
    delete [] right_edge3;
    delete [] dim1;
    delete [] dim2;
    delete [] dim3;
    delete [] field_list;

    for (int i = 0; i < num_grids_local; i++) {
        delete [] field_data[i];
    }

    /* libyt API yt_finalize */
    if ( Finalize() != LIBRARY_SUCCESS ) {
        printf("yt_finalize failed!\n");
    }

    return 0;
}
