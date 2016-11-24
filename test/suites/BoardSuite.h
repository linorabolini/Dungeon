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
#include <Board.h>

class BoardSuite : public Suite
{
public:
    BoardSuite()
    {
        ADD_TEST(BoardSuite::test_of_board_creation);
        ADD_TEST(BoardSuite::test_vectors);
    }

    void test_of_board_creation()
    {
        Board board;

        ASSERT_EQUAL(board.getTiles() == std::nullptr);

        ASSERT_TRUE(1 == 1);
        ASSERT_FALSE(1 == 3);
        ASSERT_EQUAL(1, 1);
        ASSERT_NOT_EQUAL(1, 2);
    }

};

#endif /* defined(__TEST__BoardSuite__) */
