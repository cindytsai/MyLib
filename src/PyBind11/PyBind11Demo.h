#ifndef MYLIB_PYBINDDEMO_H
#define MYLIB_PYBINDDEMO_H

#include "DataTypes/YTGrid.h"

#ifdef USE_PYBIND11

int PyBind11Initialize();
int PyBind11Import(const char* inline_script);
int PyBind11Finalize();
int PyBind11CallTestScript();
int PyBind11CallNumPyTestScript();
int PyBind11SetParameters(struct yt_param_yt* yt_param_ptr);
int PyBind11SetUserParameterInt(const char* key, int value);
int PyBind11SetUserParameterDouble(const char* key, double value);
int PyBind11SetFields(struct yt_field* yt_field_ptr, int len);
int PyBind11InitHier(int num_grids, struct yt_grid** grids_local);
int PyBind11Commit();
int PyBind11Run(const char* inline_script, const char* function);
#endif  // #ifdef USE_PYBIND11

#ifdef INIT_GLOBAL

struct yt_grid* global_grids_local;

double* grid_left_edge;
double* grid_right_edge;
int* grid_dimensions;
long* grid_parent_id;
int* grid_levels;
int* proc_num;

#endif

#ifdef USE_GLOBAL

extern double* grid_left_edge;
extern double* grid_right_edge;
extern int* grid_dimensions;
extern long* grid_parent_id;
extern int* grid_levels;
extern int* proc_num;

#endif

#endif  // MYLIB_PYBINDDEMO_H
