#ifndef MYLIB_LIBRARY_H
#define MYLIB_LIBRARY_H

#include "../DataTypes/People.h"

#ifdef __cplusplus
extern "C" {
#endif
    int Initialize(int argc, char *argv[]);
    int Finalize();

    int PrintCXXVersion();
    int UseDataType(const struct People *people);

    int CheckPython();

#ifdef __cplusplus
};
#endif

#endif //MYLIB_LIBRARY_H