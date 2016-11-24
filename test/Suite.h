//
//  Suite.h
//  TEST
//
//  Created by Lino Rabolini on 1/26/15.
//
//

#ifndef __TEST__Suite__
#define __TEST__Suite__

#include <functional>
#include <assert.h>
#include <vector>
#include <iostream>

class Suite
{
  public:
    typedef void (Suite::*Func)();

    void registerTest(Func func, const std::string &name)
    {
        tests.push_back(TestData(func, name));
    }

    void run()
    {
        for (auto &test : tests)
        {
            std::cout << test._name << std::endl;
            std::bind(test._func, this)();
            std::cout << "  OK" << std::endl;
        }
    }

    // Data structure
    struct TestData
    {
        Func _func;
        std::string _name;

        TestData(Func func, const std::string &name)
            : _func(func), _name(name) {}
    };

  private:
    std::vector<TestData> tests;
};

#define ADD_TEST(func) \
    registerTest(static_cast<Func>(&func), #func);

#define ASSERT_TRUE(expr) \
    assert(expr);

#define ASSERT_FALSE(expr) \
    assert(!(expr));

#define ASSERT_EQUAL(exp1, exp2) \
    assert((exp1) == (exp2));

#define ASSERT_NOT_EQUAL(exp1, exp2) \
    assert((exp1) != (exp2));

#endif /* defined(__TEST__Suite__) */
