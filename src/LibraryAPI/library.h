#ifndef MYLIB_LIBRARY_H
#define MYLIB_LIBRARY_H

#include "DataTypes/People.h"
#include "DataTypes/YTField.h"
#include "DataTypes/YTGrid.h"
#include "DataTypes/YTParameters.h"
#include "Macro/LibraryDefinition.h"

#ifdef __cplusplus
extern "C" {
#endif
int Initialize(int argc, char* argv[]);
int Import(const char* inline_script);
int Finalize();

int PyBind11Demo();
int PyBind11NumPyDemo();
int PyBind11_SetParameters(struct yt_param_yt* yt_param_ptr);
int PyBind11_SetUserParameterInt(const char* key, int value);
int PyBind11_SetUserParameterDouble(const char* key, double value);
int PyBind11_SetFields(struct yt_field* yt_field_ptr, int len);
int PyBind11_InitHier(long num_grids, struct yt_grid** grids_local);
int PyBind11_Commit();
int PyBind11_Run(const char* inline_script, const char* function);

int TempFunc();
int PrintCXXVersion();
int UseDataType(const struct People* people);
int CheckDependencies();
int CheckPython();

#ifdef __cplusplus
};
#endif

#endif  // MYLIB_LIBRARY_H
