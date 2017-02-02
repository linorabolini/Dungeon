#pragma once
#include "Board.hpp"
#include "Unit.hpp"

class Unit;
class Board;

class TurnManager
{
public:
    virtual void doTurn(Unit* unit, Board* board) {};
};

