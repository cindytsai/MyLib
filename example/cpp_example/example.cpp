#include <iostream>
#include "library.h"


int main(int argc, char *argv[]) {
    Initialize(argc, argv);

    PrintCXXVersion();
//    CheckDependencies();
//    PyBind11Demo();

    std::cout << "=================" << std::endl;
    int iter = 100;
    for (int i = 0; i < iter; i++) {
//    while (1) {
        PyBind11NumPyDemo();
//        PyBind11NumPyDel(); // TODO: start here, move del to other function
    }
    std::cout << "=================" << std::endl;

    Finalize();

    return 0;
}
