#include "library.h"


int main(int argc, char* argv[]) {
    Initialize(argc, argv);

    PrintCXXVersion();

    People people;
    people.age = 100;
    people.name = "Cindytsai";

    CheckDependencies();

    Finalize();

    return 0;
}

