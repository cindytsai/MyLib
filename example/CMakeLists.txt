### Example ###
# Equivalent to: g++ -I../include example.cpp -L../lib -lMyLib -Wl,-rpath,../lib
# This is only for Ctest, should also check through linking in cmd.
add_executable(example example.cpp)

# include dir
target_include_directories(example PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${MPI_PATH}/include)

# link lib
target_link_directories(example PUBLIC
        ${MPI_PATH}/lib)
target_link_libraries(example PUBLIC
        MyLib
        mpi)
