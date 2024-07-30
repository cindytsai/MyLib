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
    return LIBRARY_SUCCESS;
}

int Finalize() {
#ifdef USE_MPIE
    MPICore::Finalize();
#endif

#ifdef USE_PYTHON
    PythonCore::Finalize();
#endif
    return LIBRARY_SUCCESS;
}

int PrintCXXVersion() {
    Logger logger(LOG_DEBUG);
    logger.Info("C++ version: %lld\n", __cplusplus);
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
    CallPyBind11Demo();
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
