#ifndef TURNMANAGER_HPP
#define TURNMANAGER_HPP

#include "Unit.hpp"

class Unit;

class TurnManager
{
public:
    virtual void doTurn(Unit* unit) {};
};

#endif /* TURNMANAGER_HPP */
