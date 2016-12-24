#ifndef PLAYERTURNMANAGER_HPP
#define PLAYERTURNMANAGER_HPP

#include "Board.hpp"
#include "GameScreen.hpp"
#include "GameMacros.hpp"
#include "TurnManager.hpp"

class GameScreen;
class Unit;
class Tile;

typedef std::function<void(Unit *unit)> UnitAction;

class PlayerTurnManager : public TurnManager
{
  public:
    virtual void doTurn(Unit *unit);

  private:
    void highlightTiles(std::map<Direction, Tile *>, bool value = true);
    UnitAction waitForPlayerAction(std::map<Direction, UnitAction>);
    std::map<Direction, UnitAction> getUnitPossibleActions(Unit *, std::map<Direction, Tile *>);
};

#endif /* PLAYERTURNMANAGER_HPP */
