#ifndef TURNMANAGER_HPP
#define TURNMANAGER_HPP

#include "Board.hpp"
#include "Unit.hpp"

class Unit;
class Board;

class TurnManager
{
public:
    virtual void doTurn(Unit* unit, Board* board) {};
};

#endif /* TURNMANAGER_HPP */
