### Example ###
if (NOT SERIAL_MODE)
    find_package(MPI REQUIRED)
endif ()

# Equivalent to: g++ -I../include example.cpp -L../lib -lMyLib -Wl,-rpath,../lib
# This is only for Ctest, should also check through linking in cmd.
add_executable(example example.cpp)

# link lib
target_include_directories(example PUBLIC ../src/LibraryAPI)
target_link_libraries(example PUBLIC MyLib)
if (NOT SERIAL_MODE)
    target_link_libraries(example PUBLIC MPI::MPI_CXX)
else ()
    target_compile_definitions(example PUBLIC SERIAL_MODE)
endif ()
