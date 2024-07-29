#include "library.h"


int main(int argc, char* argv[]) {
    Initialize(argc, argv);

    PrintCXXVersion();
    CheckDependencies();

    People people;
    people.age = 100;
    people.name = "Cindytsai";


    Finalize();

    return 0;
}

