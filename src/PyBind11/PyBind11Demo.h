#ifndef MYLIB_PYBINDDEMO_H
#define MYLIB_PYBINDDEMO_H

#ifdef USE_PYBIND11
int PyBind11Initialize(const char* inline_script);
int PyBind11Finalize();
int PyBind11CallTestScript();
int PyBind11SetParameters(struct yt_param_yt* yt_param_ptr);
int PyBind11SetUserParameterInt(const char* key, int value);
int PyBind11SetFields(struct yt_field* yt_field_ptr, int len);
int PyBind11Run(const char* inline_script, const char* function);
#endif

#endif  // MYLIB_PYBINDDEMO_H
