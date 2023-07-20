#include "library.h"

#include <mpi.h>

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);

    hello();
    CheckPython();

    MPI_Finalize();

    return 0;
}

