### Example ###
if (USE_MPI)
    find_package(MPI REQUIRED)
endif ()

# Equivalent to: g++ -I../include example.cpp -L../lib -lMyLib -Wl,-rpath,../lib
# This is only for Ctest, should also check through linking in cmd.
add_executable(example example.cpp)
add_executable(amr_dummy amr_dummy.cpp)

# link lib
target_include_directories(example PUBLIC ../../src/LibraryAPI)
target_include_directories(amr_dummy PUBLIC ../../src/LibraryAPI)
target_link_libraries(example PUBLIC MyLib)
target_link_libraries(amr_dummy PUBLIC MyLib)

if (USE_MPI)
    target_link_libraries(example PUBLIC MPI::MPI_CXX)
endif ()
