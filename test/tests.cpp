#include "suites/BoardSuite.h"
#include "suites/ExampleSuite.h"
#include "TestRunner.h"

int main(int argc, char *argv[])
{
    std::cout << "Have " << argc << " arguments:" << std::endl;
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }

    TestRunner tr;
    ExampleSuite ex;
    BoardSuite board;

    // add tests
    tr.add(&ex);
    tr.add(&board);

    // run tests
    tr.run();
    return 0;
}