//
//  GameManagerSuite.h
//  TEST
//
//  Created by Lino Rabolini on 1/26/15.
//
//

#ifndef __TEST__GameManagerSuite__
#define __TEST__GameManagerSuite__

#include "../Suite.h"
#include <GameState.hpp>
#include <GameManager.hpp>

class GameManagerSuite : public Suite
{
public:
    GameManagerSuite()
    {
        ADD_TEST(GameManagerSuite::gameState_creation);
        ADD_TEST(GameManagerSuite::gameManager_creation);
        ADD_TEST(GameManagerSuite::gameManager_gameState_modification);
    }

    void gameState_creation()
    {
        GameState gs;

        ASSERT_TRUE(gs.floorsCleared == 0);
        ASSERT_TRUE(gs.enemiesKilled == 0);
        ASSERT_TRUE(gs.chestsOpened == 0);
    }

    void gameManager_creation()
    {
        GameManager gm;
        GameState& gs = gm.getGameState();

        ASSERT_TRUE(gm.getGameState().floorsCleared == 0);
        ASSERT_TRUE(gm.getGameState().enemiesKilled == 0);
        ASSERT_TRUE(gm.getGameState().chestsOpened == 0);
    }

    void gameManager_gameState_modification()
    {
        GameManager gm;
        GameState gs;

        gs.floorsCleared = 1;

        gm.setGameState(gs);

        ASSERT_TRUE(gm.getGameState().floorsCleared == 1);

        gm.on("FLOOR_CLEARED", [&](const dungeon::Event) {
            gm.getGameState().floorsCleared++;
        });

        gm.notify(dungeon::Event("FLOOR_CLEARED"));

        ASSERT_TRUE(gm.getGameState().floorsCleared == 2);
    }

};

#endif /* defined(__TEST__GameManagerSuite__) */
