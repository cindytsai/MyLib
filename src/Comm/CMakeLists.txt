if (USE_MPI)
    find_package(MPI REQUIRED)
endif ()

add_library(MPICore SHARED MPICore.cpp)

if (USE_MPI)
    target_compile_definitions(MPICore PUBLIC USE_MPI)
    target_include_directories(MPICore PUBLIC ${MPI_INCLUDE_PATH})
    target_link_libraries(MPICore PUBLIC MPI::MPI_CXX)
endif ()
