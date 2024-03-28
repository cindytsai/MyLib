if (NOT SERIAL_MODE)
    find_package(MPI REQUIRED)
endif ()

add_library(MPICore SHARED MPICore.cpp)

if (SERIAL_MODE)
    target_compile_definitions(MPICore PUBLIC SERIAL_MODE)
endif ()

if (NOT SERIAL_MODE)
    target_include_directories(MPICore PUBLIC ${MPI_INCLUDE_PATH})
    target_link_libraries(MPICore PUBLIC MPI::MPI_CXX)
endif ()
