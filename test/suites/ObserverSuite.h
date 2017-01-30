//
//  ObserverSuite.h
//  TEST
//
//  Created by Lino Rabolini on 1/26/15.
//
//

#ifndef __TEST__ObserverSuite__
#define __TEST__ObserverSuite__

#include "../Suite.h"
#include <Observer.hpp>

using namespace dungeon;

class ObserverSuite : public Suite
{
public:
    ObserverSuite()
    {
        ADD_TEST(ObserverSuite::test_observer_creation);
        ADD_TEST(ObserverSuite::test_observer_registration_of_other_observers);
        ADD_TEST(ObserverSuite::test_observer_auto_observation);
    }

    void test_observer_creation()
    {
        dungeon::Observer obs1;

        int value = 0;

        obs1.on("Event_1", [&](const dungeon::Event ev){
            value = 2;
        });

        ASSERT_TRUE(value == 0);
        
        obs1.notify(dungeon::Event("Event_1"));

        ASSERT_TRUE(value == 2);
    }

    void test_observer_registration_of_other_observers()
    {
        dungeon::Observer obs1;
        dungeon::Observer obs2;

        obs1.observe(&obs2);

        int value = 0;

        obs1.on("Event_1", [&](const dungeon::Event ev){
            value = 2;
        });

        ASSERT_TRUE(value == 0);
        
        obs2.trigger(dungeon::Event("Event_1"));

        ASSERT_TRUE(value == 2);
    }

    void test_observer_auto_observation()
    {
        dungeon::Observer obs1;

        obs1.observe(&obs1);

        int value = 0;

        obs1.on("Event_1", [&](const dungeon::Event ev){
            value = 2;
        });

        ASSERT_TRUE(value == 0);
        
        obs1.trigger(dungeon::Event("Event_1"));

        ASSERT_TRUE(value == 2);
    }
};

#endif /* defined(__TEST__ObserverSuite__) */
