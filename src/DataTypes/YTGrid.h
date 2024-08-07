#ifndef MYLIB_YTGRID_H
#define MYLIB_YTGRID_H

#include <cfloat>
#include <climits>

#include "YTData.h"

struct yt_grid {
    double left_edge[3];
    double right_edge[3];
    long* par_count_list;
    long id;
    long parent_id;
    int grid_dimensions[3];
    int level;
    int proc_num;
    struct yt_data* field_data;

#ifdef __cplusplus
    //===================================================================================
    // Method      :  yt_grid
    // Description :  Constructor of the structure "yt_grid"
    //
    // Note        :  Initialize all data members
    //
    // Parameter   :  None
    //===================================================================================
    yt_grid() {
        for (int d = 0; d < 3; d++) {
            left_edge[d] = DBL_MIN;
            right_edge[d] = DBL_MIN;
        }
        for (int d = 0; d < 3; d++) {
            grid_dimensions[d] = INT_MIN;
        }
        par_count_list = nullptr;
        id = LONG_MIN;
        parent_id = LONG_MIN;
        level = INT_MIN;
        proc_num = INT_MIN;
        field_data = nullptr;
    }
#endif  // #ifdef __cplusplus

} yt_grid;

#endif  // MYLIB_YTGRID_H
