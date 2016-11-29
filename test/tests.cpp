#include "suites/BoardSuite.h"
#include "suites/ExampleSuite.h"
#include "TestRunner.h"

int main()
{
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