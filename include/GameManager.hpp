#ifndef GameManager_HPP
#define GameManager_HPP

#include "Utils.hpp"
#include "GameMacros.hpp"
#include "Unit.hpp"
#include "TurnManager.hpp"
#include "PlayerTurnManager.hpp"
#include "Camera.hpp"
#include "Board.hpp"
#include "CommandQueue.hpp"
#include <thread>
#include "Observer.hpp"

#include "GameState.hpp"

class Board;

class GameManager : public SceneNode, public dungeon::Observer
{
  public:
    virtual void updateCurrent();
    virtual void render(sf::RenderWindow *window, const sf::Transform parentTransform) const;
    

    void load();
    void unload();

    void addUnit(Unit *unit);
    Camera *getCamera() { return camera_; };
    Board *getBoard() { return board_; };
    CommandQueue commandQueue;

    bool isGameFinished() { return gameFinished_; }

    GameState& getGameState() { return gameState_; }
    void setGameState(GameState& gs) { gameState_ = gs; }

  private:
    void initGame();
    void turnLoop();
    void doUnitTurn(Unit *unit);

    Board *board_ = nullptr;
    Camera *camera_ = nullptr;
    std::thread *turnThread_ = nullptr;
    bool gameFinished_ = false;

    SceneNode *uiLayer_;
    SceneNode *gameLayer_;

    std::vector<Unit *> units_;

    void addPlayer();
    void loadBoard();

    GameState gameState_;
};

#endif /* GameManager_HPP */
