#ifndef GAMESCREEN_HPP
#define GAMESCREEN_HPP

#include "../Screen.hpp"
#include "../Board.hpp"

class GameScreen : public Screen
{
  public:
    GameScreen();
    ~GameScreen();
    virtual void load();
    virtual void unload();
    virtual void handleInput(sf::RenderWindow *win_);
    virtual void update();
    virtual void render(sf::RenderWindow *win_);

private:
    Board board_;

    void loadBoard();
};

#endif /* GAMESCREEN_HPP */
