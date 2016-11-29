//
//  BoardSuite.h
//  TEST
//
//  Created by Lino Rabolini on 1/26/15.
//
//

#ifndef __TEST__BoardSuite__
#define __TEST__BoardSuite__

#include "../Suite.h"
#include <Board.hpp>

class BoardSuite : public Suite
{
public:
    BoardSuite()
    {
        ADD_TEST(BoardSuite::test_of_board_creation);
    }

    void test_of_board_creation()
    {
        Board* board = new Board(30, 30);

        ASSERT_EQUAL(board->getColumns(), 30);
        ASSERT_EQUAL(board->getRows(), 30);
        ASSERT_TRUE(board->getUnits().size() == 0);

        ASSERT_TRUE(1 == 1);
        ASSERT_FALSE(1 == 3);
        ASSERT_EQUAL(1, 1);
        ASSERT_NOT_EQUAL(1, 2);
    }

};

#endif /* defined(__TEST__BoardSuite__) */
