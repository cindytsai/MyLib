#include <iostream>
#include "./Comm/MPICore.h"
#include "./Python/PythonCore.h"
#include "./Utilities/Logger.h"
#include "./Macro/LibraryDefinition.h"
#include "library.h"
#include <nlohmann/json.hpp>

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
#ifndef SERIAL_MODE
    MPICore::Initialize(argc, argv);
#endif
    PythonCore::Initialize();
    return LIBRARY_SUCCESS;
}

int Finalize() {
#ifndef SERIAL_MODE
    MPICore::Finalize();
#endif
    PythonCore::Finalize();
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

int CheckDependency() {
#ifdef NL_JSON
    std::cout << "[json] using dependency" << std::endl;
    nlohmann::json j = nlohmann::json::array({1, 2, 3, 4});
    std::cout << "j = " << j << std::endl;
#else
    std::cout << "[] no dependency" << std::endl;
#endif
    return 0;
}

int CheckPython() {
    PythonCore python_core;
    python_core.CheckPython();
    return LIBRARY_SUCCESS;
}