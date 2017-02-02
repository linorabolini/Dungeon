#pragma once
#include "Utils.hpp"
#include "GameMacros.hpp"
#include "Unit.hpp"
#include "TurnManager.hpp"
#include "PlayerTurnManager.hpp"
#include "Camera.hpp"
#include "Board.hpp"
#include "CommandQueue.hpp"
#include "GameEvent.hpp"
#include "Observer.hpp"
#include <thread>

#include "GameState.hpp"

class Board;
class TurnManager;

struct TurnModel
{
  TurnModel(Unit *u, TurnManager *tm) : unit(u), turnManager(tm){};
  TurnModel();

  Unit *unit;
  TurnManager *turnManager;
};

class GameManager : public SceneNode, public dungeon::Observer
{
public:
  virtual void updateCurrent();
  virtual void render(sf::RenderWindow *window, const sf::Transform parentTransform) const;

  void load();
  void unload();

  void addTurn(Unit *unit, TurnManager *tm);
  void addTurn(TurnModel &gtm);

  Camera *getCamera() { return camera_; };
  Board *getBoard() { return board_; };

  bool isGameFinished() { return gameFinished_; }

  void setGameState(GameState &gs) { gameState_ = gs; }
  GameState &getGameState() { return gameState_; }

  void initEventListeners();

private:
  void initGame();
  void turnLoop();
  void doTurn(TurnModel gtm);

  Board *board_ = nullptr;
  Camera *camera_ = nullptr;
  std::thread *turnThread_ = nullptr;
  bool gameFinished_ = false;

  SceneNode *uiLayer_;
  SceneNode *gameLayer_;

  std::vector<TurnModel> gameTurns_;

  void addPlayer();
  void loadBoard();

  GameState gameState_;
};
