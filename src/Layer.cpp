#include <Layer.hpp>

void Layer::render(sf::RenderWindow *win_)
{
    for(auto &tile : tiles)
    {
        tile.render(win_);
    }
}