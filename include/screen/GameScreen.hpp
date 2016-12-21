#ifndef GAMESCREEN_HPP
#define GAMESCREEN_HPP


#include <GameMacros.hpp>
#include "../Screen.hpp"
#include "../PlayerTurnManager.hpp"
#include "../Board.hpp"
#include <thread>
#include <tinyxml.h>

class Unit;
class PlayerTurnManager;
class Board;

class GameScreen : public Screen
{
  public:
    virtual void load();
    virtual void unload();
    virtual void handleInput(sf::RenderWindow *window);
    virtual void update();
    virtual void render(sf::RenderWindow *window);

    void gameLoop();
    void initGame();
    void doUnitTurn(Unit* unit);

    void addPlayer();
private:
    Board* board_ = nullptr;
    Camera camera_;
    std::thread* gameLoopthread_;
    int levelFinished_ = 0;

    void loadBoard();
};

#endif /* GAMESCREEN_HPP */
