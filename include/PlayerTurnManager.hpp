#ifndef PLAYERTURNMANAGER_HPP
#define PLAYERTURNMANAGER_HPP

#include "Board.hpp"
#include "screen/GameScreen.hpp"
#include "GameMacros.hpp"
#include "TurnManager.hpp"

class GameScreen;
class Unit;
class Tile;


class PlayerTurnManager : public TurnManager
{
public:
    PlayerTurnManager(GameScreen* gamescreen):
        gamescreen_(gamescreen) {};

    virtual void doTurn(Unit* unit);
    void highlightTile(Tile* tile, bool value=true);
private:
    GameScreen* gamescreen_ = nullptr;
};

#endif /* PLAYERTURNMANAGER_HPP */
