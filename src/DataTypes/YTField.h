#ifndef MYLIB_YTFIELD_H
#define MYLIB_YTFIELD_H

#include "YTData.h"

struct yt_field {
    const char* field_name;
    const char* field_type;
    bool contiguous_in_x;
    short field_ghost_cell[6];
    const char* field_unit;
    int num_field_name_alias;
    const char** field_name_alias;
    const char* field_display_name;
    void (*derived_func)(const int, const long*, const char*, struct yt_data*);

#ifdef __cplusplus
    //=======================================================================================================
    // Method      : yt_field
    // Description : Constructor of the structure "yt_field"
    //
    // Note        : 1. Initialize field_type as "cell-centered"
    //               2. Initialize field_unit as "". If it is not set by user, then yt will use the particle
    //                  unit set at yt frontend. If there still isn't one, then it will use "".
    //
    // Parameter   : None
    // ======================================================================================================
    yt_field() {
        field_name = nullptr;
        field_type = "cell-centered";
        contiguous_in_x = true;
        for (int d = 0; d < 6; d++) {
            field_ghost_cell[d] = 0;
        }
        field_unit = "";
        num_field_name_alias = 0;
        field_name_alias = nullptr;
        field_display_name = nullptr;
        derived_func = nullptr;
    }
#endif  // #ifdef __cplusplus

} yt_field;

#endif  // MYLIB_YTFIELD_H
