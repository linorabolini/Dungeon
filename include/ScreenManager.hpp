#ifndef SCREENMANAGER_HPP
#define SCREENMANAGER_HPP

#include "Screen.hpp"

class ScreenManager
{
  public:
    ScreenManager() : current_(0){};

    Screen *loadScreen(Screen *screen);
    Screen *currentScreen() { return current_; };
    void handleInput(sf::RenderWindow *win_);
    void update();
    void render(sf::RenderWindow *win_);

  private:
    Screen *current_;
};

#endif /* SCREENMANAGER_HPP */
