#include "ScreenManager.hpp"

Screen *ScreenManager::loadScreen(Screen *screen)
{
    if (current_)
    {
        current_->unload();
    }

    current_ = screen;
    current_->load();

    return current_;
}

void ScreenManager::handleInput(sf::RenderWindow *win_)
{
    current_->handleInput(win_);
}

void ScreenManager::update()
{
    current_->update();
}

void ScreenManager::render(sf::RenderWindow *win_)
{
    current_->render(win_);
}