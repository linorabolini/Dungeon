#include "suites/BoardSuite.h"
#include "suites/ExampleSuite.h"
#include "suites/GameManagerSuite.h"
#include "suites/ObserverSuite.h"
#include "TestRunner.h"

int main(int argc, char *argv[])
{
    std::cout << "Have " << argc << " arguments:" << std::endl;
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }

    TestRunner tr;

    // suites
    ExampleSuite ex;
    BoardSuite board;
    GameManagerSuite gameManagerSuite;
    ObserverSuite observerSuite;

    // add tests
    tr.add(&ex);
    tr.add(&board);
    tr.add(&gameManagerSuite);
    tr.add(&observerSuite);

    // run tests
    tr.run();
    return 0;
}