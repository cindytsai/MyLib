#ifdef USE_PYTHON

#define PY_SSIZE_T_CLEAN

#include "PythonCore.h"

#include <Python.h>

#include <iostream>

#include "../Macro/LibraryDefinition.h"

wchar_t *PythonCore::s_PythonProgram = NULL;

int PythonCore::Initialize() {
    s_PythonProgram = Py_DecodeLocale("PythonCore", NULL);
    if (s_PythonProgram == NULL) {
        std::cout << "[PythonCore] cannot decode" << std::endl;
        return LIBRARY_FAIL;
    }
    Py_SetProgramName(s_PythonProgram);
    Py_Initialize();
    return LIBRARY_SUCCESS;
}

int PythonCore::Finalize() {
    if (Py_FinalizeEx() < 0) {
        return LIBRARY_FAIL;
    }
    PyMem_RawFree(s_PythonProgram);
    return LIBRARY_SUCCESS;
}

int PythonCore::CheckPython() {
    PyRun_SimpleString("print('[python] hello world')\n");
    std::cout << "[python] python version" << PY_MAJOR_VERSION << "." << PY_MINOR_VERSION << "." << PY_MICRO_VERSION
              << std::endl;
#ifdef USE_BOO
    std::cout << "[python] USE_BOO = USE_BOO" << std::endl;
#endif
    return LIBRARY_SUCCESS;
}

#endif
