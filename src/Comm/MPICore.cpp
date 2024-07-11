#ifdef USE_MPI

#include "../Macro/LibraryDefinition.h"
#include "MPICore.h"
#include <mpi.h>

int MPICore::m_Process;
int MPICore::m_Size;

int MPICore::Initialize(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &m_Size);
    MPI_Comm_rank(MPI_COMM_WORLD, &m_Process);
    return LIBRARY_SUCCESS;
}

int MPICore::Finalize() {
    MPI_Finalize();
    return LIBRARY_SUCCESS;
}

#endif
