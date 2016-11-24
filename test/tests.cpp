#include "suites/ExampleSuite.h"
#include "TestRunner.h"

int main()
{
    TestRunner tr;
    ExampleSuite ex;

    // add tests
    tr.add(&ex);

    // run tests
    tr.run();
    return 0;
}