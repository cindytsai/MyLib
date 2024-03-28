#include "library.h"
#ifndef SERIAL_MODE
#include <mpi.h>
#endif

int main(int argc, char* argv[]) {
    Initialize(argc, argv);

    PrintCXXVersion();

    CheckPython();
    People people;
    people.age = 100;
    people.name = "Cindytsai";

    CheckDependency();

    Finalize();

    return 0;
}

