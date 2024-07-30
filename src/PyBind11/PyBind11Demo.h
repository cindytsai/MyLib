#ifndef MYLIB_PYBINDDEMO_H
#define MYLIB_PYBINDDEMO_H

#ifdef USE_PYBIND11
int PyBind11Initialize();
int PyBind11Finalize();
int PyBind11CallTestScript();
#endif

#endif  // MYLIB_PYBINDDEMO_H
