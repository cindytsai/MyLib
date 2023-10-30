#include "library.h"
#include <mpi.h>

int main(int argc, char* argv[]) {
    Initialize(argc, argv);

    CheckPython();
    People people;
    people.age = 100;
    people.name = "Cindytsai";

    Finalize();

    return 0;
}

