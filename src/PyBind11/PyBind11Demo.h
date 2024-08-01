#ifndef MYLIB_PYBINDDEMO_H
#define MYLIB_PYBINDDEMO_H

#ifdef USE_PYBIND11
int PyBind11Initialize(const char* inline_script);
int PyBind11Finalize();
int PyBind11CallTestScript();
int PyBind11SetParameters(struct yt_param_yt* yt_param_ptr);
#endif

#endif  // MYLIB_PYBINDDEMO_H
