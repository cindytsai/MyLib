#include "library.h"

#include <mpi.h>

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);

    hello();

    MPI_Finalize();

    return 0;
}

