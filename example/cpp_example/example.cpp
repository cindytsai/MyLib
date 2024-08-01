#include "library.h"


int main(int argc, char* argv[]) {
    Initialize(argc, argv, nullptr);

    PrintCXXVersion();
    CheckDependencies();
    PyBind11Demo();

    People people;
    people.age = 100;
    people.name = "Cindytsai";

    Finalize();

    return 0;
}

