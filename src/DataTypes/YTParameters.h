#ifndef MYLIB_YTPARAMETERS_H
#define MYLIB_YTPARAMETERS_H

#include <cfloat>
#include <climits>

struct yt_param_yt {
    const char* frontend;
    const char* fig_basename;
    double domain_left_edge[3];
    double domain_right_edge[3];
    double current_time;
    double current_redshift;
    double omega_lambda;
    double omega_matter;
    double hubble_constant;
    double length_unit;
    double mass_unit;
    double time_unit;
    double velocity_unit;
    double magnetic_unit;
    int periodicity[3];
    int cosmological_simulation;
    int dimensionality;
    int domain_dimensions[3];
    int refine_by;
    int index_offset;
    long num_grids;
    int num_fields;
    int num_par_types;
    int num_grids_local;

#ifdef __cplusplus
    //===================================================================================
    // Method      :  yt_param_yt
    // Description :  Constructor of the structure "yt_param_yt"
    //
    // Note        :  Initialize all data members
    //
    // Parameter   :  None
    //===================================================================================
    yt_param_yt() {
        frontend = nullptr;
        fig_basename = nullptr;
        for (int d = 0; d < 3; d++) {
            domain_left_edge[d] = DBL_MIN;
            domain_right_edge[d] = DBL_MIN;
        }
        current_time = DBL_MIN;
        current_redshift = DBL_MIN;
        omega_lambda = DBL_MIN;
        omega_matter = DBL_MIN;
        hubble_constant = DBL_MIN;
        length_unit = DBL_MIN;
        mass_unit = DBL_MIN;
        time_unit = DBL_MIN;
        velocity_unit = DBL_MIN;
        magnetic_unit = DBL_MIN;

        for (int d = 0; d < 3; d++) {
            periodicity[d] = INT_MIN;
            domain_dimensions[d] = INT_MIN;
        }
        cosmological_simulation = INT_MIN;
        dimensionality = INT_MIN;
        refine_by = INT_MIN;
        index_offset = 0;
        num_grids = LONG_MIN;

        num_fields = 0;
        num_par_types = 0;
        num_grids_local = 0;
    }
#endif  // #ifdef __cplusplus

} yt_param_yt;

#endif  // MYLIB_YTPARAMETERS_H
