#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include "../Screen.hpp"

class MainMenu : public Screen
{
  public:
    virtual void render(sf::RenderWindow *win_);
};

#endif /* MAINMENU_HPP */
