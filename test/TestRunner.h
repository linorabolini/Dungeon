//
//  TestRunner.h
//  TEST
//
//  Created by Lino Rabolini on 1/26/15.
//
//

#ifndef __TEST__TestRunner__
#define __TEST__TestRunner__

#include <vector>
#include <iostream>
#include "Suite.h"

class TestRunner
{
  public:
    void add(Suite *suite)
    {
        this->suites.push_back(suite);
    }

    void run()
    {
        for (auto &suite : this->suites)
            suite->run();
    }

  private:
    std::vector<Suite *> suites;
};

#endif /* defined(__TEST__TestRunner__) */
