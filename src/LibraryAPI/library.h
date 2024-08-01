#ifndef MYLIB_LIBRARY_H
#define MYLIB_LIBRARY_H

#include "DataTypes/People.h"
#include "DataTypes/YTParameters.h"
#include "Macro/LibraryDefinition.h"

#ifdef __cplusplus
extern "C" {
#endif
int Initialize(int argc, char* argv[], const char* inline_script);
int Finalize();

int PyBind11Demo();
int PyBind11_SetParameters(struct yt_param_yt* yt_param_ptr);
int PyBind11_SetUserParameterInt(const char* key, int value);

int TempFunc();
int PrintCXXVersion();
int UseDataType(const struct People* people);
int CheckDependencies();
int CheckPython();

#ifdef __cplusplus
};
#endif

#endif  // MYLIB_LIBRARY_H
