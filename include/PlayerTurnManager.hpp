#ifndef PLAYERTURNMANAGER_HPP
#define PLAYERTURNMANAGER_HPP

#include "TurnManager.hpp"
#include "Directions.hpp"
#include "Tile.hpp"
#include "Board.hpp"
#include "GameMacros.hpp"
#include "TextNode.hpp"
#include <tween.h>

class Tile;
class Unit;
class Board;

using namespace std;
using namespace sf;

typedef function<void()> UnitAction;
typedef map<Direction, UnitAction> UnitActionsByDirection;
typedef map<Direction, Tile *> TilesByDirection;

class PlayerTurnManager : public TurnManager
{
public:
  virtual void doTurn(Unit* unit, Board* board);

private:
  void highlightTiles(UnitActionsByDirection &possibleActions, TilesByDirection, bool value = true);
  UnitAction* waitForPlayerAction(UnitActionsByDirection &);
  UnitActionsByDirection getUnitPossibleActions(Unit *, Board* board);
  map<Direction, Keyboard::Key> dirToKeyboard_ = {
      {Direction::UP, Keyboard::Up},
      {Direction::DOWN, Keyboard::Down},
      {Direction::LEFT, Keyboard::Left},
      {Direction::RIGHT, Keyboard::Right}};
};

#endif /* PLAYERTURNMANAGER_HPP */
