#ifndef GameManager_HPP
#define GameManager_HPP

#include "GameMacros.hpp"
#include "Unit.hpp"
#include "TurnManager.hpp"
#include "PlayerTurnManager.hpp"
#include "Camera.hpp"
#include "Board.hpp"
#include <thread>
#include "CommandQueue.hpp"

class Board;

class GameManager : public SceneNode
{
  public:
    virtual void updateCurrent();
    virtual void render(sf::RenderWindow *window);

    void load();
    void unload();

    void addUnit(Unit *unit);
    Camera *getCamera() { return camera_; };
    Board *getBoard() { return board_; };
    CommandQueue commandQueue;

  private:
    void initGame();
    void turnLoop();
    void doUnitTurn(Unit *unit);

    Board *board_ = nullptr;
    Camera *camera_ = nullptr;
    std::thread *turnThread_ = nullptr;
    int levelFinished_ = 0;

    SceneNode *uiLayer_;
    SceneNode *gameLayer_;

    std::vector<Unit *> units_;

    void addPlayer();
    void loadBoard();
};

#endif /* GameManager_HPP */
