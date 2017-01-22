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
        ADD_TEST(BoardSuite::test_of_board_loading);
        ADD_TEST(BoardSuite::test_of_board_tile_nodes_interconnection);
        ADD_TEST(BoardSuite::test_of_unit_creation_and_damage);
        ADD_TEST(BoardSuite::test_of_board_units_and_tiles);
        ADD_TEST(BoardSuite::test_board_unit_movement);
    }

    void test_of_board_creation()
    {
        Board board;

        ASSERT_TRUE(board.getColumns() == 0);
        ASSERT_TRUE(board.getRows() == 0);
        ASSERT_TRUE(SceneNode::nodeCount == 1);
    }

    void test_of_board_loading()
    {
        Board board;
        bool loaded = board.loadFromFile("/Users/linorabolini/Documents/Projects/Cpp/SFML/Test/test/data/testmap.tmx");

        ASSERT_TRUE(loaded);
        ASSERT_TRUE(board.getColumns() == 2);
        ASSERT_TRUE(board.getRows() == 2);
        ASSERT_TRUE(board.getTileLayers().size() == 2);
    }

    void test_of_board_tile_nodes_interconnection()
    {
        Board board;
        bool loaded = board.loadFromFile("/Users/linorabolini/Documents/Projects/Cpp/SFML/Test/test/data/testmap.tmx");
        auto& layers = board.getTileLayers();

        ASSERT_TRUE(loaded);

        auto rows = board.getRows();
        auto cols = board.getColumns();
        for(auto &layer : layers) {
            layer.connectTiles(rows, cols);

            ASSERT_TRUE(layer.getTile(0).isConnectedTo(layer.getTile(1)));
            ASSERT_TRUE(layer.getTile(0).isConnectedTo(layer.getTile(2)));
            ASSERT_TRUE(layer.getTile(1).isConnectedTo(layer.getTile(0)));
            ASSERT_TRUE(layer.getTile(1).isConnectedTo(layer.getTile(3)));
            ASSERT_TRUE(layer.getTile(2).isConnectedTo(layer.getTile(0)));
            ASSERT_TRUE(layer.getTile(2).isConnectedTo(layer.getTile(3)));
            ASSERT_TRUE(layer.getTile(3).isConnectedTo(layer.getTile(1)));
            ASSERT_TRUE(layer.getTile(3).isConnectedTo(layer.getTile(2)));
        }

        // test with a random 4 column 
        for(auto &layer : layers) {
            layer.connectTiles(1, 4);

            ASSERT_TRUE(layer.getTile(0).isConnectedTo(layer.getTile(1)));
            ASSERT_TRUE(layer.getTile(1).isConnectedTo(layer.getTile(2)));
            ASSERT_TRUE(layer.getTile(2).isConnectedTo(layer.getTile(3)));
            ASSERT_TRUE(layer.getTile(3).isConnectedTo(layer.getTile(2)));
            ASSERT_TRUE(layer.getTile(2).isConnectedTo(layer.getTile(1)));
            ASSERT_TRUE(layer.getTile(1).isConnectedTo(layer.getTile(0)));
            ASSERT_FALSE(layer.getTile(0).isConnectedTo(layer.getTile(3)));
        }
    }

    void test_of_unit_creation_and_damage()
    {
        Unit unit;

        ASSERT_TRUE(unit.isDead());
        ASSERT_TRUE(unit.getHP() == 0);

        unit.setHP(20);

        ASSERT_FALSE(unit.isDead());
        ASSERT_TRUE(unit.getHP() == 20);

        unit.receiveDamage(10);

        ASSERT_FALSE(unit.isDead());
        ASSERT_TRUE(unit.getHP() == 10);

        unit.receiveDamage(10);

        ASSERT_TRUE(unit.getHP() == 0);
        ASSERT_TRUE(unit.isDead());
    }

    void test_of_board_units_and_tiles()
    {
        Board board;
        bool loaded = board.loadFromFile("/Users/linorabolini/Documents/Projects/Cpp/SFML/Test/test/data/testmap.tmx");
        auto& tileLayer = board.getTileLayers()[0];
        Tile& tile = tileLayer.getTile(0);
        Unit unit;

        ASSERT_TRUE(loaded);
        ASSERT_TRUE(board.getUnitTile(&unit) == nullptr);
        ASSERT_TRUE(board.getTileUnit(&tile) == nullptr);
        ASSERT_TRUE(unit.getParent() == nullptr);

        board.setUnitTile(&unit, &tile);
        ASSERT_TRUE(board.getUnitTile(&unit) == &tile);
        ASSERT_TRUE(board.getTileUnit(&tile) == &unit);
        ASSERT_TRUE(unit.getParent() == &tile);

        // ERASE tile-unit mapping
        board.setUnitTile(&unit, nullptr);
        ASSERT_TRUE(board.getTileUnit(&tile) == nullptr);
        ASSERT_TRUE(board.getUnitTile(&unit) == nullptr);
    }

    void test_board_unit_movement()
    {
        Board board;
        bool loaded = board.loadFromFile("/Users/linorabolini/Documents/Projects/Cpp/SFML/Test/test/data/testmap.tmx");
        auto& tileLayer = board.getTileLayers()[0];
        Tile& tile = tileLayer.getTile(0);
        Unit unit;

        ASSERT_TRUE(loaded);
        ASSERT_TRUE(board.getUnitTile(&unit) == nullptr);
        ASSERT_TRUE(board.getTileUnit(&tile) == nullptr);
        ASSERT_TRUE(unit.getParent() == nullptr);

        board.setUnitTile(&unit, &tile);
        ASSERT_TRUE(board.getUnitTile(&unit) == &tile);
        ASSERT_TRUE(board.getTileUnit(&tile) == &unit);
        ASSERT_TRUE(unit.getParent() == &tile);

        board.connectTilesFromTileLayer(&tileLayer);
        auto nearTiles = board.getSurroundingTiles(&tile);

        board.setUnitTile(&unit, nearTiles[Direction::DOWN]);
        ASSERT_TRUE(&tileLayer.getTile(1) == nearTiles[Direction::RIGHT]);
        ASSERT_TRUE(board.getUnitTile(&unit) == nearTiles[Direction::DOWN]);
        ASSERT_TRUE(board.getUnitTile(&unit) != &tile);
    }
};

#endif /* defined(__TEST__BoardSuite__) */
