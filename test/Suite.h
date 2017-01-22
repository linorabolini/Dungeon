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

using namespace std;

class Suite
{
  public:
    typedef void (Suite::*Func)();

    void registerTest(Func func, const string &name)
    {
        tests.push_back(TestData(func, name));
    }

    void run()
    {
        for (auto &test : tests)
        {
            cout << test._name << endl;
            bind(test._func, this)();
            cout << "  OK" << endl;
        }
    }

    // Data structure
    struct TestData
    {
        Func _func;
        string _name;

        TestData(Func func, const string &name)
            : _func(func), _name(name) {}
    };

  private:
    vector<TestData> tests;
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
