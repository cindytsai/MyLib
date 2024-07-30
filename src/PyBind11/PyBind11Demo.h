#ifndef MYLIB_PYBINDDEMO_H
#define MYLIB_PYBINDDEMO_H

#ifdef USE_PYBIND11
int PyBind11Initialize();
int PyBind11Finalize();
int CallPyBind11Demo();
#endif

#endif  // MYLIB_PYBINDDEMO_H
