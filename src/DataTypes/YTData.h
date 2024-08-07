#ifndef MYLIB_YTDATA_H
#define MYLIB_YTDATA_H

struct yt_data {
    void* data_ptr;
    int data_dimensions[3];

#ifdef __cplusplus
    //===================================================================================
    // Method      :  yt_data
    // Description :  Constructor of the structure "yt_data"
    //
    // Note        :  Initialize all data members
    //
    // Parameter   :  None
    //===================================================================================
    yt_data() {
        data_ptr = nullptr;
        for (int d = 0; d < 3; d++) {
            data_dimensions[d] = 0;
        }
    }
#endif  // #ifdef __cplusplus
} yt_data;

#endif  // MYLIB_YTDATA_H
