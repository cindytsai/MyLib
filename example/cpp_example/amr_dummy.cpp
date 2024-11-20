#include <iostream>
#include <cstdio>
#include <vector>
#include <unistd.h>
#include <cstdlib>
#include "library.h"

#ifdef USE_MPI
#include <mpi.h>
#endif

#ifdef USE_VALGRIND
#include <valgrind/valgrind.h>
#endif

void DerivedFunc(const int len, const long *list_gid, const char *field_name, struct yt_data *data_array){
    for(int l=0; l<len; l++){
        for(int idx=0; idx<(8 * 8 * 8); idx++){ ((float*)data_array[l].data_ptr)[idx] = 1.0; }
    }
}

int main (int argc, char *argv[]){

    /* initialize testing environment. */
    int myrank = 0;
    int nrank = 1;
#ifdef USE_MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &nrank );
#endif

    /* Parameters for testing */
    long iter = 3;
    int  grid_size = 8;
    int  num_grids = 2000000; // cannot alter arbitrary.
    int  num_grids_local = num_grids / nrank;
    char valgrind_cmd[1000];

    /* Generate data set for testing */
    if ( Initialize( argc, argv ) != LIBRARY_SUCCESS ) {
        printf("Initialize failed!\n");
    }

    if ( Import("inline_script") != LIBRARY_SUCCESS ) {
        printf("Import failed!\n");
    }

    struct yt_param_yt param_yt;
    param_yt.frontend                = "gamer";
    param_yt.fig_basename            = "FigName";
    param_yt.length_unit             = 3.0857e21;
    param_yt.mass_unit               = 1.9885e33;
    param_yt.time_unit               = 3.1557e13;
    param_yt.velocity_unit           = param_yt.length_unit / param_yt.time_unit;

    param_yt.current_time            = 0.0;
    param_yt.dimensionality          = 3;
    param_yt.refine_by               = 2;
    param_yt.num_grids               = num_grids;
    param_yt.domain_dimensions[0]    = 100 * grid_size;    // should be based on num_grids
    param_yt.domain_dimensions[1]    = 100 * grid_size;
    param_yt.domain_dimensions[2]    = 200 * grid_size;

    double space[3] = { 100.0 / param_yt.domain_dimensions[0] ,
                        100.0 / param_yt.domain_dimensions[1] ,
                        100.0 / param_yt.domain_dimensions[2] };

    for (int d=0; d<3; d++)
    {
        param_yt.domain_left_edge [d] = 0.0;
        param_yt.domain_right_edge[d] = 100.0;
        param_yt.periodicity      [d] = 0;
    }

    param_yt.cosmological_simulation = 0;
    param_yt.current_redshift        = 0.5;
    param_yt.omega_lambda            = 0.7;
    param_yt.omega_matter            = 0.3;
    param_yt.hubble_constant         = 0.7;
    param_yt.num_grids_local         = num_grids_local;

    // for fields and particles
    param_yt.num_fields              = 2;         // cell-centered and derived
    struct yt_field *field_list = new struct yt_field[param_yt.num_fields];

    // generating field (twos field in cell-centered) and particle data (position x/y/z)
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
        PyBind11_SetUserParameterDouble("srhd", 0);

        /* libyt API yt_get_FieldsPtr */
        // set derived field
        field_list[0].field_name = "DerivedOnes";
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

        struct yt_grid *grids_local;
        PyBind11_InitHier(num_grids, &grids_local );

        for(long lid=0; lid<num_grids_local; lid++){
            // general info
            long gid = lid + myrank * num_grids_local;
            int grid_idx[3];
            grid_idx[2] = gid / (param_yt.domain_dimensions[0] * param_yt.domain_dimensions[1]);
            grid_idx[1] = (gid - (grid_idx[2] * param_yt.domain_dimensions[0] * param_yt.domain_dimensions[1])) / param_yt.domain_dimensions[0];
            grid_idx[0] = gid - (grid_idx[2] * param_yt.domain_dimensions[0] * param_yt.domain_dimensions[1]) - (grid_idx[1] * param_yt.domain_dimensions[0]);
            for(int d=0; d<3; d++){
                grids_local[lid].left_edge[d]  = space[d] * (double)grid_idx[d];
                grids_local[lid].right_edge[d] = grids_local[lid].left_edge[d] + space[d];
                grids_local[lid].grid_dimensions[d] = grid_size;
            }
            grids_local[lid].id = gid;
            grids_local[lid].parent_id = -1;
            grids_local[lid].level = 0;

            // append cell-centered field data
            grids_local[lid].field_data[0].data_ptr = field_data[lid];
            grids_local[lid].field_data[1].data_ptr = field_data[lid];
        }

        /* libyt API commit, call Python function, and free*/
        if (PyBind11_Commit() != LIBRARY_SUCCESS) {
            std::cout << "[error] commit failed" << std::endl;
        }

//        if (PyBind11_Run("inline_script", "func") != LIBRARY_SUCCESS) {
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

    // free resources
    delete [] field_list;
    for (int i = 0; i < num_grids_local; i++) {
        delete [] field_data[i];
    }

    /* libyt API yt_finalize */
    if ( Finalize() != LIBRARY_SUCCESS ) {
        printf("yt_finalize failed!\n");
    }

#ifdef USE_MPI
    MPI_Finalize();
#endif

    return 0;
}
