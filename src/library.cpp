#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <mpi.h>
#include <iostream>

#include "library.h"

void hello() {
    int myrank;
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    std::cout << "[" << myrank << "]" << "Hello, World!" << std::endl;
}

void CheckPython() {
    wchar_t *program = Py_DecodeLocale("CheckPython", NULL);
    if (program == NULL)
        std::cout << "[CheckPython] cannot decode argv[0]" << std::endl;

    Py_SetProgramName(program);
    Py_Initialize();
    PyRun_SimpleString("print('[Python] hello world!')\n");

    if (Py_FinalizeEx() < 0)
        exit(120);
    PyMem_RawFree(program);
}

void ImportSubHeader() {
    std::cout << "[ImportSubHeader]" << std::endl;
#ifdef USE_BOO
    std::cout << "[ImportSubHeader] USE_BOO" << std::endl;
#endif
}