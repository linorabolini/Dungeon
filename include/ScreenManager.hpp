#ifndef SCREENMANAGER_HPP
#define SCREENMANAGER_HPP

#include "Screen.hpp"
#include "GameObject.hpp"

class ScreenManager : public GameObject
{
  public:
    Screen *loadScreen(Screen *screen);
    Screen *currentScreen() { return current_; };
    void handleInput(sf::RenderWindow *win_);
    virtual void update();
    virtual void render(sf::RenderWindow *win_);

  private:
    Screen *current_ = nullptr;
};

#endif /* SCREENMANAGER_HPP */
