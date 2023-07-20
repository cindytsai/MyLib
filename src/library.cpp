#include "library.h"

#include <mpi.h>
#include <iostream>

void hello() {
    int myrank;
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    std::cout << "[" << myrank << "]" << "Hello, World!" << std::endl;
}
