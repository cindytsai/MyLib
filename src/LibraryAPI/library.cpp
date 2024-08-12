#include <iostream>
#include "./Comm/MPICore.h"
#include "./Python/PythonCore.h"
#include "./Utilities/Logger.h"
#include "./Macro/LibraryDefinition.h"
#include "./PyBind11/PyBind11Demo.h"
#include "library.h"
#ifdef USE_NLJSON
#include <nlohmann/json.hpp>
#endif

/******************************************************************************
 * \file library.cpp
 * Source file of LibraryAPI.
 *****************************************************************************/

/******************************************************************************
 * \brief A brief description of Initialize
 *
 * \note 1. This is note line 1.
 *       2. This is note line 2.
 *       3. This is note line 3.
 *
 * @param argc[in] Number of input arguments
 * @param argv[in] Input arguments
 * @return The job's state, either success or fail.
 *****************************************************************************/
int Initialize(int argc, char *argv[]) {
#ifdef USE_MPI
    MPICore::Initialize(argc, argv);
#endif
#ifdef USE_PYTHON
    PythonCore::Initialize();
#endif
#ifdef USE_PYBIND11
    PyBind11Initialize();
#endif
    return LIBRARY_SUCCESS;
}

int Import(const char *inline_script) {
#ifdef USE_PYBIND11
    PyBind11Import(inline_script);
    return LIBRARY_SUCCESS;
#else
    std::cout << "[] no pybind11" << std::endl;
    return LIBRARY_FAIL;
#endif
}

int Finalize() {
#ifdef USE_MPIE
    MPICore::Finalize();
#endif
#ifdef USE_PYTHON
    PythonCore::Finalize();
#endif
#ifdef USE_PYBIND11
    PyBind11Finalize();
#endif

    return LIBRARY_SUCCESS;
}

int PyBind11_SetParameters(struct yt_param_yt *yt_param_ptr) {
#ifdef USE_PYBIND11
    PyBind11SetParameters(yt_param_ptr);
    return LIBRARY_SUCCESS;
#else
    std::cout << "[] no pybind11" << std::endl;
    return LIBRARY_FAIL;
#endif
}

int PyBind11_SetUserParameterInt(const char *key, int value) {
#ifdef USE_PYBIND11
    PyBind11SetUserParameterInt(key, value);
    return LIBRARY_SUCCESS;
#else
    std::cout << "[] no pybind11" << std::endl;
    return LIBRARY_FAIL;
#endif
}

int PyBind11_SetUserParameterDouble(const char* key, double value) {
#ifdef USE_PYBIND11
    PyBind11SetUserParameterDouble(key, value);
    return LIBRARY_SUCCESS;
#else
    std::cout << "[] no pybind11" << std::endl;
    return LIBRARY_FAIL;
#endif
}

int PyBind11_SetFields(struct yt_field *yt_field_ptr, int len) {
#ifdef USE_PYBIND11
    PyBind11SetFields(yt_field_ptr, len);
#else
    std::cout << "[] no pybind11" << std::endl;
    return LIBRARY_FAIL;
#endif
}

int PyBind11_InitHier(long num_grids, struct yt_grid **grids_local) {
#ifdef USE_PYBIND11
    PyBind11InitHier(num_grids, grids_local);
    return LIBRARY_SUCCESS;
#else
    std::cout << "[] no pybind11" << std::endl;
    return LIBRARY_FAIL;
#endif
}

int PyBind11_Commit() {
#ifdef USE_PYBIND11
    PyBind11Commit();
    return LIBRARY_SUCCESS;
#else
    std::cout << "[] no pybind11" << std::endl;
    return LIBRARY_FAIL;
#endif
}

int PyBind11_Run(const char *inline_script, const char *function) {
#ifdef USE_PYBIND11
    PyBind11Run(inline_script, function);
    return LIBRARY_SUCCESS;
#else
    std::cout << "[] no pybind11" << std::endl;
    return LIBRARY_FAIL;
#endif
}

int PrintCXXVersion() {
//    Logger logger(LOG_DEBUG);
//    logger.Info("C++ version: %lld\n", __cplusplus);
    std::cout << "[cpp version] " << __cplusplus << std::endl;
    return LIBRARY_SUCCESS;
}

int UseDataType(const struct People *people) {
    Logger logger(LOG_DEBUG);
    logger.Info("People.age = %d\n", people->age);
    logger.Info("People.name = %s\n", people->name);
    return LIBRARY_SUCCESS;
}

int PyBind11Demo() {
#ifdef USE_PYBIND11
    PyBind11CallTestScript();
#endif
    return LIBRARY_SUCCESS;
}

int PyBind11NumPyDemo() {
#ifdef USE_PYBIND11
    PyBind11CallNumPyTestScript();
#endif
    return LIBRARY_SUCCESS;
}

int PyBind11NumPyDel(const char *key) {
#ifdef USE_PYBIND11
    PyBind11CallNumPyDel(key);
#endif
    return LIBRARY_SUCCESS;
}

int CheckDependencies() {
#ifdef USE_NLJSON
    std::cout << "[json] using dependency" << std::endl;
    nlohmann::json j = nlohmann::json::array({1, 2, 3, 4});
    std::cout << "j = " << j << std::endl;
#else
    std::cout << "[] no nljson" << std::endl;
#endif
#ifdef USE_PYTHON
    PythonCore python_core;
    python_core.CheckPython();
#else
    std::cout << "[] no python" << std::endl;
#endif
#ifdef USE_BOO
    std::cout << "[] USE_BOO = USE_BOO" << std::endl;
#else
    std::cout << "[] USE_BOO = (empty)" << std::endl;
#endif
#ifdef USE_PYBIND11
    std::cout << "[pybind11] using dependency" << std::endl;
#else
    std::cout << "[] no pybind11" << std::endl;
#endif
    return 0;
}
