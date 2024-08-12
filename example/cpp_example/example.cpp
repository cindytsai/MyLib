#include <iostream>
#include "library.h"
#ifdef USE_VALGRIND
#include "valgrind/valgrind.h"
#endif


int main(int argc, char *argv[]) {

    char filename[100];

    Initialize(argc, argv);

    PrintCXXVersion();
//    CheckDependencies();
//    PyBind11Demo();

    std::cout << "=================" << std::endl;
    int iter = 100;
    for (int i = 0; i < iter; i++) {

        PyBind11NumPyDemo();

#ifdef USE_VALGRIND
        sprintf(filename, "detailed_snapshot snapshot_before_%d", i);
        VALGRIND_MONITOR_COMMAND(filename);
#endif

        PyBind11NumPyDel("numpy_array");

#ifdef USE_VALGRIND
        sprintf(filename, "detailed_snapshot snapshot_after_%d", i);
        VALGRIND_MONITOR_COMMAND(filename);
#endif
    }
    std::cout << "=================" << std::endl;

    Finalize();

    return 0;
}
